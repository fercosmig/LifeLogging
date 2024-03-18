#include "global_functions.h"

global_functions::global_functions() {}

QString global_functions::nameGenerator()
{
    /*
     * function: nameGenerator()
     * Gera nomes aleatórios concatenando vogais e consoantes.
     * Gera strings com número de caracteres entre 8 e 20.
     * Retorna um valor do tipo string contendo o nome gerado.
     * date: 2024-03-11 - Fernando Costa Migliorini
     */

    QString nome;
    QString vogais[] {"a", "e", "i", "o", "u"};
    QString consoantes[] {"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "w", "v", "x", "y", "z"};

    std::uniform_int_distribution<int> int_vogais(0, 4);
    std::uniform_int_distribution<int> int_consoantes(0, 20);
    std::uniform_int_distribution<int> int_tamanho(4, 10);

    int tamanho = int_tamanho(*QRandomGenerator::global());

    for (int i = 0; i < tamanho; i++){
        nome += consoantes[int_consoantes(*QRandomGenerator::global())];
        nome += vogais[int_vogais(*QRandomGenerator::global())];
    }
    return nome;
}

QString global_functions::doubleToString(double valor)
{
    /*
     * function: doubleToString()
     * Recebe um valor do tipo double.
     * Formata o valor com duas casas decimais.
     * Retorna uma string com o valor formatado.
     * date: 2024-03-09 - Fernando Costa Migliorini
     */

    QString formatado;
    try {

        formatado = QString("%1").arg(valor, 0, 'f', 2);

    } catch (const std::exception &e) {
        qDebug() << "fd (formata_double): " << e.what();
    }

    return formatado;
}

void global_functions::tableWidgetFormat(QTableWidget *tw, QStringList cabecalho)
{
    /*
     * function: tableWidgetFormat()
     * Recebe um QTableWidget e um QStringList.
     * Formata o tableWidget e insere o QStringList como cabecalho.
     * date: 2024-03-07 - Fernando Costa Migliorini
     */

    int columns = cabecalho.size();

    tw->setColumnCount(columns);
    tw->setHorizontalHeaderLabels(cabecalho);
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers); // desabilitando edição
    tw->setSelectionBehavior(QAbstractItemView::SelectRows); // seleção de toda a linha
    tw->verticalHeader()->setVisible(false); // remove nº linha
    tw->setSelectionMode(QAbstractItemView::SingleSelection); // selecionando somente uma linha
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // formata largura da coluna conforme conteudo
    //tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //// formata largura da coluna conforme tamanho do tableWidget
}

bool global_functions::minCaracter(QString str, int quantidade)
{
    /*
     * function: minCaracter()
     * Recebe uma String e a quantidade mínima de caracteres que a string precisa ter.
     * Retorna true se a string contiver a quantidade de caracteres passada ou mais.
     * Retorna false se a string contiver menos caracteres do que foi passado.
     * date: 2024-03-04 - Fernando Costa Migliorini
     */

    if (str.length() < quantidade)
        return false;
    return true;
}
