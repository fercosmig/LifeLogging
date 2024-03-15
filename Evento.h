#ifndef EVENTO_H
#define EVENTO_H

#include <QString>

class Evento{
private:
    int id;
    QString titulo;
    QString descricao;

protected:
public:
    // CONSTRUCTOR
    Evento() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getTitulo() const;
    void setTitulo(const QString &newTitulo);
    QString getDescricao() const;
    void setDescricao(const QString &newDescricao);
};

inline int Evento::getId() const
{
    return id;
}

inline void Evento::setId(int newId)
{
    id = newId;
}

inline QString Evento::getTitulo() const
{
    return titulo;
}

inline void Evento::setTitulo(const QString &newTitulo)
{
    titulo = newTitulo;
}

inline QString Evento::getDescricao() const
{
    return descricao;
}

inline void Evento::setDescricao(const QString &newDescricao)
{
    descricao = newDescricao;
}

#endif // EVENTO_H
