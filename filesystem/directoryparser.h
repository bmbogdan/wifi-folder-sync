#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include <QObject>
#include "fileobject.h"
#include "QList"

class DirectoryParser : public QObject
{
    Q_OBJECT
public:
    explicit DirectoryParser(QObject *parent = 0);
    
signals:
    
public slots:
public:
    static QList<FileObject> getFileList(QString);
    
};

#endif // DIRECTORYPARSER_H
