#include "mthread.h"
#include "qcoreapplication.h"

//tcpport=udpidport+100

MThread::MThread(QObject *parent) :
    QThread(parent)
{
    udpSkt = 0;
    udpSkt = new Udp(this);
    tcpSkt = 0;
    tcpSrv = 0;
    master_fileStruct = "";
    d_scanner = new DirectoryScanner(this);
    connect(udpSkt,SIGNAL(masterDiscovered(qint16,qint32)), this, SLOT(connectToMaster(qint16,qint32)));
}
void MThread::run()
{
    QThread::exec();    //event loop for thread, tine threadul activ

    // dupa oprirea threadului do some clean up
    //QMetaObject::invokeMethod(this->parent(),"metaCalled", Qt::QueuedConnection, Q_ARG(int, exitCode));
}
void MThread::toGui(const QByteArray &ba)
{
    //multiplexeaza informatiile
    QMetaObject::invokeMethod(this->parent(),"dataFromThread", Qt::QueuedConnection, Q_ARG(QByteArray, ba));

}
void MThread::fromGui(QByteArray &ba)
{
    //demultiplexeaza ba si citeste date master sau slave
    if(ba[0]&0x01){
        udpSkt->initialize(true);
        initTcpServer();
        ba.remove(0,1);
        QString masterDir = QString(ba);
        master_fileStruct = d_scanner->getFileSystemFromDir(QDir(masterDir));
        master_fileSystem = DirectoryParser::getFileList(master_fileStruct);

    }else{
        //slave parse filesystem
    }
}
void MThread::initTcpServer()
{
    qint16 port = udpSkt->getId() + 100;
    tcpSrv = new QTcpServer(this);
    tcpSrv->listen(QHostAddress::Any, port);
    connect(tcpSrv, SIGNAL(newConnection()), this,SLOT(onSlaveConnected()) );
}
void MThread::connectToMaster(qint16 port, qint32 addr)
{
    //todo - counter to keep track of connections number
    QTcpSocket *sktSlave = new QTcpSocket(this);
    sktSlave->connectToHost(QHostAddress(addr),port+100);
    connect(sktSlave, SIGNAL(readyRead()),this,SLOT(syncToMaster()));
}
void MThread::onSlaveConnected()
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

}
void MThread::masterReadyRead(){
    QTcpSocket *sktSlave = (QTcpSocket*)QObject::sender();
    QByteArray header = sktSlave->read(1); // read 1 byte, header
    QByteArray filerequested;
    if(header[0] == 0x10){ //0001 0000 req file
        filerequested = sktSlave->readAll();
        FileObject fo(QString(filerequested), true);
        if(master_fileSystem.contains(fo)){
            //trimite fisierul!!! si header cu indexul fisierului
        }
    }

}
void MThread::syncToMaster()
{
    QTcpSocket *sktSlave = (QTcpSocket*)QObject::sender();
    //parse header
    //if dir struct, compare current dir struct and request filemode
    QByteArray header = sktSlave->read(1);
    if(header[0] == 0x03){
        //slave a primit o struct d dir de la master
        received_fileStruct = QString(sktSlave->readAll());
        received_fileSystem = DirectoryParser::getFileList(received_fileStruct);

    }
}
