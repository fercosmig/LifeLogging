/* *****************************************
 * Fernando Costa Migliorini
 * 2024-03-11
 * LifeLogging
 * ColaboradorController.h
 * *****************************************/

#ifndef COLABORADORCONTROLLER_H
#define COLABORADORCONTROLLER_H

#include "Conexao.h"
#include <QVector>
#include "Colaborador.h"

class ColaboradorController{
private:
    QString sql;
    QSqlQuery query;
    Conexao conn;

protected:
public:
    // CONSTRUCTOR
    ColaboradorController() {}

    // METHODS
    int insere(Colaborador colaborador);
    QVector<Colaborador> listaTodos();
    Colaborador buscaPorId(int id_colaborador);
    Colaborador autenticaColaborador(QString nomeAcesso, QString senha);
    bool verificaNomeAcessoDuplicado(QString nome_Acesso);
    void altera(Colaborador coalborador);
    void remove(int id_colaborador);
};

inline int ColaboradorController::insere(Colaborador colaborador)
{
    sql = "INSERT INTO tb_colaboradores ";
    sql += "( nome, nome_acesso, senha, id_grupo ) ";
    sql += "VALUES ( :nome, :nome_acesso, :senha, :id_grupo )";

    int retorno = 0;
    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()) {

        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":nome_acesso", colaborador.getNomeAcesso());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", colaborador.getGrupo().getId());

        if (query.exec()){
            sql = "SELECT id FROM tb_colaboradores ORDER BY id DESC LIMIT 1";
            query.prepare(sql);
            if (query.exec()){
                if (query.next())
                    retorno = query.record().value("id").toInt();
            }

            qDebug() << "ColaboradorController::insere() query.exec: " << colaborador.getNome();
        } else
            qDebug() << "ColaboradorController::insere() query.exec: " << query.lastError().text();
    }
    return retorno;
}

inline QVector<Colaborador> ColaboradorController::listaTodos()
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.nome_acesso, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "ORDER BY tb_colaboradores.nome ASC";

    Grupo grupo;
    Colaborador colaborador;
    QVector<Colaborador> listaColaboradores;
    int contador = 0;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);

        if(query.exec()){
            if(query.next()){
                do {
                    grupo.setId(query.record().value("id_grupo").toInt());
                    grupo.setDescricao(query.record().value("descricao").toString());
                    grupo.setSigla(query.record().value("sigla").toString());

                    colaborador.setId(query.record().value("id").toInt());
                    colaborador.setNome(query.record().value("nome").toString());
                    colaborador.setNomeAcesso(query.record().value("nome_acesso").toString());
                    colaborador.setSenha(query.record().value("senha").toString());
                    colaborador.setGrupo(grupo);

                    listaColaboradores.push_back(colaborador);
                    contador++;
                } while (query.next());
            }
            qDebug() << "ColaboradorController.listaTodos() query.next: " << contador << "registros.";
        } else
            qDebug() << "ColaboradorController.listaTodos() query.exec: " << query.lastError().text();
    }
    conn.close();
    return listaColaboradores;
}

inline Colaborador ColaboradorController::buscaPorId(int id_colaborador)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.nome_acesso, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE tb_colaboradores.id = :id ";

    Colaborador colaborador;
    Grupo grupo;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", id_colaborador);

        if(query.exec()){
            if(query.next()){
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setDescricao(query.record().value("descricao").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                colaborador.setNomeAcesso(query.record().value("nome_acesso").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);
            } else {
                qDebug() << "ColaboradorController.buscaPorId() query.next: colaborador não encontrado.";
            }
        } else
            qDebug() << "ColaboradorController.buscaPorId() query.exec: " << query.lastError().text();
    }
    conn.close();
    return colaborador;
}

