#include "fm_sobre.h"
#include "ui_fm_sobre.h"

fm_sobre::fm_sobre(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_sobre)
{
    ui->setupUi(this);
}

fm_sobre::~fm_sobre()
{
    delete ui;
}

void fm_sobre::on_pushButton_fechar_clicked()
{
    close();
}

