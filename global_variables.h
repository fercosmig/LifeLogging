/* *****************************************
 * Fernando Costa Migliorini
 * 2024-03-11
 * LifeLogging
 * global_variables.h
 * *****************************************/

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <QSqlDatabase>
#include "Colaborador.h"

class global_variables
{
public:
    static QSqlDatabase bancoDeDados;
    static bool isLogged;
    static Colaborador colaboradorLogado;

    global_variables();
};

#endif // GLOBAL_VARIABLES_H
