#include "gui.h"
#include "ui_gui.h"
#include "QFileDialog"

#include "qdebug.h"


Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    d_scanner = new DirectoryScanner(this);
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
    QString str = d_scanner->getFileSystemFromDir(direct);

    ui->textEdit->append(str);
}
