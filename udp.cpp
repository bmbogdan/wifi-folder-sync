#include "udp.h"

Udp::Udp(QObject *parent) :
    QObject(parent)
{
    socket = 0;
}

void Udp::initialize()
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 1989);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
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
    if(datagram.size()>42+1) return; //discard datagram
    quint32 addr = h_address.toIPv4Address();
    //QByteArray ba(addr);
    //daca ... e master senderul atunci trimite ack si el se pune slave
}
