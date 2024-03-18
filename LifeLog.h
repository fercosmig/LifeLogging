/* *****************************************
 * Fernando Costa Migliorini
 * 2024-03-11
 * LifeLogging
 * LifeLog.h
 * *****************************************/

#ifndef LIFELOG_H
#define LIFELOG_H

#include "Evento.h"
#include "Colaborador.h"

class LifeLog{
private:
    int id;
    QString data;
    QString hora;
    QString descricao;
    Evento evento;
    Colaborador colaborador;

protected:
public:
    // CONSTRUCTOR
    LifeLog() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getData() const;
    void setData(const QString &newData);
    QString getHora() const;
    void setHora(const QString &newHora);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
    Evento getEvento() const;
    void setEvento(const Evento &newEvento);
    Colaborador getColaborador() const;
    void setColaborador(const Colaborador &newColaborador);
};

inline int LifeLog::getId() const
{
    return id;
}

inline void LifeLog::setId(int newId)
{
    id = newId;
}

inline QString LifeLog::getData() const
{
    return data;
}

inline void LifeLog::setData(const QString &newData)
{
    data = newData;
}

inline QString LifeLog::getHora() const
{
    return hora;
}

inline void LifeLog::setHora(const QString &newHora)
{
    hora = newHora;
}

inline QString LifeLog::getDescricao() const
{
    return descricao;
}

inline void LifeLog::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

inline Evento LifeLog::getEvento() const
{
    return evento;
}

inline void LifeLog::setEvento(const Evento &newEvento)
{
    evento = newEvento;
}

inline Colaborador LifeLog::getColaborador() const
{
    return colaborador;
}

inline void LifeLog::setColaborador(const Colaborador &newColaborador)
{
    colaborador = newColaborador;
}

#endif // LIFELOG_H
