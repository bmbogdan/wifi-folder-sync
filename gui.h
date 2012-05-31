#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "mthread.h"

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    
private slots:
    void on_masterButton_clicked();
    void on_slaveButton_clicked();
    void dataFromThread(QByteArray);
private:
    Ui::Gui *ui;
    MThread *worker;
    void closeEvent(QCloseEvent *);
};

#endif // GUI_H
