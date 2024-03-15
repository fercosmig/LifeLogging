#include "fm_principal.h"
#include <QMessageBox>
#include <QVector>
#include "Colaborador.h"
#include "Evento.h"
#include "EventoController.h"
#include "LifeLogController.h"
#include "global_variables.h"
#include "global_functions.h"
#include "fm_autenticacao.h"
#include "fm_sobre.h"
#include "ui_fm_principal.h"

fm_principal::fm_principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::fm_principal)
{
    ui->setupUi(this);

    inicializa_fm_principal();
}

fm_principal::~fm_principal()
{
    delete ui;
}

// *******************************************************
// MY FUNCTIONS
// *******************************************************

void fm_principal::inicializa_fm_principal()
{
    QString local_db = qApp->applicationDirPath();
    QString nome_db = "/db/lifelogging.db";
    QString banco = local_db + nome_db;
    global_variables::bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    global_variables::bancoDeDados.setDatabaseName(banco);

    locked.addFile(":/icons/images/locked.png");
    unlocked.addFile(":/icons/images/unlocked.png");
    ui->pushButton_autenticacao->setText("");
    ui->label_logado->setText("");
    ui->statusbar->addWidget(ui->pushButton_autenticacao);
    ui->statusbar->addWidget(ui->label_logado);

    QDate di, df;
    df = QDate::currentDate();
    di.setDate(df.year(), df.month(), 1);
    ui->dateEdit_data_inicial->setDate(di);
    ui->dateEdit_data_final->setDate(df);

    QStringList cabecalho{"ID","Data","Hora","Evento", "Descrição"};
    global_functions::tableWidgetFormat(ui->tableWidget_life_log, cabecalho);

    if(global_variables::isLogged){
        populaTableWidget();
    }

    carregaCombo();
    verificaLogin();
}

void fm_principal::verificaLogin()
{
    if(global_variables::isLogged){

        QString str;

        ui->pushButton_autenticacao->setIcon(unlocked);

        str = global_variables::colaboradorLogado.getGrupo().getSigla();
        str += " | ";
        str += global_variables::colaboradorLogado.getNome();

        ui->label_logado->setText(str);
    } else {
        ui->pushButton_autenticacao->setIcon(locked);
        ui->label_logado->setText("");
    }
}

void fm_principal::insereLifeLog(QString acao, QString descricao)
{
    Evento evento;
    LifeLog life_log;
    Colaborador colaborador;
    LifeLogController life_log_controller;
    EventoController evento_controller;

    evento = evento_controller.buscaPorTitulo(acao);
    colaborador = global_variables::colaboradorLogado;

    life_log.setDescricao(descricao);
    life_log.setEvento(evento);
    life_log.setColaborador(colaborador);

    life_log_controller.insere(life_log);
}

void fm_principal::carregaCombo()
{
    ui->comboBox_eventos->clear();
    ui->comboBox_eventos->addItem("Selecione...", 0);

    QVector<Evento> listaEventos;
    EventoController evento_controller;

    listaEventos = evento_controller.listaTodos();

    for(Evento evento : listaEventos) {
        ui->comboBox_eventos->addItem(evento.getDescricao(), evento.getTitulo());
    }
}

void fm_principal::populaTableWidget()
{
    int id_colaborador;
    QString data_inicial, data_final, descricao;

    id_colaborador = global_variables::colaboradorLogado.getId();
    data_inicial = ui->dateEdit_data_inicial->date().toString("yyyy-MM-dd");
    data_final = ui->dateEdit_data_final->date().toString("yyyy-MM-dd");
    descricao = ui->lineEdit_pesquisar->text().trimmed();

    QVector<LifeLog> listaLifeLog;
    LifeLogController life_log_controller;

    if (descricao == "")
        listaLifeLog = life_log_controller.listaPorColaboradorPeriodo(id_colaborador, data_inicial, data_final);
    else {
        if(global_functions::minCaracter(descricao, 3))
            listaLifeLog = life_log_controller.listaPorColaboradorPeriodoPesquisa(id_colaborador, data_inicial, data_final, descricao);
        else {
            QMessageBox::warning(this,"","Campo pesquisa deve ter no mínimo 3 caracteres.");
            return;
        }
    }

    ui->tableWidget_life_log->setRowCount(0);
    int contador = 0;
    for(LifeLog life_log : listaLifeLog){
        ui->tableWidget_life_log->insertRow(contador);
        ui->tableWidget_life_log->setItem(contador, 0, new QTableWidgetItem(QString::number(life_log.getId())));
        ui->tableWidget_life_log->setItem(contador, 1, new QTableWidgetItem(life_log.getData()));
        ui->tableWidget_life_log->setItem(contador, 2, new QTableWidgetItem(life_log.getHora()));
        ui->tableWidget_life_log->setItem(contador, 3, new QTableWidgetItem(life_log.getEvento().getDescricao()));
        ui->tableWidget_life_log->setItem(contador, 4, new QTableWidgetItem(life_log.getDescricao()));
        ui->tableWidget_life_log->setRowHeight(contador, 20);
    }
}

