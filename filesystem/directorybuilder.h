#ifndef DIRECTORYBUILDER_H
#define DIRECTORYBUILDER_H

#include <QObject>
#include "fileobject.h"

class DirectoryBuilder : public QObject
{
    Q_OBJECT
public:
    explicit DirectoryBuilder(const QList<FileObject> f,QObject *parent = 0);
    
signals:
    
public slots:
    void mkDirs(QString parentDir);
private:
    QList<FileObject> fs;
};

#endif // DIRECTORYBUILDER_H
