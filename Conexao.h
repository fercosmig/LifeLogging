/* *****************************************
 * Fernando Costa Migliorini
 * 2024-03-11
 * LifeLogging
 * Conexao.h
 * *****************************************/

#ifndef CONEXAO_H
#define CONEXAO_H

#include <QDebug>
#include <QtSql>
#include "global_variables.h"

class Conexao
{
private:
protected:
public:
    // CONSTRUCTOR
    Conexao(){}

    // METHODS
    void open();
    bool isOpen();
    void close();
};

inline void Conexao::open()
{
    if (!global_variables::bancoDeDados.isOpen()) {
        if (!global_variables::bancoDeDados.open())
            qDebug() << "Conexao.open(): " << global_variables::bancoDeDados.lastError().text();
    }
}

inline bool Conexao::isOpen()
{
    if (global_variables::bancoDeDados.isOpen())
        return true;
    return false;
}

inline void Conexao::close()
{
    if (global_variables::bancoDeDados.isOpen()) {
        global_variables::bancoDeDados.close();
    }
}

/*
 * 2024-03-01 - Fernando Costa Migliorini
 */

#endif // CONEXAO_H
