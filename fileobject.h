#ifndef FILEOBJECT_H
#define FILEOBJECT_H
#include<QString>
class FileObject
{
public:
    FileObject(QString,bool);
    bool isFile(){
        return file;
    }
    QString getName(){
        return name;
    }
private:
    bool file;
    QString name;
};

#endif // FILEOBJECT_H
