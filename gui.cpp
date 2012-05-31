#include "gui.h"
#include "ui_gui.h"
#include "QFileDialog"
#include <QCloseEvent>
#include "qdebug.h"
#include "directoryparser.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    worker = 0;
    worker = new MThread(this);
    worker->start();
}

Gui::~Gui()
{
    delete ui;
}

void Gui::on_dirButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    QDir direct = QDir(dir);
    //QString str = d_scanner->getFileSystemFromDir(direct);

    ui->textEdit->append(dir);
    //DirectoryParser::getFileList(str);
    QByteArray ba;
    ba.resize(1);
    ba[0]=0x01;//master code 0000 0001
    ba.append(dir);
}

void Gui::closeEvent(QCloseEvent *event)
{
    if(worker->isRunning())worker->quit();    //exit from thread event loop
    event->accept();    //accept event
}
