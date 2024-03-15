#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <QString>
#include "Grupo.h"

class Colaborador{
private:
    int id;
    QString nome;
    QString nomeAcesso;
    QString senha;
    Grupo grupo;

protected:
public:
    // CONSTRUCTOR
    Colaborador() {}

    // GETTERS AND SETTERS
    int getId() const;
    void setId(int newId);
    QString getNome() const;
    void setNome(const QString &newNome);
    QString getNomeAcesso() const;
    void setNomeAcesso(const QString &newNomeAcesso);
    QString getSenha() const;
    void setSenha(const QString &newSenha);
    Grupo getGrupo() const;
    void setGrupo(const Grupo &newGrupo);
};

inline int Colaborador::getId() const
{
    return id;
}

inline void Colaborador::setId(int newId)
{
    id = newId;
}

inline QString Colaborador::getNome() const
{
    return nome;
}

inline void Colaborador::setNome(const QString &newNome)
{
    nome = newNome;
}

inline QString Colaborador::getNomeAcesso() const
{
    return nomeAcesso;
}

inline void Colaborador::setNomeAcesso(const QString &newNomeAcesso)
{
    nomeAcesso = newNomeAcesso;
}

inline QString Colaborador::getSenha() const
{
    return senha;
}

inline void Colaborador::setSenha(const QString &newSenha)
{
    senha = newSenha;
}

inline Grupo Colaborador::getGrupo() const
{
    return grupo;
}

inline void Colaborador::setGrupo(const Grupo &newGrupo)
{
    grupo = newGrupo;
}
#endif // COLABORADOR_H
