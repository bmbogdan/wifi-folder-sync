#ifndef MASTERSLAVE_H
#define MASTERSLAVE_H

#include <QObject>
#include <QTcpServer>
#include "filesystem/directoryscanner.h"
#include "filesystem/directoryparser.h"
#include "filesystem/fileobject.h"
#include <QList>

class MasterSlave : public QObject
{
    Q_OBJECT
public:
    explicit MasterSlave(QObject *parent = 0);
    
signals:
    
public slots:
    void setMasterDir(QString);
    void initTcpServer(qint16);
    void onSlaveConnected();
    void masterReadyRead();

private:
    QTcpServer *tcpSrv;
    QString master_fileStruct;
    QList<FileObject> master_fileSystem;
    QString masterDir;
    DirectoryScanner *d_scanner;
};

#endif // MASTERSLAVE_H
