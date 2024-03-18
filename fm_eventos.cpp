#include "fm_eventos.h"
#include "ui_fm_eventos.h"

fm_eventos::fm_eventos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_eventos)
{
    ui->setupUi(this);

    // CHAMA FUNÇÃO QUE CONFIGURA O FORMULARIO
    inicializa_fm_eventos();
}

fm_eventos::~fm_eventos()
{
    delete ui;
}

/* **************************************************
 * MINHAS FUNÇÕES
 * *************************************************/

void fm_eventos::inicializa_fm_eventos()
{
    // CRIA CABECALHO PARA O TABLEWIDGET
    QStringList cabecalho{"ID", "Título", "Descrição"};

    // CHAMA FUNÇÃO QUE CONFIGURA O TABLEWIDGET
    global_functions::tableWidgetFormat(ui->tableWidget_eventos,cabecalho);

    // TRANSFORMANDO O LABEL EM CAMPO HIDDEN
    ui->label_numero_da_linha->setVisible(false);

    // INSERE EVENTOS NO TABLEWIDGET
    atualizaTableWidgetEventos();
}

void fm_eventos::populaTableWidgetEventos(QVector<Evento> listaEventos)
{
    // INSERE EVENTOS DA LISTA NO TABLEWIDGET
    ui->tableWidget_eventos->setRowCount(0);
    int contador = 0;
    for (Evento evento : listaEventos) {
        ui->tableWidget_eventos->insertRow(contador);
        ui->tableWidget_eventos->setItem(contador, 0, new QTableWidgetItem(QString::number(evento.getId())));
        ui->tableWidget_eventos->setItem(contador, 1, new QTableWidgetItem(evento.getTitulo()));
        ui->tableWidget_eventos->setItem(contador, 2, new QTableWidgetItem(evento.getDescricao()));
        ui->tableWidget_eventos->setRowHeight(contador, 20);
        contador ++;
    }
}

void fm_eventos::limpaFormulario()
{
    // LIMPA TODOS OS CAMPOS
    ui->lineEdit_id->clear();
    ui->lineEdit_titulo->clear();
    ui->lineEdit_descricao->clear();
    ui->lineEdit_titulo->setFocus();
    ui->pushButton_excluir->setEnabled(false);
}

void fm_eventos::atualizaTableWidgetEventos()
{
    // VARIÁVEIS E OBJETOS
    QVector<Evento> listaEventos;
    EventoController evento_controller;

    // GERA LISTA COM TODOS OS EVENTOS
    listaEventos = evento_controller.listaTodos();

    // CHAMA A FUNÇÃO PARA POPUPAR O TABLEWIDGET
    populaTableWidgetEventos(listaEventos);
}
/* **************************************************
 * SLOTS
 * *************************************************/

void fm_eventos::on_pushButton_fechar_clicked()
{
    // FECHA O FORMULÁRIO
    close();
}


