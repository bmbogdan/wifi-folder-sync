#include "mthread.h"
#include "qcoreapplication.h"

//tcpport=udpidport+100

MThread::MThread(QObject *parent) :
    QThread(parent)
{
    udpSkt = 0;
    udpSkt = new Udp(this);
}

void MThread::run()
{
    QThread::exec();    //event loop for thread, tine threadul activ

    // dupa oprirea threadului do some clean up
    //QMetaObject::invokeMethod(this->parent(),"metaCalled", Qt::QueuedConnection, Q_ARG(int, exitCode));
}

void MThread::toGui(const QByteArray &ba)
{
    QMetaObject::invokeMethod(this->parent(),"dataFromThread", Qt::QueuedConnection, Q_ARG(QByteArray, ba));

}


void MThread::fromGui(const QByteArray &ba)
{
    //demultiplexeaza ba si citeste date master sau slave
    //initUdp(bool master=true)
    bool master = true;
    if(master){
        udpSkt->initialize(master);
        initTcpServer();
    }
}


void MThread::initTcpServer(){

}

