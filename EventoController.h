/* *****************************************
 * Fernando Costa Migliorini
 * 2024-03-11
 * LifeLogging
 * EventoController.h
 * *****************************************/

#ifndef EVENTOCONTROLLER_H
#define EVENTOCONTROLLER_H

#include "Conexao.h"
#include <QVector>
#include "Evento.h"

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
    int insere(Evento evento);
    QVector<Evento> listaTodos();
    Evento buscaPorId(int id);
    Evento buscaPorTitulo(QString titulo);
    void altera(Evento evento);
    void remove(int id_evento);
};

inline int EventoController::insere(Evento evento)
{
    sql = "INSERT INTO tb_eventos ( titulo, descricao ) ";
    sql += "VALUES ( :titulo, :descricao )";

    int retorno = 0;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":titulo", evento.getTitulo());
        query.bindValue(":descricao", evento.getDescricao());

        if (query.exec()){
            sql = "SELECT id FROM tb_eventos ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if(query.exec()){
                if (query.next()){
                    retorno = query.record().value("id").toInt();
                }
            }
            qDebug() << "EventoController.insere() query.exec: " << evento.getTitulo() <<  " inserido com sucesso!";
        } else
            qDebug() << "EventoController.insere() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline QVector<Evento> EventoController::listaTodos()
{
    sql = "SELECT id, titulo, descricao ";
    sql += "FROM tb_eventos ";
    sql += "ORDER BY descricao ASC";

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

inline Evento EventoController::buscaPorId(int id_evento)
{
    sql = "SELECT id, titulo, descricao ";
    sql += "FROM tb_eventos ";
    sql += "WHERE id = :id";

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

inline Evento EventoController::buscaPorTitulo(QString titulo)
{
    titulo = titulo.toLower();

    sql = "SELECT id, titulo, descricao ";
    sql += "FROM tb_eventos ";
    sql += "WHERE titulo = :titulo";

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

inline void EventoController::altera(Evento evento)
{
    sql ="UPDATE tb_eventos SET ";
    sql += "titulo = :titulo, ";
    sql += "descricao = :descricao ";
    sql += "WHERE id = :id";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":titulo", evento.getTitulo());
        query.bindValue(":descricao", evento.getDescricao());
        query.bindValue(":id", evento.getId());

        if(query.exec())
            qDebug() << "EventoController.altera() query.exec: " << evento.getDescricao() << " alterado com sucesso.";
        else
            qDebug() << "EventoController.altera() query.exec: " << query.lastError().text();
    }
    conn.close();
}

inline void EventoController::remove(int id_evento)
{
    sql ="DELETE FROM tb_eventos WHERE id = :id";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", id_evento);

        if(!query.exec())
            qDebug() << "EventoController.remove() query.exec: " << query.lastError().text();
    }
    conn.close();
}

#endif // EVENTOCONTROLLER_H
