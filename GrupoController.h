#ifndef GRUPOCONTROLLER_H
#define GRUPOCONTROLLER_H

#include <QString>
#include "Grupo.h"
#include <QtSql>
#include <QDebug>
#include <QVector>
#include "Conexao.h"

class GrupoController{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;
protected:
public:
    // CONSTRUCTOR
    GrupoController() {}

    // METHODS
    QVector<Grupo> listaTodos();
    Grupo buscaPorId(int id);
};

QVector<Grupo> GrupoController::listaTodos()
{
    sql = "SELECT ";
    sql += "tb_grupos.id, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_grupos";

    int i = 0;
    Grupo grupo;
    QVector<Grupo> ListaGrupos;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);

        if(query.exec()){
            if(query.next()){
                do {
                    grupo.setId(query.record().value("id").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());
                    ListaGrupos.push_back(grupo);
                    i++;
                } while(query.next());
            }
            qDebug() << "GrupoController.listaTodos() query.exec retornou " << i << " registros.";
        } else {
            qDebug() << "GrupoController.listaTodos() query.exec: " << query.lastError().text();
        }
    }
    conn.close();
    return ListaGrupos;
}

Grupo GrupoController::buscaPorId(int id_grupo)
{
    sql = "SELECT ";
    sql += "tb_grupos.id, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_grupos ";
    sql += "WHERE tb_grupos.id = :id";

    Grupo grupo;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", id_grupo);

        if(query.exec()){
            if(query.next()){
                grupo.setId(query.record().value("id").toInt());
                grupo.setDescricao(query.record().value("descricao").toString());
                grupo.setSigla(query.record().value("sigla").toString());
                qDebug() << "GrupoController.buscaPorId() query.exec retornou: " << grupo.getDescricao();
            } else
                qDebug() << "GrupoController.buscaPorId() 0 registros.";
        } else
            qDebug() << "GrupoController.buscaPorId() query.exec: " << query.lastError().text();
    }
    conn.close();
    return grupo;
}

#endif // GRUPOCONTROLLER_H
