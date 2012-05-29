#ifndef DIRECTORYSCANNER_H
#define DIRECTORYSCANNER_H

#include <QObject>
#include <QDir>
#include <QFileInfo>

class DirectoryScanner : public QObject
{
    Q_OBJECT
public:
    explicit DirectoryScanner(QObject *parent = 0);
    
signals:
    
public slots:
    QString getFileSystemFromDir(QDir);

private:
    int contor;
    
};

#endif // DIRECTORYSCANNER_H