void fm_eventos::on_pushButton_salvar_clicked()
{
    // VARIÁVEIS E OBJETOS
    int id, row;
    QString titulo, descricao;
    Evento evento;
    EventoController evento_controller;

    // RECUPERA OS DADOS DO FORMULÁRIO
    id = ui->lineEdit_id->text().trimmed().toInt();
    titulo = ui->lineEdit_titulo->text().trimmed().toLower();
    descricao = ui->lineEdit_descricao->text().trimmed();

    if(titulo == "outro" || titulo == "água" || titulo == "fumar" || titulo == "peidar"){
        QMessageBox::warning(this, "", "Titulo não pode ser usado.");
        ui->lineEdit_titulo->clear();
        ui->lineEdit_titulo->setFocus();
        return;
    }

    // VERIFICA SE OS CAMPOS ESTÃO PREENCHIDOS
    if (!global_functions::minCaracter(titulo, 3) || !global_functions::minCaracter(descricao, 3)) {
        QMessageBox::warning(this, "", "Campos devem ter no mínimo 3 caracteres.");
        return;
    }

    // VERIFICA SE É INCLUSÃO OU ALTERAÇÃO DE EVENTO
    if (id == 0) { // INCLUSAO DE EVENTO ***** ***** *****

        // CRIA O OBJETO
        evento.setTitulo(titulo);
        evento.setDescricao(descricao);

        // INSERE NO BANCO DE DADOS
        evento.setId(evento_controller.insere(evento));
        qDebug() << evento.getId();

        //LIMPA CAMPOS DO FORMULARIO
        limpaFormulario();

        //ATUALIZA O TABLEWIDGET
        row = ui->tableWidget_eventos->rowCount();
        ui->tableWidget_eventos->insertRow(row);
        ui->tableWidget_eventos->setItem(row, 0, new QTableWidgetItem(QString::number(evento.getId())));
        ui->tableWidget_eventos->setItem(row, 1, new QTableWidgetItem(evento.getTitulo()));
        ui->tableWidget_eventos->setItem(row, 2, new QTableWidgetItem(evento.getDescricao()));
        ui->tableWidget_eventos->setRowHeight(row, 20);

        // AVISA O USUÁRIO
        QMessageBox::information(this, "", QString::number(evento.getId()) + "-" + evento.getDescricao() + " inserido com sucesso.");

    } else { // ALTERAÇÃO DE EVENTO ***** ***** *****

        // CRIA O OBJETO
        evento.setId(id);
        evento.setTitulo(titulo);
        evento.setDescricao(descricao);

        // ALTERA NO BANCO DE DADOS
        evento_controller.altera(evento);

        //LIMPA CAMPOS DO FORMULARIO
        limpaFormulario();

        //ATUALIZA O TABLEWIDGET
        // RECUPERA O INDEX DA LINHA DO CAMPO HIDDEN
        row = ui->label_numero_da_linha->text().toInt();

        // ALTERA DADOS DO COLABORADOR NO TABLEWIDGET
        ui->tableWidget_eventos->item(row, 1)->setText(evento.getTitulo());
        ui->tableWidget_eventos->item(row, 2)->setText(evento.getDescricao());

        // AVISA O USUÁRIO
        QMessageBox::information(this, "", evento.getDescricao() + " alterado com sucesso.");
    }
}

void fm_eventos::on_pushButton_excluir_clicked()
{
    // VARIÁVEIS E OBJETOS
    int row, id;
    QMessageBox::StandardButton resposta;
    EventoController evento_controller;

    // PERGUNTA SE O USUÁRIO TEM CERTEZA
    resposta = QMessageBox::question(this, "", "Tem certeza que deseja excluir?", QMessageBox::Yes | QMessageBox::No);
    if (resposta == QMessageBox::Yes) {
        row = ui->tableWidget_eventos->currentRow();
        id = ui->tableWidget_eventos->item(row, 0)->text().toInt();
        evento_controller.remove(id);
        ui->tableWidget_eventos->removeRow(row);
        limpaFormulario();
    }
}

void fm_eventos::on_pushButton_cancelar_clicked()
{
    limpaFormulario();
}


void fm_eventos::on_tableWidget_eventos_itemSelectionChanged()
{
    // VARIÁVEIS E OBJETOS
    int id, row;
    QString titulo, descricao;

    // RECUPERA A LINHA SELECIONADA
    row = ui->tableWidget_eventos->currentRow();

    // VERIFICA SE É O ITEM PADRÃO
    id = ui->tableWidget_eventos->item(row, 0)->text().toInt();
    if (id <= 4){
        limpaFormulario();
        return;
    }

    // INSERE O NUMERO DA LINHA NO CAMPO HIDDEN
    ui->label_numero_da_linha->setText(QString::number(row));

    // ARMAZENA OS VALORES DA LINHA SELECIONADA
    id = ui->tableWidget_eventos->item(row, 0)->text().toInt();
    titulo = ui->tableWidget_eventos->item(row, 1)->text();
    descricao = ui->tableWidget_eventos->item(row, 2)->text();

    // COLOCA OS VALORES DA LINHA NOS CAMPOS
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_titulo->setText(titulo);
    ui->lineEdit_descricao->setText(descricao);

    ui->pushButton_excluir->setEnabled(true);
}
