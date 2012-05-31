#include "mthread.h"
#include "qcoreapplication.h"
#include "networking/masterslave.h"
#include "networking/slavemaster.h"

//tcpport=udpidport+100

MThread::MThread(QObject *parent) :
    QThread(parent)
{
    isSlaveDirSelected = false;
    isMasterDirSelected = false;
    udpSkt = 0;
    udpSkt = new Udp(this);
    connect(udpSkt,SIGNAL(masterDiscovered(qint16,qint32)), this, SLOT(connectToMaster(qint16,qint32)));
}
void MThread::run()
{
    QThread::exec();    //event loop for thread, keep thread active

    // after thread meltdown do some clean up
    //QMetaObject::invokeMethod(this->parent(),"metaCalled", Qt::QueuedConnection, Q_ARG(int, exitCode));
}
void MThread::toGui(const QByteArray &ba)
{
    //multiplexeaza informatiile
    QMetaObject::invokeMethod(this->parent(),"dataFromThread", Qt::QueuedConnection, Q_ARG(QByteArray, ba));
}
void MThread::fromGui(QByteArray &ba)
{
    //demultiplexeaza ba si citeste date master0x01 sau slave0x02
    if(ba[0]&0x01)
    {        
        if(isMasterDirSelected){
            QByteArray b;
            b.resize(1);
            b[0] = 0x04;//no coded
            toGui(b);
            return;
        }
        ba.remove(0,1);
        QString masterDir = QString(ba);

        //create new masterslave
        MasterSlave *ms = new MasterSlave(this);

        if(udpSkt->getCounter()==0)
        udpSkt->initialize(true);
        else udpSkt->resetBroadcasting();

        //setmasterdir
        ms->setMasterDir(masterDir);

        //inittcpserver with id of udpskt
        ms->initTcpServer(udpSkt->getId());

        isMasterDirSelected = true;

    }
    if(ba[0]&0x02){
        if(isSlaveDirSelected){
            QByteArray b;
            b.resize(1);
            b[0] = 0x04;//no coded
            toGui(b);
            return;
        }
        //slave parse filesystem
        ba.remove(0,1);
        slaveDir = QString(ba);
        isSlaveDirSelected = true;
    }
}
void MThread::connectToMaster(qint16 port, qint32 addr)
{
    //todo - counter to keep track of connections number

    if(!isSlaveDirSelected)return; // if slave dir is not setted return!

    //create new slavemaster obj and call connecttomaster
    SlaveMaster *sm = new SlaveMaster(this);
    sm->setSlaveDir(slaveDir);
    sm->connectToMaster(port,addr);
}
