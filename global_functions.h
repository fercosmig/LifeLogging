#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <QString>
#include <QTableWidget>

class global_functions
{
public:
    global_functions();
    static bool minCaracter(QString str, int quantidade);
    static void tableWidgetFormat(QTableWidget *tw, QStringList cabecalho);
    static QString doubleToString(double valor);
    static QString nameGenerator();
};

#endif // GLOBAL_FUNCTIONS_H
