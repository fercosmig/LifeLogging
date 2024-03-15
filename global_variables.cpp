#include "global_variables.h"

global_variables::global_variables() {}

QSqlDatabase global_variables::bancoDeDados;
bool global_variables::isLogged;
Colaborador global_variables::colaboradorLogado;

// Colocar código abaixo no construtor do mainWindow.cpp
/*
QString local_db = qApp->applicationDirPath();
QString nome_db = "/db/aula83.db";
QString banco = local_db + nome_db;

global_variables::bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
global_variables::bancoDeDados.setDatabaseName(banco);
*/
