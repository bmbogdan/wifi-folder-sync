#include "fileobject.h"

FileObject::FileObject(QString nm, bool file = true)
{
    name = nm;
    this->file = file;
}
