#ifndef MTHREAD_H
#define MTHREAD_H

#include <QThread>
#include "udp.h"

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
    void fromGui(const QByteArray&);


private:
    Udp *udpSkt;
    void initTcpServer();


private slots:

};

#endif // THREAD_H
