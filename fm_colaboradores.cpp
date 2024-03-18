#include "fm_colaboradores.h"
#include "ui_fm_colaboradores.h"

fm_colaboradores::fm_colaboradores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_colaboradores)
{
    ui->setupUi(this);

    // CHAMA FUNÇÃO QUE CONFIGURA O FORMULARIO
    inicializa_fm_colaboradores();
}

fm_colaboradores::~fm_colaboradores()
{
    delete ui;
}

/* **************************************************
 * MINHAS FUNÇÕES
 * *************************************************/

void fm_colaboradores::inicializa_fm_colaboradores()
{
    // CRIA CABECALHO PARA O TABLEWIDGET
    QStringList cabecalho {"ID", "Nome", "Nome de acesso", "Grupo"};

    // CHAMA FUNÇÃO QUE CONFIGURA O TABLEWIDGET
    global_functions::tableWidgetFormat(ui->tableWidget_colaboradores, cabecalho);

    // INSERE COLABORADORES NO TABLEWIDGET
    atualizaTableWidgetColaboradores();

    // INSERE GRUPOS NO COMBOBOX
    carregaComboGrupos();

    // ESCONDE O LABEL COM INDEX DA LINHA
    ui->label_numero_da_linha->setVisible(false);
}

void fm_colaboradores::populaTAbleWidgetColaboradoes(QVector<Colaborador> listaColaboradores)
{
    // INSERE COLABORADORES DA LISTA NO TABLEWIDGET
    int contador  = 0;
    ui->tableWidget_colaboradores->setRowCount(0);
    for (Colaborador colaborador : listaColaboradores) {
        ui->tableWidget_colaboradores->insertRow(contador);
        ui->tableWidget_colaboradores->setItem(contador, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(contador, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(contador, 2, new QTableWidgetItem(colaborador.getNomeAcesso()));
        ui->tableWidget_colaboradores->setItem(contador, 3, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
        ui->tableWidget_colaboradores->setRowHeight(contador, 20);
        contador++;
    }
}

void fm_colaboradores::atualizaTableWidgetColaboradores()
{
    // VARIÁVEIS E OBJETOS
    QVector<Colaborador> listaColaboradores;
    ColaboradorController colaborador_controller;

    // GERA LISTA COM TODOS OS COLABORADORES
    listaColaboradores = colaborador_controller.listaTodos();

    // CHAMA A FUNÇÃO PARA POPUPAR O TABLEWIDGET
    populaTAbleWidgetColaboradoes(listaColaboradores);
}

void fm_colaboradores::carregaComboGrupos()
{
    // VARIÁVEIS E OBJETOS
    QVector<Grupo> listaGrupos;
    GrupoController grupo_controller;
    listaGrupos = grupo_controller.listaTodos();

    // LIMPA O COMBOBOX E ADICIONANDO VALOR PADRÃO
    ui->comboBox_grupo->clear();
    ui->comboBox_grupo->addItem("Selecione", 0);

    // PREENCHE O COMBOBOX COM REGISTROS DO BANCO DE DADOS
    for (Grupo grupo : listaGrupos) {
        ui->comboBox_grupo->addItem(grupo.getDescricao(), grupo.getId());
    }
}

void fm_colaboradores::limpaFormulario()
{
    // LIMPA TODOS OS CAMPOS
    ui->lineEdit_id->clear();
    ui->lineEdit_nome->clear();
    ui->lineEdit_nome_de_usuario->clear();
    ui->lineEdit_senha->clear();
    ui->comboBox_grupo->setCurrentIndex(0);
    ui->lineEdit_nome->setFocus();
    ui->pushButton_excluir->setEnabled(false);
}

/* **************************************************
 * SLOTS
 * *************************************************/

void fm_colaboradores::on_pushButton_fechar_clicked()
{
    // FECHA O FORMULÁRIO
    close();
}

void fm_colaboradores::on_pushButton_salvar_clicked()
{
    // VARIÁVEIS E OBJETOS
    int id, id_grupo, row;
    QString nome, nome_acesso, senha;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;
    Grupo grupo;
    GrupoController grupo_controller;

    // RECUPERA OS DADOS DO FORMULÁRIO
    id = ui->lineEdit_id->text().trimmed().toInt();
    nome = ui->lineEdit_nome->text().trimmed();
    nome_acesso = ui->lineEdit_nome_de_usuario->text().trimmed();
    senha = ui->lineEdit_senha->text().trimmed();
    id_grupo = ui->comboBox_grupo->currentData().toInt();

    // VERIFICA SE OS CAMPOS ESTÃO PREENCHIDOS
    if (!global_functions::minCaracter(nome, 3) || !global_functions::minCaracter(nome_acesso, 3) || !global_functions::minCaracter(senha, 3)) {
        QMessageBox::warning(this, "", "Campos devem ter no mínimo 3 caracteres.");
        return;
    }

    // VERIFICA SE FOI SELECIONADO UM GRUPO
    if (id_grupo == 0){
        QMessageBox::warning(this, "", "Selecione um grupo.");
        return;
    }

    // VERIFICA SE É INCLUSÃO OU ALTERAÇÃO DE COLABORADOR
    if (id == 0) { // INCLUIR ***** ***** ***** ***** *****

        // VERIFICA SE O NOME DE USUÁRIO JÁ EXISTE
        if(colaborador_controller.verificaNomeAcessoDuplicado(nome_acesso)){
            QMessageBox::warning(this, "", "Nome de usuário já existe.");
            ui->lineEdit_nome_de_usuario->setFocus();
            return;
        }

        // CRIA OBJETO PARA INSERÇÃO
        grupo = grupo_controller.buscaPorId(id_grupo);
        colaborador.setNome(nome);
        colaborador.setNomeAcesso(nome_acesso);
        colaborador.setSenha(senha);
        colaborador.setGrupo(grupo);

        // INSERE NO BANCO DE DADOS E RECUPERA O ID
        colaborador.setId(colaborador_controller.insere(colaborador));
        qDebug() << "fm_colaboradores::on_pushButton_salvar_clicked() - Colaborador inserido com sucesso. ID: " << colaborador.getId();

        // INSERE NOVO COLABORADOR NO TABLEWIDGET
        row = ui->tableWidget_colaboradores->rowCount();
        ui->tableWidget_colaboradores->insertRow(row);
        ui->tableWidget_colaboradores->setItem(row, 0, new QTableWidgetItem(QString::number(colaborador.getId())));
        ui->tableWidget_colaboradores->setItem(row, 1, new QTableWidgetItem(colaborador.getNome()));
        ui->tableWidget_colaboradores->setItem(row, 2, new QTableWidgetItem(colaborador.getNomeAcesso()));
        ui->tableWidget_colaboradores->setItem(row, 3, new QTableWidgetItem(colaborador.getGrupo().getDescricao()));
        ui->tableWidget_colaboradores->setRowHeight(row, 20);

        // AVISA O USUÁRIO
        QMessageBox::information(this, "", colaborador.getNome() + " inserido com sucesso");

        // LIMPA O FORMULARIO
        limpaFormulario();

    } else { // ALTERAR ***** ***** ***** ***** *****
        colaborador = colaborador_controller.buscaPorId(id);

        // VERIFICA SE O NOME DE USUÁRIO JÁ EXISTE
        if (colaborador.getNomeAcesso() != nome_acesso){
            if(colaborador_controller.verificaNomeAcessoDuplicado(nome_acesso)){
                QMessageBox::warning(this, "", "Nome de usuário já existe.");
                ui->lineEdit_nome_de_usuario->setFocus();
                return;
            }
        }

        // CRIA OBJETO PARA ALTERAÇÃO
        grupo = grupo_controller.buscaPorId(id_grupo);
        colaborador.setNome(nome);
        colaborador.setNomeAcesso(nome_acesso);
        colaborador.setSenha(senha);
        colaborador.setGrupo(grupo);

        // ALTERA NO BANCO DE DADOS
        colaborador_controller.altera(colaborador);

        // RECUPERA O INDEX DA LINHA DO CAMPO HIDDEN
        row = ui->label_numero_da_linha->text().toInt();

        // ALTERA DADOS DO COLABORADOR NO TABLEWIDGET
        ui->tableWidget_colaboradores->item(row, 1)->setText(colaborador.getNome());
        ui->tableWidget_colaboradores->item(row, 2)->setText(colaborador.getNomeAcesso());
        ui->tableWidget_colaboradores->item(row, 3)->setText(colaborador.getGrupo().getDescricao());

        // AVISA O USUÁRIO
        QMessageBox::information(this, "", colaborador.getNome() + " alterado com sucesso");

        // LIMPA O FORMULARIO
        limpaFormulario();
    }
}

void fm_colaboradores::on_pushButton_cancelar_clicked()
{
    limpaFormulario();
}

void fm_colaboradores::on_tableWidget_colaboradores_itemSelectionChanged()
{
    //VARIÁVEIS E OBJETOS
    int row, id, item_combo;
    QString nome, nome_acesso, senha, id_grupo;
    Colaborador colaborador;
    ColaboradorController colaborador_controller;

    // ARMAZENA O INDEX DA LINHA E ID DO COLABORADOR
    row = ui->tableWidget_colaboradores->currentRow();
    id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();

    // RECUPERA O COLABORADOR
    colaborador = colaborador_controller.buscaPorId(id);

    // COLOCANDO OS DADOS DO COLABORADOR NOS CAMPOS
    ui->lineEdit_id->setText(QString::number(colaborador.getId()));
    ui->lineEdit_nome->setText(colaborador.getNome());
    ui->lineEdit_nome_de_usuario->setText(colaborador.getNomeAcesso());
    ui->lineEdit_senha->setText(colaborador.getSenha());
    item_combo = ui->comboBox_grupo->findData(colaborador.getGrupo().getId());
    ui->comboBox_grupo->setCurrentIndex(item_combo);

    // GUARDA O INDEX DA LINHA EM UM CAMPO HIDDEN
    ui->label_numero_da_linha->setText(QString::number(row));

    // HABILITA O BOTÃO EXCLUIR
    if (id != global_variables::colaboradorLogado.getId())
        ui->pushButton_excluir->setEnabled(true);
    else
        ui->pushButton_excluir->setEnabled(false);
}

void fm_colaboradores::on_pushButton_excluir_clicked()
{

    // VARIÁVEIS E OBJETOS
    int row, id;
    QMessageBox::StandardButton resposta;
    ColaboradorController colaborador_controller;

    // RECUPERA O INDEX DA LINHA DO CAMPO HIDDEN
    row = ui->label_numero_da_linha->text().toInt();

    // PERGUNTA SE O USUÁRIO TEM CERTEZA
    resposta = QMessageBox::question(this, "", "Tem certeza que deseja excluir?", QMessageBox::Yes | QMessageBox::No);
    if (resposta == QMessageBox::Yes) {

        // RECUPERA O ID DO USUÁRIO DO TABLEWIDGET
        id = ui->tableWidget_colaboradores->item(row, 0)->text().toInt();

        // EXCLUI COLABORADOR DO BANCO DE DADOS
        colaborador_controller.remove(id);

        // REMOVE A LINHA DO TABLEWIDGET
        ui->tableWidget_colaboradores->removeRow(row);
    }
}

