#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>


class Udp : public QObject
{
    Q_OBJECT
public:
    explicit Udp(QObject *parent = 0);
    
signals:
    
public slots:
    void initialize();
    void readPendingDatagrams();

private:
    QUdpSocket *socket;
    void processDatagram(const QByteArray, const QHostAddress, const quint16);

};

#endif // UDP_H
