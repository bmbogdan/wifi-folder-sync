#include "udp.h"
#include<ctime>

//protocol discovery 1 min ptr anuntarea deviceurilor in lan

Udp::Udp(QObject *parent) :
    QObject(parent)
{
    srand(time(0));
    id = 10000 + (rand()%100)*2*(rand()%100);
    qDebug()<<id;

    socket = 0;
    socket = new QUdpSocket(this);
    timerCounter = 0;
    timerObj = 0;
    socket->bind(QHostAddress::Any, 1989);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void Udp::initialize(bool master)
{
    if(!master)return;
    timerObj = new QTimer(this);
    connect(timerObj, SIGNAL(timeout()), this, SLOT(sendBroadcast()));
    timerObj->start(1000);
}
void Udp::readPendingDatagrams()
{
     while (socket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(socket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         socket->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);

         processDatagram(datagram, sender, senderPort);

         ///mai degraba procesez aici datagrameleleele
     }
 }
void Udp::processDatagram(const QByteArray datagram, const QHostAddress h_address, const quint16 port)
{
    qDebug()<<"Processdatagram!";
    //char *ch = (char*)id;
    QByteArray idb(reinterpret_cast<const char*>(&id), sizeof(id));

    if(idb[0]==datagram[0] && idb[1]==datagram[1])
    {
        qDebug()<<"aceeasi datagrama";
        return;
    }

    qDebug()<<"alta datagrama";
    if(datagram.size()>42+1) return; //discard datagram
    quint32 addr = h_address.toIPv4Address();
    //QByteArray ba(addr);
    QByteArray idOfSender;
    idOfSender.append(datagram[0]);
    idOfSender.append(datagram[1]);
    qint16 idSender = (qint16)idOfSender.toInt(); // check here conversion !!!
    if(masterIDs.contains(idSender))return;

    if(masterIDs.size() > 5)return; // overflow protection
    masterIDs.append(idSender);

    //citeste portul masterului si trimite un semnal pentru a se conecta la serverul tcp
    emit masterDiscovered(idSender,addr);
}

//anunta masterul in retea
void Udp::sendBroadcast(){

    if(timerCounter>60){
        timerObj->stop();
        return;
    }
    timerCounter++;
    qDebug()<<"Broadcasting!";

    //prepare header
    //write id in header
    QByteArray data(reinterpret_cast<const char*>(&id), sizeof(id));

    //id este portul serverului tcp care va asculta

    socket->writeDatagram(data,QHostAddress::Broadcast, 1989);

}
