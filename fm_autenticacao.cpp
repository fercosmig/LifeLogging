#include "fm_autenticacao.h"
#include "ui_fm_autenticacao.h"

fm_autenticacao::fm_autenticacao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_autenticacao)
{
    ui->setupUi(this);

    // CHAMA FUNÇÃO QUE INICIALIZA O FORMULARIO
    inicializa_fm_autenticacao();
}

fm_autenticacao::~fm_autenticacao()
{
    delete ui;
}

/* **************************************************
 * MINHAS FUNÇÕES
 * *************************************************/

void fm_autenticacao::limpa_formulario(){

    //LIMPA OS CAMPOS DO FORMULÁRIO
    ui->lineEdit_nome_acesso->clear();
    ui->lineEdit_senha->clear();
    ui->lineEdit_nome_acesso->setFocus();
}

void fm_autenticacao::inicializa_fm_autenticacao()
{
    /*
    // GAMBIARRA
    ui->lineEdit_nome_acesso->setText("fercosmig");
    ui->lineEdit_senha->setText("123");
    */
}

/* **************************************************
 * SLOTS
 * *************************************************/

void fm_autenticacao::on_pushButton_fechar_clicked()
{
    // FECHA O FORMULARIO
    close();
}


void fm_autenticacao::on_pushButton_autenticar_clicked()
{
    // VARIÁVEIS E OBJETOS
    QString nomeAcesso, senha;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;

    //RECUPERA DADOS DO FORMULARIO
    nomeAcesso = ui->lineEdit_nome_acesso->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();

    // VERIFICA SE FOI DIGITADO ALGO COM PELO MENOS 3 CARACTERES
    if(global_functions::minCaracter(nomeAcesso, 3) && global_functions::minCaracter(senha, 3)){

        // EXECUTA A AUTENTICAÇÃO DO COLABORADOR
        colaborador = colaborador_controller.autenticaColaborador(nomeAcesso, senha);

        // SETA AS VARIÁVEIS GLOBAIS
        if (colaborador.getId() > 0){
            global_variables::colaboradorLogado = colaborador;
            global_variables::isLogged = true;
        } else {
            QMessageBox::warning(this,"","Nome de acesso ou senha inválidos");
            limpa_formulario();
            return;
        }
    } else {
        QMessageBox::warning(this,"","Nome de acesso e senha precisam de no mínimo 3 caracteres.");
        limpa_formulario();
        return;
    }
    close();
}
