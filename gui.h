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
    void on_dirButton_clicked();

private:
    Ui::Gui *ui;
    MThread *worker;
    void closeEvent(QCloseEvent *);
};

#endif // GUI_H
