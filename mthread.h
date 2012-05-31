#ifndef MTHREAD_H
#define MTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "networking/udp.h"

/*************************************************
**************************************************
Worker Thread
**************************************************
**************************************************
*/

class MThread : public QThread
{
    Q_OBJECT
public:
    explicit MThread(QObject *parent = 0);
    
signals:
    
public slots:
    void run();
    //gui data interface
    void toGui(const QByteArray&);
    void fromGui(QByteArray&);
    void connectToMaster(qint16 port, qint32 addr);

private:
    Udp *udpSkt;
    QString slaveDir;
    bool isSlaveDirSelected;
    bool isMasterDirSelected;


private slots:

};

#endif // THREAD_H
