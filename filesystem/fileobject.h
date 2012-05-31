#ifndef FILEOBJECT_H
#define FILEOBJECT_H
#include<QString>
class FileObject
{
public:
    FileObject(QString,bool);
    bool isFile() const{
        return file;
    }
    QString getName() const{
        return name;
    }
    bool operator==(const FileObject &other) const{
        if(isFile() == other.isFile()){
            if(getName() == other.getName()){
                return true;
            }
            return false;
        }
        return true;
      }
private:
    bool file;
    QString name;
};

#endif // FILEOBJECT_H
