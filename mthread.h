#ifndef MTHREAD_H
#define MTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include "udp.h"
#include "directoryscanner.h"
#include "directoryparser.h"

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
    void onSlaveConnected();
    void syncToMaster();
    void masterReadyRead();

private:
    Udp *udpSkt;
    void initTcpServer();
    QTcpSocket *tcpSkt;
    QTcpServer *tcpSrv;
    DirectoryScanner *d_scanner;
    QString master_fileStruct;
    QList<FileObject> master_fileSystem;
    QString slave_fileStruct;
    QList<FileObject> slave_fileSystem;
    QString received_fileStruct;
    QList<FileObject> received_fileSystem;


private slots:

};

#endif // THREAD_H
