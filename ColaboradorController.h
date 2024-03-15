#ifndef COLABORADORCONTROLLER_H
#define COLABORADORCONTROLLER_H

#include "Colaborador.h"
#include "Conexao.h"
#include <QVector>
#include <QtSql>
#include <QDebug>

class ColaboradorController{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    ColaboradorController() {}

    // METHODS
    Colaborador autenticaColaborador(QString nomeAcesso, QString senha);
};

Colaborador ColaboradorController::autenticaColaborador(QString nomeAcesso, QString senha)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.nome_acesso, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE tb_colaboradores.nome_acesso = :nome_acesso ";
    sql += "AND tb_colaboradores.senha = :senha";

    Colaborador colaborador;
    Grupo grupo;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome_acesso", nomeAcesso);
        query.bindValue(":senha", senha);

        if(query.exec()){
            if(query.next()){
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setDescricao(query.record().value("descricao").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                colaborador.setNomeAcesso(query.record().value("nome_acesso").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);
                qDebug() << "ColaboradorController.autenticaColaborador() query.next retornou " << colaborador.getNome();
            } else {
                colaborador.setId(0);
                qDebug() << "ColaboradorController.autenticaColaborador() query.next: colaborador não encontrado. Nome ou senha inválidos.";
            }
        } else {
            colaborador.setId(0);
            qDebug() << "ColaboradorController.autenticaColaborador() query.exec: " << query.lastError().text();
        }
    }
    conn.close();
    return colaborador;
}

#endif // COLABORADORCONTROLLER_H
