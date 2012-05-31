#include "gui.h"
#include "ui_gui.h"
#include "QFileDialog"
#include <QCloseEvent>
#include "qdebug.h"
#include "filesystem/directoryparser.h"

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

void Gui::closeEvent(QCloseEvent *event)
{
    if(worker->isRunning())worker->quit();    //exit from thread event loop
    event->accept();    //accept event
}
void Gui::on_masterButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    //QDir direct = QDir(dir);
    //QString str = d_scanner->getFileSystemFromDir(direct);

    ui->textEdit->append("MasterDir->" + dir);
    //DirectoryParser::getFileList(str);
    QByteArray ba;
    ba.resize(1);
    ba[0]=0x01;//master code 0000 0001
    ba.append(dir);
    if(worker->isRunning())worker->fromGui(ba);
}

void Gui::on_slaveButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    //QDir direct = QDir(dir);
    //QString str = d_scanner->getFileSystemFromDir(direct);

    ui->textEdit->append("SlaveDir->" + dir);
    //DirectoryParser::getFileList(str);
    QByteArray ba;
    ba.resize(1);
    ba[0]=0x02;//master code 0000 0001
    ba.append(dir);
    if(worker->isRunning())worker->fromGui(ba);
}

void Gui::dataFromThread(QByteArray ba)
{
    if(ba[0] & 0x04){
        ui->textEdit->append("Already selected!");
    }

}
