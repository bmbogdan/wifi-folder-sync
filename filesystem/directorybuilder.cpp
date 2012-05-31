#include "directorybuilder.h"
#include "QDir"

DirectoryBuilder::DirectoryBuilder(const QList<FileObject> f, QObject *parent) :
    fs(f),QObject(parent)
{

}
void DirectoryBuilder::mkDirs(QString parentDir){
    QString absolutePath(parentDir);
    for(int i=0;i<fs.size();i++){
        if(!fs.at(i).isFile()){
            QDir dir(absolutePath);
            dir.mkpath(fs.at(i).getName());
        }
    }
}
