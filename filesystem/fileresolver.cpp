#include "fileresolver.h"

FileResolver::FileResolver(const QList<FileObject> f, QObject *parent) :
    fs(f),QObject(parent)
{

}

QStack<qint16> FileResolver::getIndexesOfFiles(){
    QStack<qint16> stack;
    for(int i=0; i<fs.size();i++){
        if(fs.at(i).isFile()){
            stack.push(i);
        }
    }
    return stack;
}