// *******************************************************
// SLOTS
// *******************************************************

void fm_principal::on_pushButton_fechar_clicked()
{
    QApplication::quit();
}

void fm_principal::on_actionSobre_triggered()
{
            fm_sobre f_sobre;
            f_sobre.exec();
}

void fm_principal::on_actionSair_triggered()
{
    QApplication::quit();
}

void fm_principal::on_pushButton_autenticacao_clicked()
{
    fm_autenticacao f_autenticacao;

    if(global_variables::isLogged){
        global_variables::isLogged = false;
        ui->tableWidget_life_log->setRowCount(0);
        verificaLogin();
    } else {
        f_autenticacao.exec();
        if(global_variables::isLogged){
            verificaLogin();
            populaTableWidget();
        }
    }
}

void fm_principal::on_pushButton_inserir_clicked()
{
    if(global_variables::isLogged){

        QString acao, descricao;
        acao = ui->comboBox_eventos->currentData().toString();

        if (acao == "outro") {
            descricao = ui->lineEdit_outro->text();
            if (!global_functions::minCaracter(descricao, 3)){
                QMessageBox::warning(this,"","Outro: mínimo de 3 caracteres.");
                return;
            }
        } else
            descricao = "";

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this,"","Tem certeza?", QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::Yes){
            insereLifeLog(acao, descricao);
            populaTableWidget();
        }
    } else
        QMessageBox::warning(this,"","Você não está logado. Favor efetuar o login!");

    ui->lineEdit_outro->clear();
}

void fm_principal::on_pushButton_pesquisar_clicked()
{
    if(global_variables::isLogged){

        populaTableWidget();
        ui->lineEdit_pesquisar->clear();
        ui->lineEdit_pesquisar->setFocus();

    } else
        QMessageBox::warning(this,"","Você não está logado. Favor efetuar o login!");
}

void fm_principal::on_pushButton_acao_comum1_clicked()
{
    if(global_variables::isLogged){

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this,"","Tem certeza?", QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::Yes){
            QString acao;
            acao = "água";
            insereLifeLog(acao, "");
            populaTableWidget();
        }

    } else
        QMessageBox::warning(this,"","Você não está logado. Favor efetuar o login!");
}

void fm_principal::on_pushButton_acao_comum2_clicked()
{
    if(global_variables::isLogged){

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this,"","Tem certeza?", QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::Yes){
            QString acao;
            acao = "peidar";
            insereLifeLog(acao, "");
            populaTableWidget();
        }
    } else
        QMessageBox::warning(this,"","Você não está logado. Favor efetuar o login!");
}

void fm_principal::on_pushButton_acao_comum3_clicked()
{
    if(global_variables::isLogged){

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this,"","Tem certeza?", QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::Yes){
            QString acao;
            acao = "fumar";
            insereLifeLog(acao, "");
            populaTableWidget();
        }
    } else
        QMessageBox::warning(this,"","Você não está logado. Favor efetuar o login!");
}


void fm_principal::on_comboBox_eventos_currentTextChanged(const QString &arg1)
{
    QString titulo;
    titulo = ui->comboBox_eventos->currentData().toString();
    if (titulo == "outro") {
        ui->lineEdit_outro->setEnabled(true);
        ui->lineEdit_outro->setFocus();
    } else {
        ui->lineEdit_outro->clear();
        ui->lineEdit_outro->setEnabled(false);
    }
}

