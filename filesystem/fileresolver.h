#ifndef FILERESOLVER_H
#define FILERESOLVER_H
#include "filesystem/directoryparser.h"
#include "filesystem/fileobject.h"
#include <QObject>
#include <QStack>

class FileResolver : public QObject
{
    Q_OBJECT
public:
    explicit FileResolver(const QList<FileObject> f,QObject *parent = 0);
    
signals:
    
public slots:
    QStack<qint16> getIndexesOfFiles();

private:
    QList<FileObject> fs;
    
};

#endif // FILERESOLVER_H
