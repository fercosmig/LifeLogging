#ifndef FM_SOBRE_H
#define FM_SOBRE_H

#include <QDialog>

namespace Ui {
class fm_sobre;
}

class fm_sobre : public QDialog
{
    Q_OBJECT

public:
    explicit fm_sobre(QWidget *parent = nullptr);
    ~fm_sobre();

private slots:
    void on_pushButton_fechar_clicked();

private:
    Ui::fm_sobre *ui;
};

#endif // FM_SOBRE_H
