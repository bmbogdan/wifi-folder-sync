#include "mthread.h"
#include "qcoreapplication.h"

MThread::MThread(QObject *parent) :
    QThread(parent)
{

}

void MThread::run()
{
    QThread::exec();    //event loop for thread, tine threadul activ

    // dupa oprirea threadului do some clean up
    //QMetaObject::invokeMethod(this->parent(),"metaCalled", Qt::QueuedConnection, Q_ARG(int, exitCode));

}

void MThread::toGui(const QByteArray &ba)
{
    QMetaObject::invokeMethod(this->parent(),"dataFromThread", Qt::QueuedConnection, Q_ARG(QByteArray, ba));

}


void MThread::fromGui(const QByteArray &ba)
{

}

