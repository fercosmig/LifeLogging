#ifndef FM_EVENTOS_H
#define FM_EVENTOS_H

#include <QDialog>
#include <QVector>
#include "Evento.h"
#include "EventoController.h"
#include "global_functions.h"
#include <QMessageBox>

namespace Ui {
class fm_eventos;
}

class fm_eventos : public QDialog
{
    Q_OBJECT

public:
    explicit fm_eventos(QWidget *parent = nullptr);
    ~fm_eventos();

    // MINHAS FUNÇÕES
    void inicializa_fm_eventos();
    void populaTableWidgetEventos(QVector<Evento> listaEventos);
    void limpaFormulario();
    void atualizaTableWidgetEventos();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_excluir_clicked();

    void on_pushButton_cancelar_clicked();

    void on_tableWidget_eventos_itemSelectionChanged();

private:
    Ui::fm_eventos *ui;
};

#endif // FM_EVENTOS_H
