#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>

#include "QTimer"

class Udp : public QObject
{
    Q_OBJECT
public:
    explicit Udp(QObject *parent = 0);
    
signals:
    
public slots:
    void initialize(bool);
    void readPendingDatagrams();
    void sendBroadcast();
    qint16 getId(){
        return id;
    }
    void resetBroadcasting(){
        timerCounter = 0;
        timerObj->start(1000);
    }

private:
    QUdpSocket *socket;
    void processDatagram(const QByteArray, const QHostAddress, const quint16);
    qint16 id;
    qint8 timerCounter;
    QTimer *timerObj;

};

#endif // UDP_H
