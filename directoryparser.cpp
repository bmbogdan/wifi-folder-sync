#include "directoryparser.h"
#include "qdebug.h"
#include "qstringlist.h"
#include "fileobject.h"
#include <QDir>

DirectoryParser::DirectoryParser(QObject *parent) :
    QObject(parent)
{

}
QList<FileObject> DirectoryParser::getFileList(QString fs){

    QStringList sl = fs.split("\n");//n+1

    QList<FileObject> fl;

    QStringList dirNameTemp;

    for(int m=0;m<sl.size() - 1;m++){

        QString temp = sl.at(m);
        int index = temp.indexOf(QRegExp("[^ ]"));
        temp = temp.trimmed();
        QString fileName = "";

        if(temp.contains("<")){
            temp = temp.remove(0,1);
            QStringList tmp;
            for(int i=0;i<index/2;i++){
                tmp.append(dirNameTemp.at(i));

            }
            dirNameTemp = tmp;
            dirNameTemp.append(temp);

            for(int i=0;i<dirNameTemp.size();i++){
                if(i == dirNameTemp.size() - 1){
                    fileName.append(dirNameTemp.at(i));
                }else{
                    fileName.append(dirNameTemp.at(i)).append(QDir::separator());
                }
            }
            fl.append(FileObject(fileName,false));
        }
        else{
            QStringList tmp;
            for(int i=0;i<index/2;i++){
                tmp.append(dirNameTemp.at(i));

            }
            dirNameTemp = tmp;
            dirNameTemp.append(temp);

            for(int i=0;i<dirNameTemp.size();i++){
                if(i == dirNameTemp.size() - 1){
                    fileName.append(dirNameTemp.at(i));
                }else{
                    fileName.append(dirNameTemp.at(i)).append(QDir::separator());
                }
            }
            fl.append(FileObject(fileName,true));

        }
        qDebug()<<fileName;
    }
    return fl;
}
