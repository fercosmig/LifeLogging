#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>
#include "Conexao.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class fm_principal;
}
QT_END_NAMESPACE

class fm_principal : public QMainWindow
{
    Q_OBJECT

public:
    fm_principal(QWidget *parent = nullptr);
    ~fm_principal();

    // MINHAS VARIÁVEIS
    QIcon locked, unlocked;
    Conexao conn;

    // MINHAS FUNÇÕES
    void inicializa_fm_principal();
    void verificaLogin();
    void insereLifeLog(QString acao, QString descricao);
    void carregaCombo();
    void populaTableWidget();

private slots:
    void on_pushButton_fechar_clicked();

    void on_actionSobre_triggered();

    void on_actionSair_triggered();

    void on_pushButton_autenticacao_clicked();

    void on_pushButton_inserir_clicked();

    void on_pushButton_pesquisar_clicked();

    void on_pushButton_acao_comum1_clicked();

    void on_pushButton_acao_comum2_clicked();

    void on_pushButton_acao_comum3_clicked();

    void on_comboBox_eventos_currentTextChanged(const QString &arg1);

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
