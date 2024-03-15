#ifndef LIFELOGCONTROLLER_H
#define LIFELOGCONTROLLER_H

#include <QString>
#include "LifeLog.h"
#include <QtSql>
#include <QDebug>
#include <QVector>
#include "Conexao.h"

class LifeLogController{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    LifeLogController () {}

    // METHODS CRUD - Create Read Update Delete
    void insere(LifeLog lifeLog);
    QVector<LifeLog> listaPorColaboradorPeriodoPesquisa(int id_colaborador, QString data_inicial, QString data_final, QString descricao);
    QVector<LifeLog> listaPorColaboradorPeriodo(int id_colaborador, QString data_inicial, QString data_final);
    void altera(LifeLog lifeLog);
    void remove(int id);
};

void LifeLogController::insere(LifeLog lifeLog)
{
    sql = "INSERT INTO tb_life_log ( descricao, id_evento, id_colaborador ) ";
    sql += "VALUES ( :descricao, :id_evento, :id_colaborador )";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":descricao", lifeLog.getDescricao());
        query.bindValue(":id_evento", lifeLog.getEvento().getId());
        query.bindValue(":id_colaborador", lifeLog.getColaborador().getId());

        if (query.exec()){
            qDebug() << "LifeLogController.insere() query.exec: " << lifeLog.getEvento().getTitulo() <<  " inserido com sucesso!";
        } else
            qDebug() << "LifeLogController.insere() query.exec: " << query.lastError().text();
    }
    conn.close();
}

QVector<LifeLog> LifeLogController::listaPorColaboradorPeriodoPesquisa(int id_colaborador, QString data_inicial, QString data_final, QString descricao)
{
    sql = "SELECT ";
    sql += "tb_life_log.id, ";
    sql += "tb_life_log.data, ";
    sql += "tb_life_log.hora, ";
    sql += "tb_life_log.descricao, ";
    sql += "tb_eventos.id as id_evento, ";
    sql += "tb_eventos.titulo, ";
    sql += "tb_eventos.descricao as descricao_evento, ";
    sql += "tb_colaboradores.id as id_colaborador, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.nome_acesso, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.descricao as descricao_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_life_log ";
    sql += "INNER JOIN tb_eventos ON tb_life_log.id_evento = tb_eventos.id ";
    sql += "INNER JOIN tb_colaboradores ON tb_life_log.id_colaborador = tb_colaboradores.id ";
    sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE tb_life_log.data BETWEEN :data_inicial AND :data_final ";
    sql += "AND ( tb_eventos.descricao LIKE :descricao ";
    sql += "OR tb_life_log.descricao LIKE :descricao ) ";
    sql += "AND tb_colaboradores.id = :id_colaborador ";
    sql += "ORDER BY tb_life_log.data, tb_life_log.hora ASC";

    int i = 0;
    QVector<LifeLog> listaLifeLog;
    Grupo grupo;
    Colaborador colaborador;
    Evento evento;
    LifeLog life_log;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":data_inicial", data_inicial);
        query.bindValue(":data_final", data_final);
        query.bindValue(":descricao", "%" + descricao + "%");
        query.bindValue(":id_colaborador", id_colaborador);

        if (query.exec()){
            if(query.next()){
                do{
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id_colaborador").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setNomeAcesso(query.record().value("nome_acesso").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    evento.setId(query.record().value("id_evento").toInt());
                    evento.setTitulo(query.record().value("titulo").toString());
                    evento.setDescricao(query.record().value("descricao_evento").toString());

                    life_log.setId(query.record().value("id").toInt());
                    life_log.setData(query.record().value("data").toString());
                    life_log.setHora(query.record().value("hora").toString());
                    life_log.setDescricao(query.record().value("descricao").toString());
                    life_log.setEvento(evento);
                    life_log.setColaborador(colaborador);

                    listaLifeLog.push_back(life_log);
                    i++;
                } while (query.next());
                qDebug() << "LifeLogController.listaPorColaboradorPeriodoPesquisa() query.exec: " << i << " registros.";
            } else
                qDebug() << "LifeLogController.listaPorColaboradorPeriodoPesquisa() query.exec: 0 registros.";
        } else
            qDebug() << "LifeLogController.listaPorColaboradorPeriodoPesquisa() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaLifeLog;
}

