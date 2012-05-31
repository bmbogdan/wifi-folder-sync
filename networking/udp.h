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
    void masterDiscovered(qint16 port, qint32 addr);
    
public slots:
    void initialize(bool);
    void readPendingDatagrams();
    void sendBroadcast();
    qint16 getId() const{
        return id;
    }
    qint8 getCounter() const{
        return timerCounter;
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
    QList<qint16> masterIDs;

};

#endif // UDP_H
