#include "masterslave.h"
#include <QTcpSocket>
#include <QByteArray>

MasterSlave::MasterSlave(QObject *parent) :
    QObject(parent)
{
    tcpSrv = 0;
    master_fileStruct = "";
    d_scanner = new DirectoryScanner(this);
}

void MasterSlave::initTcpServer(qint16 id)
{
    qint16 port = id + 100;
    tcpSrv = new QTcpServer(this);
    tcpSrv->listen(QHostAddress::Any, port);
    connect(tcpSrv, SIGNAL(newConnection()), this,SLOT(onSlaveConnected()) );
}

void MasterSlave::onSlaveConnected()
{
    //todo - counter to keep track of connections number
    QTcpSocket *sktMaster = tcpSrv->nextPendingConnection();
    connect(sktMaster, SIGNAL(readyRead()),this, SLOT(masterReadyRead()));

    //write data header - master folder filesystem
    QByteArray ba;
    ba.resize(1);
    ba[0]=0x03; // 0000 0011 // master + filestruct
    ba.append(master_fileStruct);
    sktMaster->write(ba);
    sktMaster->flush();
}
void MasterSlave::masterReadyRead()
{
    QTcpSocket *sktSlave = (QTcpSocket*)QObject::sender();
    QByteArray header = sktSlave->read(1); // read 1 byte, header
    QByteArray filerequested;
    if(header[0]&0x10){ //0001 0000 req file
        filerequested = sktSlave->readAll();
        FileObject fo(QString(filerequested), true);
        if(master_fileSystem.contains(fo))
        {
            //build dir path
            QString absolutePath("");
            absolutePath.append(masterDir).append(QDir::separator());
            absolutePath.append(fo.getName());
            //pack header
            QByteArray header;
            header.append(0x20);
            header.append((qint16)master_fileSystem.indexOf(fo));
            sktSlave->write(header);

            //trimite fisierul!!! si header cu indexul fisierului
            //also send filesize in qint32 - daca nu merge!
            //to do not opening case
            QFile fisier(absolutePath);
            if (!fisier.open(QIODevice::ReadOnly))
                qDebug()<<"not opening";

            while(!fisier.atEnd()){
                sktSlave->write(fisier.read(1000));
            }
            fisier.close();

            sktSlave->flush();
        }
    }
}
void MasterSlave::setMasterDir(QString s)
{
    masterDir = s;
    master_fileStruct = d_scanner->getFileSystemFromDir(s);
    master_fileSystem = DirectoryParser::getFileList(master_fileStruct);
}
