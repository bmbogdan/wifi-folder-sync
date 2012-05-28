#ifndef MTHREAD_H
#define MTHREAD_H

#include <QThread>

/*************************************************
**************************************************
Worker Thread
**************************************************
**************************************************
*/

class MThread : public QThread
{
    Q_OBJECT
public:
    explicit MThread(QObject *parent = 0);
    
signals:
    
public slots:
    void run();

    //gui data interface
    void toGui(const QByteArray&);
    void fromGui(const QByteArray&);


private:

private slots:

};

#endif // THREAD_H
