#include "openx.h"
#include "ui_openx.h"

openX::openX(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::openX)
{
    ui->setupUi(this);
}

openX::~openX()
{
    delete ui;
}

void openX::on_quitButton_clicked()
{
    qApp->quit();
}
