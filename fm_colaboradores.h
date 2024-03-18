#ifndef FM_COLABORADORES_H
#define FM_COLABORADORES_H

#include <QDialog>
#include "Colaborador.h"
#include "global_functions.h"
#include "ColaboradorController.h"
#include "GrupoController.h"
#include <QMessageBox>

namespace Ui {
class fm_colaboradores;
}

class fm_colaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_colaboradores(QWidget *parent = nullptr);
    ~fm_colaboradores();

    // MINHAS FUNÇÕES
    void inicializa_fm_colaboradores();
    void populaTAbleWidgetColaboradoes(QVector<Colaborador> listaColaboradores);
    void atualizaTableWidgetColaboradores();
    void carregaComboGrupos();
    void limpaFormulario();

private slots:
    void on_pushButton_fechar_clicked();

    void on_pushButton_salvar_clicked();

    void on_pushButton_cancelar_clicked();

    void on_tableWidget_colaboradores_itemSelectionChanged();

    void on_pushButton_excluir_clicked();

private:
    Ui::fm_colaboradores *ui;
};

#endif // FM_COLABORADORES_H
