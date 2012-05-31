#include "slavemaster.h"
#include <QHostAddress>
#include "filesystem/fileobject.h"
#include "filesystem/fileresolver.h"
#include "filesystem/directorybuilder.h"

SlaveMaster::SlaveMaster(QObject *parent) :
    QObject(parent)
{
    sktSlave = 0;
}

void SlaveMaster::connectToMaster(qint16 port, qint32 addr)
{
    //todo - counter to keep track of connections number
    sktSlave = new QTcpSocket(this);
    sktSlave->connectToHost(QHostAddress(addr),port+100);
    connect(sktSlave, SIGNAL(readyRead()),this,SLOT(slaveReadyRead()));
}
void SlaveMaster::slaveReadyRead()
{
    //parse header
    //if dir struct, compare current dir struct and request filemode
    QByteArray header = sktSlave->read(1);
    if(header[0] & 0x03){
        //slave a primit o struct d dir de la master
        received_fileStruct = QString(sktSlave->readAll());
        received_fileSystem = DirectoryParser::getFileList(received_fileStruct);
        FileResolver *fr = new FileResolver(received_fileSystem,this);
        fileStack = fr->getIndexesOfFiles();

        //make dirs
        DirectoryBuilder *db = new DirectoryBuilder(received_fileSystem,this);
        db->mkDirs(slaveDir);

        //request first file!
        if(fileStack.size() == 0) return; // if no files existing in filesyst
        QByteArray ba;
        ba.resize(1);
        ba[0] = 0x10;
        ba.append(received_fileSystem.at(fileStack.pop()).getName());
        sktSlave->write(ba);
        sktSlave->flush();
    }
    if(header[0] & 0x20){

        //slave received an header announcing a file
        //get indexof file
        QByteArray fileIndex = sktSlave->read(2);

        //build absolute path
        QString absolutePath("");
        QString file = received_fileSystem.at(fileIndex.toInt()).getName();
        absolutePath.append(slaveDir).append(QDir::separator());
        absolutePath.append(file);

        //make file from absolute path
        //to do not opening case
        QFile fisier(absolutePath);
        if (!fisier.open(QIODevice::WriteOnly))
            qDebug()<<"not opening";

        //get file from network and write it to disk
        //readfilesize in qint32 to stop reading - daca nu merge!

        while (!sktSlave->atEnd())
        {
            fisier.write(sktSlave->read(1000));
        }
        fisier.flush();
        fisier.close();

        //request next file!
        if(fileStack.size() == 0) return; // if stack is empty, no more files
        QByteArray ba;
        ba.resize(1);
        ba[0] = 0x10;
        ba.append(received_fileSystem.at(fileStack.pop()).getName());
        sktSlave->write(ba);
        sktSlave->flush();
    }
}
void SlaveMaster::setSlaveDir(QString s){
    slaveDir = s;
}
