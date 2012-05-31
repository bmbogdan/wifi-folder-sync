#ifndef SLAVEMASTER_H
#define SLAVEMASTER_H

#include <QObject>
#include "filesystem/directoryscanner.h"
#include "filesystem/directoryparser.h"
#include "filesystem/fileresolver.h"
#include <QTcpSocket>
#include <QStack>

class SlaveMaster : public QObject
{
    Q_OBJECT
public:
    explicit SlaveMaster(QObject *parent = 0);
    
signals:
    
public slots:
    void connectToMaster(qint16 port, qint32 addr);
    void setSlaveDir(QString);
    void slaveReadyRead();

private:
    DirectoryScanner *d_scanner;
    QString slave_fileStruct;
    QString slaveDir;
    QList<FileObject> slave_fileSystem;
    QString received_fileStruct;
    QList<FileObject> received_fileSystem;
    QTcpSocket *sktSlave;
    QStack<qint16> fileStack;
    
};

#endif // SLAVEMASTER_H