inline Colaborador ColaboradorController::autenticaColaborador(QString nomeAcesso, QString senha)
{
    sql = "SELECT ";
    sql += "tb_colaboradores.id, ";
    sql += "tb_colaboradores.nome, ";
    sql += "tb_colaboradores.nome_acesso, ";
    sql += "tb_colaboradores.senha, ";
    sql += "tb_grupos.id as id_grupo, ";
    sql += "tb_grupos.descricao, ";
    sql += "tb_grupos.sigla ";
    sql += "FROM tb_colaboradores ";
    sql += "INNER JOIN tb_grupos ";
    sql += "ON tb_colaboradores.id_grupo = tb_grupos.id ";
    sql += "WHERE tb_colaboradores.nome_acesso = :nome_acesso ";
    sql += "AND tb_colaboradores.senha = :senha";

    Colaborador colaborador;
    Grupo grupo;

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome_acesso", nomeAcesso);
        query.bindValue(":senha", senha);

        if(query.exec()){
            if(query.next()){
                grupo.setId(query.record().value("id_grupo").toInt());
                grupo.setDescricao(query.record().value("descricao").toString());
                grupo.setSigla(query.record().value("sigla").toString());

                colaborador.setId(query.record().value("id").toInt());
                colaborador.setNome(query.record().value("nome").toString());
                colaborador.setNomeAcesso(query.record().value("nome_acesso").toString());
                colaborador.setSenha(query.record().value("senha").toString());
                colaborador.setGrupo(grupo);
                qDebug() << "ColaboradorController.autenticaColaborador() query.next retornou " << colaborador.getNome();
            } else {
                colaborador.setId(0);
                qDebug() << "ColaboradorController.autenticaColaborador() query.next: colaborador não encontrado. Nome ou senha inválidos.";
            }
        } else {
            colaborador.setId(0);
            qDebug() << "ColaboradorController.autenticaColaborador() query.exec: " << query.lastError().text();
        }
    }
    conn.close();
    return colaborador;
}

inline bool ColaboradorController::verificaNomeAcessoDuplicado(QString nome_acesso)
{
    bool retorno = false;

    sql = "SELECT id FROM tb_colaboradores WHERE nome_acesso = :nome_acesso";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome_acesso", nome_acesso);

        if(query.exec()) {
            if(query.next()){
                retorno  = true;
                qDebug() << "ColaboradorController.verificaNomeAcessoDuplicado() query.exec: nome_acesso já existe!";
            }
        } else
            qDebug() << "ColaboradorController.verificaNomeAcessoDuplicado() query.exec: " << query.lastError().text();
    }
    conn.close();
    return retorno;
}

inline void ColaboradorController::altera(Colaborador colaborador)
{
    sql = "UPDATE tb_colaboradores SET ";
    sql += "nome = :nome, ";
    sql += "nome_acesso = :nome_acesso, ";
    sql += "senha = :senha, ";
    sql += "id_grupo = :id_grupo ";
    sql += "WHERE id = :id";

    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":nome", colaborador.getNome());
        query.bindValue(":nome_acesso", colaborador.getNomeAcesso());
        query.bindValue(":senha", colaborador.getSenha());
        query.bindValue(":id_grupo", colaborador.getGrupo().getId());
        query.bindValue(":id", colaborador.getId());

        if(query.exec())
            qDebug() << "ColaboradorController.altera() query.exec: " << colaborador.getNome() << " alterado.";
        else
            qDebug() << "ColaboradorController.altera() query.exec: " << query.lastError().text();
    }
    conn.close();
}

inline void ColaboradorController::remove(int id_colaborador)
{
    sql ="DELETE FROM tb_colaboradores WHERE id = :id";


    if(!conn.isOpen())
        conn.open();

    if(conn.isOpen()){
        query.prepare(sql);
        query.bindValue(":id", id_colaborador);

        if(!query.exec())
            qDebug() << "ColaboradorController.remove() query.exec: " << query.lastError().text();
    }
    conn.close();
}

#endif // COLABORADORCONTROLLER_H
