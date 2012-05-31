#include "slavemaster.h"
#include <QHostAddress>

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
    }
}
void SlaveMaster::setSlaveDir(QString s){
    slaveDir = s;
}