QVector<LifeLog> LifeLogController::listaPorColaboradorPeriodo(int id_colaborador, QString data_inicial, QString data_final)
{
    sql = "SELECT ";
    sql += "tb_life_log.id, ";
    sql += "tb_life_log.data, ";
    sql += "tb_life_log.hora, ";
    sql += "tb_life_log.descricao, ";
    sql += "tb_eventos.id as id_evento, ";
    sql += "tb_eventos.titulo, ";
    sql += "tb_eventos.descricao as descricao_evento, ";
    sql += "tb_colaboradores.id as id_colaborador, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.nome_acesso, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.descricao as descricao_grupo, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_life_log ";
    sql += "INNER JOIN tb_eventos ON tb_life_log.id_evento = tb_eventos.id ";
    sql += "INNER JOIN tb_colaboradores ON tb_life_log.id_colaborador = tb_colaboradores.id ";
    sql += "INNER JOIN tb_grupos ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE tb_life_log.data BETWEEN :data_inicial AND :data_final ";
    sql += "AND tb_colaboradores.id = :id_colaborador ";
    sql += "ORDER BY tb_life_log.data, tb_life_log.hora ASC";

    int i = 0;
    QVector<LifeLog> listaLifeLog;
    Grupo grupo;
    Colaborador colaborador;
    Evento evento;
    LifeLog life_log;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":data_inicial", data_inicial);
        query.bindValue(":data_final", data_final);
        query.bindValue(":id_colaborador", id_colaborador);

        if (query.exec()){
            if(query.next()){
                do{
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao_grupo").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id_colaborador").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setNomeAcesso(query.record().value("nome_acesso").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    evento.setId(query.record().value("id_evento").toInt());
                    evento.setTitulo(query.record().value("titulo").toString());
                    evento.setDescricao(query.record().value("descricao_evento").toString());

                    life_log.setId(query.record().value("id").toInt());
                    life_log.setData(query.record().value("data").toString());
                    life_log.setHora(query.record().value("hora").toString());
                    life_log.setDescricao(query.record().value("descricao").toString());
                    life_log.setEvento(evento);
                    life_log.setColaborador(colaborador);

                    listaLifeLog.push_back(life_log);
                    i++;
                } while (query.next());
                qDebug() << "LifeLogController.listaPorColaboradorPeriodo() query.exec: " << i << " registros.";
            } else
                qDebug() << "LifeLogController.listaPorColaboradorPeriodo() query.exec: 0 registros.";
        } else
            qDebug() << "LifeLogController.listaPorColaboradorPeriodo() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaLifeLog;
}

void LifeLogController::altera(LifeLog lifeLog)
{
    sql ="UPDATE tb_life_log SET ";
    sql += "tb_life_log.data = :data, ";
    sql += "tb_life_log.hora = :hora, ";
    sql += "tb_life_log.descricao = :descricao, ";
    sql += "tb_life_log.id_evento = :id_evento, ";
    sql += "tb_life_log.id_colaborador = :id_colaborador ";
    sql += "WHERE tb_life_log.id = :id";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":data", lifeLog.getData());
        query.bindValue(":hora", lifeLog.getHora());
        query.bindValue(":descricao", lifeLog.getDescricao());
        query.bindValue(":id_evento", lifeLog.getEvento().getId());
        query.bindValue(":id_colaborador", lifeLog.getColaborador().getId());

        if(!query.exec())
            qDebug() << "LifeLogController.altera() query.exec: " << query.lastError().text();
    }
    conn.close();
}

void LifeLogController::remove(int id_life_log)
{
    sql ="DELETE FROM tb_life_log WHERE id = :id";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", id_life_log);

        if(!query.exec())
            qDebug() << "LifeLogController.remove() query.exec: " << query.lastError().text();
    }
    conn.close();
}

#endif // LIFELOGCONTROLLER_H
