#ifndef EVENTOCONTROLLER_H
#define EVENTOCONTROLLER_H

#include <QString>
#include "Evento.h"
#include <QtSql>
#include <QDebug>
#include <QVector>
#include "Conexao.h"

class EventoController{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;
protected:
public:
    // CONSTRUCTOR
    EventoController() {}

    // METHODS CRUD - Create Read Update Delete
    QVector<Evento> listaTodos();
    Evento buscaPorId(int id);
    Evento buscaPorTitulo(QString titulo);
};

QVector<Evento> EventoController::listaTodos()
{
    sql = "SELECT ";
    sql += "tb_eventos.id, ";
    sql += "tb_eventos.titulo, ";
    sql += "tb_eventos.descricao ";
    sql += "FROM tb_eventos ";
    sql += "ORDER BY tb_eventos.descricao ASC";

    int i = 0;
    Evento evento;
    QVector<Evento> ListaEventos;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);

        if(query.exec()){
            if(query.next()){
                do {
                    evento.setId(query.record().value("id").toInt());
                    evento.setTitulo(query.record().value("titulo").toString());
                    evento.setDescricao(query.record().value("descricao").toString());
                    ListaEventos.push_back(evento);
                    i++;
                } while(query.next());
            }
            qDebug() << "EventoController.listaTodos() query.exec retornou " << i << " registros.";
        } else {
            qDebug() << "EventoController.listaTodos() query.exec: " << query.lastError().text();
        }
    }
    conn.close();
    return ListaEventos;
}

Evento EventoController::buscaPorId(int id_evento)
{
    sql = "SELECT ";
    sql += "tb_eventos.id, ";
    sql += "tb_eventos.titulo, ";
    sql += "tb_eventos.descricao ";
    sql += "FROM tb_eventos ";
    sql += "WHERE tb.eventos.id = :id";

    Evento evento;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", id_evento);

        if(query.exec()){
            if(query.next()){
                evento.setId(query.record().value("id").toInt());
                evento.setTitulo(query.record().value("titulo").toString());
                evento.setDescricao(query.record().value("descricao").toString());
                qDebug() << "EventoController.buscaPorId() query.exec retornou : " << evento.getDescricao();
            } else
                qDebug() << "EventoController.buscaPorId() 0 registros.";
        } else
            qDebug() << "EventoController.buscaPorId() query.exec: " << query.lastError().text();
    }
    conn.close();
    return evento;
}

Evento EventoController::buscaPorTitulo(QString titulo)
{
    titulo = titulo.toLower();

    sql = "SELECT ";
    sql += "tb_eventos.id, ";
    sql += "tb_eventos.titulo, ";
    sql += "tb_eventos.descricao ";
    sql += "FROM tb_eventos ";
    sql += "WHERE tb_eventos.titulo = :titulo";

    Evento evento;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":titulo", titulo);

        if(query.exec()){
            if(query.next()){
                evento.setId(query.record().value("id").toInt());
                evento.setTitulo(query.record().value("titulo").toString());
                evento.setDescricao(query.record().value("descricao").toString());
                qDebug() << "EventoController.buscaPorTitulo() query.exec retornou : " << evento.getDescricao();
            } else
                qDebug() << "EventoController.buscaPorTitulo() 0 registros.";
        } else
            qDebug() << "EventoController.buscaPorTitulo() query.exec: " << query.lastError().text();
    }
    conn.close();
    return evento;
}

#endif // EVENTOCONTROLLER_H
