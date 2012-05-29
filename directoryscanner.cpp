#include "directoryscanner.h"
#include "qdebug.h"

//Returns tree like filesystem structure in canonical form
//directories are reprezented with "<" symbol at the begining of their names



DirectoryScanner::DirectoryScanner(QObject *parent) :
    QObject(parent)
{
    counter = 0;
}
QString DirectoryScanner::getFileSystemFromDir(QDir dir){
    QFileInfoList fil = dir.entryInfoList(QDir::Dirs |
                                     QDir::Files |
                                     QDir::NoSymLinks |
                                     QDir::NoDotAndDotDot
                                         ,QDir::DirsFirst );

    QString filesystem = "";
    if(fil.size() == 0)return filesystem;

    for(int i = 0; i < fil.size(); i++){
        QFileInfo fi = fil.at(i);

        qDebug()<<fi.fileName();

        for(int j=0;j<counter;j++){
            filesystem.append("  ");
        }
        if(fi.isDir()){
            counter += 1;
            filesystem.append("<");
            filesystem.append(fi.fileName());
            filesystem.append("\n");
            filesystem.append(getFileSystemFromDir(QDir(fi.absoluteFilePath())));
            counter -= 1;
        }
        else{
            filesystem.append(fi.fileName());
            filesystem.append("\n");
        }
    }
    return filesystem;
}
