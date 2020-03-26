/*
 * bibliotecas da linguagem c inseridas no programa
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include<locale.h>

/*
 *constantes para indicar o estado de uma tarefa
*/
#define TAREFA_NAO_EXECUTADA 0
#define TAREFA_EXECUTADA 1

/*
 *constantes representando os tamanhos maximos 
 *para as strings nome e descricao
*/
#define TAMANHO_MAXIMO_NOME 80
#define TAMANHO_MAXIMO_DESCRICAO 400


/*
 * estrutura representando a data
*/
struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct data Data;

/*
 * estrutura representando a tarefa
*/
struct tarefa{
    char descricao[TAMANHO_MAXIMO_DESCRICAO];
    Data data;
    int estado;
};

typedef struct tarefa Tarefa;

/*
 * estrutura representando a lista de tarefas
*/
struct listaTarefas{
    char nome[TAMANHO_MAXIMO_NOME];
    char descricao[TAMANHO_MAXIMO_DESCRICAO];
    Tarefa * listaTarefas;
    int tamanhoAtual;
    int tamanhoMaximo;
};

typedef struct listaTarefas ListaTarefas;

/*
 * estrutura representando o conjunto de listas de tarefas
*/
struct conjuntoListasTarefas{
    ListaTarefas * conjuntoListas;
    int tamanhoAtual;
    int tamanhoMaximo;
};

typedef struct conjuntoListasTarefas ConjuntoListasTarefas;



/*
 *            definicao dos cabecalhos(headers) dos procedimentos e funcoes implementados para o programa
*/



/*
 * procedimentos e funcoes relativas ao conjunto de listas de tarefas (primeiro nivel hierarquico)
*/

void menuPrincipal();

ConjuntoListasTarefas * alocarConjuntoListasTarefas();

void realocarConjuntoListasTarefas(ConjuntoListasTarefas * conjunto, int novoTamanho);

void adicionarListaTarefas(ConjuntoListasTarefas * conjunto, ListaTarefas todoList);

void exibirListasTarefas(ConjuntoListasTarefas * conjunto);

void removerListaTarefas(ConjuntoListasTarefas * conjunto, int escolha);

void imprimirTarefasEntreDatas(ConjuntoListasTarefas * conjunto,Data inicio, Data fim);

int verificarExisteListaNoConjuntoListas(ConjuntoListasTarefas conjunto);


/*
 * procedimentos e funcoes relativas a manipulacao de datas
*/

int validarData(Data data);

void preencherData(Data  * data);

int verificarSeDataEstaNoIntervalo(Data data, Data inicio,Data fim);

int verificarSeDataEMenor(Data dataAnalisada,Data dataReferencia);

/*
 * procedimentos e funcoes relativas a manipulacao das tarefas contidas em uma lista de tarefas (segundo nivel hierarquico)
*/

void menuManipulacaoLista(ConjuntoListasTarefas * conjunto);

ListaTarefas * alocarListaTarefas();

void realocarListaTarefas(ListaTarefas * todoList, int novoTamanho);

void adicionarTarefa(ListaTarefas * todoList, Tarefa tarefa);

void exibirTarefas(ListaTarefas todoList);

int verificarExisteTarefaNaLista(ListaTarefas todoList);

void removerTarefa(ListaTarefas * todoList, int escolha);

void marcarTarefaComoFeita(ListaTarefas * todoList, int escolha);

void marcarTarefaComoNaoFeita(ListaTarefas * todoList, int escolha);

void aumentarPrioridadeTarefa(ListaTarefas * todoList, int escolha);


/*
 * procedimento para a liberacao da memoria alocada para o conjunto de listas e suas listas de tarefas
*/
void liberarMemoriaAlocada(ConjuntoListasTarefas * conjunto);



/*
 *               implementacao das funcoes e procedimentos
*/



/*
 *funcao principal do programa
*/
int main(){
    /*definindo a a linguagem e regras de acentuacao do programa para a lingua portuguesa*/
    setlocale(LC_ALL,"Portuguese");
    menuPrincipal();
    return 0;
}


/*
 * menu principal da aplicacao, o qual gerencia as opcoes do primeiro nivel
 * hierárquico das operacoes sobre as tarefas, como inserir uma nova lista de tarefas
 * remover uma lista de tarefas, abrir e editar uma lista de tarefas
 * listar todas as tarefas existentes entre duas datas especificas e sair do programa
*/
void menuPrincipal(){
    int opcao;
    ConjuntoListasTarefas * conjunto = NULL;
    conjunto = alocarConjuntoListasTarefas();

    printf(" ---------------------------------------------------------------------\n");
    printf("|           Bem vindo ao sistema de gerenciamento de tarefas          |\n");
    printf(" ---------------------------------------------------------------------\n\n\n");
    do{
        printf("                Menu de manipulação das listas de tarefas\n");
        printf("                -----------------------------------------\n\n");

        printf("Digite a opcao desejada:\n\n\n");
        printf("1 - Adicionar lista de tarefas\n");
        printf("2 - Remover lista de tarefas\n");
        printf("3 - Abrir lista de tarefas\n");
        printf("4 - Listar tarefas de um período\n");
        printf("5 - Sair\n");
        printf("Entrada: ");
        scanf("%d",&opcao);
        __fpurge(stdin);
        if(opcao==1){
            system("clear");
            printf("                Adicionar nova lista de tarefas\n");
            printf("                -------------------------------\n\n");
            ListaTarefas * todoList = NULL;
            todoList = alocarListaTarefas();
            printf("Digite o nome da Lista de tarefas: ");
            fgets(todoList->nome,TAMANHO_MAXIMO_NOME,stdin);
            __fpurge(stdin);
            printf("Digite a descrição da Lista de tarefas: ");
            fgets(todoList->descricao,TAMANHO_MAXIMO_DESCRICAO,stdin);
            __fpurge(stdin);
            adicionarListaTarefas(conjunto,*todoList);
            system("clear");
            printf("Adicionado com sucesso!\n");
            printf("Tecle Enter para retornar...");
            getchar();
            system("clear");
        }
        else if(opcao==2){
            system("clear");
            if(verificarExisteListaNoConjuntoListas(*conjunto)==0){
                printf("Não há nenhuma lista de tarefas cadastrada\n");
                printf("Tecle Enter para retornar...");
                getchar();
                system("clear");
                continue;
            }
            printf("                Remover uma lista de tarefas\n");
            printf("                ----------------------------\n\n");
            int escolha;
            printf("Escolha o numero da lista de tarefas a ser removida\n\n");
            exibirListasTarefas(conjunto);
            printf("Entrada: ");
            scanf("%d",&escolha);
            __fpurge(stdin);
            removerListaTarefas(conjunto,escolha);
        }
        else if(opcao==3){
            system("clear");
            if(verificarExisteListaNoConjuntoListas(*conjunto)==0){
                printf("Não há nenhuma lista de tarefas cadastrada\n");
                printf("Tecle Enter para retornar...");
                getchar();
                system("clear");
                continue;
            }
            menuManipulacaoLista(conjunto);
        }
        else if(opcao==4){
            system("clear");
            printf("                Pesquisar tarefas por intervalo de tempo\n");
            printf("                ----------------------------------------\n\n");
            Data inicio;
            Data fim;
            printf("Digite a data de inicio para a pesquisa\n");
            preencherData(&inicio);
            printf("\n------------------------------\n");
            printf("Digite a data de término para a pesquisa\n");
            preencherData(&fim);
            imprimirTarefasEntreDatas(conjunto,inicio,fim);
        }
        else if(opcao==5){
            printf("Obrigado por utilizar o programa : )\n\n");
            liberarMemoriaAlocada(conjunto);
            exit(1);
        }
    }
    while(1);
}

/*
 * função que retorna a memória para um novo conjunto de listas de tarefas, com um tamanho máximo inicial de 10 posições
 * que pode crescer ou diminuir caso necessario por meio de alocacao dinamica
*/
ConjuntoListasTarefas * alocarConjuntoListasTarefas(){
    ConjuntoListasTarefas * conjunto = NULL;
    conjunto = (ConjuntoListasTarefas *)malloc(sizeof(struct conjuntoListasTarefas));
    conjunto->tamanhoAtual = 0;
    conjunto->tamanhoMaximo = 10;
    conjunto->conjuntoListas = (ListaTarefas*)malloc(conjunto->tamanhoMaximo * sizeof(struct conjuntoListasTarefas));
    return conjunto;
}

/*
 *procedimento auxiliar que realoca o tamanho do conjunto de lista de tarefas
 *quando ele necessita crescer ou diminuir o seu tamanho
*/
void realocarConjuntoListasTarefas(ConjuntoListasTarefas * conjunto, int novoTamanho){
    ListaTarefas * listaTarefasAuxiliar = (ListaTarefas *)malloc(novoTamanho * sizeof(struct listaTarefas));
    for(int i = 0; i < conjunto->tamanhoAtual; i++){
        listaTarefasAuxiliar[i] = conjunto->conjuntoListas[i];
    }
    free(conjunto->conjuntoListas);
    conjunto->conjuntoListas = listaTarefasAuxiliar;
    conjunto->tamanhoMaximo = novoTamanho;
}

/*
 * procedimento que adiciona uma nova lista de tarefas no conjunto de listas de tarefas
*/
void adicionarListaTarefas(ConjuntoListasTarefas * conjunto, ListaTarefas todoList){
    if(conjunto->tamanhoAtual == conjunto->tamanhoMaximo){
        realocarConjuntoListasTarefas(conjunto, conjunto->tamanhoMaximo*2);
    }
    /*inserindo a lista no conjunto de listas*/
    conjunto->conjuntoListas[conjunto->tamanhoAtual].listaTarefas = todoList.listaTarefas;
    strcpy(conjunto->conjuntoListas[conjunto->tamanhoAtual].nome,todoList.nome);
    strcpy(conjunto->conjuntoListas[conjunto->tamanhoAtual].descricao,todoList.descricao);
    conjunto->conjuntoListas[conjunto->tamanhoAtual].tamanhoAtual = todoList.tamanhoAtual;
    conjunto->conjuntoListas[conjunto->tamanhoAtual].tamanhoMaximo = todoList.tamanhoMaximo;
    conjunto->tamanhoAtual++;
}

/*
 * procedimento que tem como objetivo exibir todas as listas de tarefas
 * existentes no conjunto de listas de tarefas
*/
void exibirListasTarefas(ConjuntoListasTarefas * conjunto){
    printf("-------------------------------------------------\n\n");
    for(int i=0;i<conjunto->tamanhoAtual;i++){
        printf("Lista de tarefas %d\n",i+1);
        printf("Nome - %s",conjunto->conjuntoListas[i].nome);
        printf("Descrição - %s\n",conjunto->conjuntoListas[i].descricao);
        printf("-------------------------------------------------\n\n");
    }
}

/*
 * procedimento que remove uma lista de tarefas do conjunto de listas de tarefas por
 * meio de uma escolha(representado por um numero inteiro que varia de 1 ao numero de elementos do conjunto de lista de tarefas)
*/
void removerListaTarefas(ConjuntoListasTarefas * conjunto, int escolha){
    if(escolha <= 0){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    if(escolha > conjunto->tamanhoAtual){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    escolha = escolha - 1;
    /*realizando a remocao*/
    for(int i = escolha; i < conjunto->tamanhoMaximo - 1; i++){
        conjunto->conjuntoListas[i] = conjunto->conjuntoListas[i + 1];
    }
    conjunto->tamanhoAtual--;

    if(conjunto->tamanhoAtual == conjunto->tamanhoMaximo/4){
        realocarConjuntoListasTarefas(conjunto, conjunto->tamanhoMaximo/2);
    }

    system("clear");
    printf("Removida com sucesso!\n");
    printf("Tecle Enter para retornar...");
    getchar();
    system("clear");
}

/*
 *procedimento que recebe duas datas e o conjunto de listas de tarefas.
 *ele imprime todas as tarefas encontradas entre essas duas datas
*/
void imprimirTarefasEntreDatas(ConjuntoListasTarefas * conjunto,Data inicio, Data fim){
    if(verificarSeDataEMenor(fim,inicio)){
        system("clear");
        printf("Data inválida! a data de destino é menor do que a data de origem\n");
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    if(validarData(inicio) == 0 || validarData(fim) == 0){
        system("clear");
        printf("Data inválida! Os dados escritos na data são inconsistentes! \n");
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    system("clear");
    for(int i=0;i<conjunto->tamanhoAtual;i++){
        /*nao existe tarefa nessa lista*/
        if(verificarExisteTarefaNaLista(conjunto->conjuntoListas[i])==0){
            continue;
        }
        else{
            printf("\n-------------------------------------------------\n");
            printf("Lista: %s",conjunto->conjuntoListas[i].nome);
            printf("-------------------------------------------------\n");

            for(int j=0;j<conjunto->conjuntoListas[i].tamanhoAtual;j++){
                /*data esta no intervalo*/
                if(verificarSeDataEstaNoIntervalo(conjunto->conjuntoListas[i].listaTarefas[j].data,inicio,fim)==1){
                        printf("\nTarefa %d\n",j+1);
                        printf("Data: %d/%d/%d\n",conjunto->conjuntoListas[i].listaTarefas[j].data.dia,conjunto->conjuntoListas[i].listaTarefas[j].data.mes,conjunto->conjuntoListas[i].listaTarefas[j].data.ano);
                        if(conjunto->conjuntoListas[i].listaTarefas[j].estado == TAREFA_NAO_EXECUTADA){
                            printf("Estado: Tarefa Não Executada\n");
                        }
                        else{
                            printf("Estado: Tarefa Executada\n");
                        }
                        printf("Descricao: - %s\n",conjunto->conjuntoListas[i].listaTarefas[j].descricao);
                }
                /*data nao esta no intervalo*/
                else{
                    continue;
                }
            }
        }
    }
    printf("\n\nDados da pesquisa\n");
    printf("Data de inicio da pesquisa: %d/%d/%d\n",inicio.dia,inicio.mes,inicio.ano);
    printf("Data de término da pesquisa: %d/%d/%d\n",fim.dia,fim.mes,fim.ano);
    printf("Tecle Enter para retornar...\n");
    getchar();
    system("clear");
}

/*
 * função que retorna 0 se nao existir uma lista de tarefas no
 * conjunto de listas de tarefas
 * ou 1 caso exista alguma lista de tarefas nesse conjunto
*/
int verificarExisteListaNoConjuntoListas(ConjuntoListasTarefas conjunto){
    if(conjunto.tamanhoAtual==0){
        return 0;
    }
    else{
        return 1;
    }
}


/*
 * procedimentos e funcoes relativas a manipulacao de datas
*/


/*
 *funcao que retorna 1 caso a data seja valida, ou 0 caso a data seja invalida
*/
int validarData(Data data){
    if(data.dia >=1 && data.dia <=31){
        if(data.mes >=1 && data.mes <=12){
            if(data.ano >= 0){
                return 1;
            }
        }
    }
    return 0;
}

/*
 *procedimento que recebe uma data por referencia e preenche cada um dos seus campos
*/
void preencherData(Data  * data){
    printf("(Preenchendo data) - dia: ");
    scanf("%d",&data->dia);
    __fpurge(stdin);
    printf("(Preenchendo data) - mês: ");
    scanf("%d",&data->mes);
    __fpurge(stdin);
    printf("(Preenchendo data) - ano: ");
    scanf("%d",&data->ano);
    __fpurge(stdin);
}

/*
 *esta funcao usa a funcao auxiliar verificarSeDataEMenor para retornar 1
 *caso a data esteja no intervalo entre 2 datas
 *ou 0 caso nao esteja nesse mesmo intervalo
*/
int verificarSeDataEstaNoIntervalo(Data data, Data inicio,Data fim){
    return (verificarSeDataEMenor(inicio, data) && verificarSeDataEMenor(data, fim));
}

/*
 *funcao que retorna 1 caso a data analisada seja menor do que a data de referencia, ou 0 caso contrario
*/
int verificarSeDataEMenor(Data dataAnalisada,Data dataReferencia){
    //comparando os anos
    if (dataAnalisada.ano < dataReferencia.ano){
        return 1;
    }
    //comparando meses, quando os anos forem iguais
    if (dataAnalisada.ano == dataReferencia.ano && dataAnalisada.mes < dataReferencia.mes){
        return 1;
    }
    //comparando dias, quando anos e meses forem iguais
    if (dataAnalisada.ano == dataReferencia.ano && dataAnalisada.mes == dataReferencia.mes && dataAnalisada.dia < dataReferencia.dia){
        return 1;
    }
    return 0;
}

/*
 * procedimentos e funcoes relativas a manipulacao das tarefas contidas em uma lista de tarefas (segundo nivel hierarquico)
*/




/*
 * procedimento responsavel por representar o menu do segundo nivel hierarquico, indicando as operacoes sobre uma lista de tarefas
 * especifica e suas respectivas tarefas, como inserir uma nova tarefa, remover uma tarefa especifica,marcar uma tarefa como feita,
 * marcar uma tarefa como nao feita, mudar a prioridade de uma tarefa dentro dessa lista específica e voltar para o menu do primeiro
 * nivel  hierarquico do programa
*/
void menuManipulacaoLista(ConjuntoListasTarefas * conjunto){
    int escolhaListaTarefa;
    int opcao;
    printf("                Gerenciar tarefas de uma lista específica\n");
    printf("                -----------------------------------------\n\n");
    printf("Escolha uma lista de tarefas para editar: \n\n");
    exibirListasTarefas(conjunto);
    printf("Entrada: ");
    scanf("%d",&escolhaListaTarefa);
    __fpurge(stdin);
    system("clear");
    if(escolhaListaTarefa <= 0 || escolhaListaTarefa > conjunto->tamanhoAtual){
        system("clear");
        printf("A posição %d não existe no conjunto de listas de tarefas!\n",escolhaListaTarefa);
        printf("Tecle Enter para continuar\n");
        getchar();
        system("clear");
        return;
    }
    do{
        printf("                Gerenciar tarefas de uma lista específica\n");
        printf("                -----------------------------------------\n\n");
        printf("                Lista escolhida: %s\n\n",conjunto->conjuntoListas[escolhaListaTarefa-1].nome);
        if(verificarExisteTarefaNaLista(conjunto->conjuntoListas[escolhaListaTarefa-1])==0){
            printf("                ---------------------------------------\n");
            printf("                Ainda não há nenhuma tarefa nessa lista\n");
            printf("                ---------------------------------------\n\n");
        }
        else{
            exibirTarefas(conjunto->conjuntoListas[escolhaListaTarefa-1]);
        }
        printf("1 - Adicionar tarefa na lista\n");
        printf("2 - Remover tarefa na lista\n");
        printf("3 - Marcar tarefa como feita na lista\n");
        printf("4 - Marcar tarefa como nao feita\n");
        printf("5 - Mudar prioridade da tarefa\n");
        printf("6 - Voltar ao inicio\n");
        printf("Entrada: ");
        scanf("%d",&opcao);
        __fpurge(stdin);
        if(opcao==1){
            system("clear");
            printf("                Adicionar nova tarefa em %s\n\n",conjunto->conjuntoListas[escolhaListaTarefa-1].nome);
            Tarefa tarefa;
            printf("Digite a descricao da tarefa: ");
            fgets(tarefa.descricao,TAMANHO_MAXIMO_DESCRICAO,stdin);
            __fpurge(stdin);
            preencherData(&tarefa.data);
            if(validarData(tarefa.data)==0){
                system("clear");
                printf("A data digitada não é válida!\n");
                printf("Tecle Enter para retornar...");
                getchar();
                system("clear");
                continue;
            }
            tarefa.estado = TAREFA_NAO_EXECUTADA;
            adicionarTarefa(&conjunto->conjuntoListas[escolhaListaTarefa-1],tarefa);
            system("clear");
            printf("Adicionado com sucesso!\n");
            printf("Tecle Enter para retornar...");
            getchar();
            system("clear");
        }
        else if(opcao==2){
            system("clear");
            if(verificarExisteTarefaNaLista(conjunto->conjuntoListas[escolhaListaTarefa-1])==0){
                printf("Não há nenhuma tarefa na lista escolhida\n");
                printf("Tecle Enter para retornar...");
                getchar();
                continue;
            }
            printf("                Remover tarefa em %s\n\n",conjunto->conjuntoListas[escolhaListaTarefa-1].nome);
            int escolha;
            printf("Escolha o numero da tarefa a ser removida\n");
            exibirTarefas(conjunto->conjuntoListas[escolhaListaTarefa-1]);
            printf("Entrada: ");
            scanf("%d",&escolha);
            __fpurge(stdin);
            removerTarefa(&conjunto->conjuntoListas[escolhaListaTarefa-1],escolha);
        }
        else if(opcao==3){
            system("clear");
            printf("         Marcar alguma tarefa como feita em %s\n\n",conjunto->conjuntoListas[escolhaListaTarefa-1].nome);
            if(verificarExisteTarefaNaLista(conjunto->conjuntoListas[escolhaListaTarefa-1])==0){
                printf("Não há nenhuma tarefa na lista escolhida\n");
                printf("Tecle Enter para retornar...");
                getchar();
                system("clear");
                continue;
            }
            int escolha;
            printf("Escolha o numero da tarefa a ser marcada como feita\n");
            exibirTarefas(conjunto->conjuntoListas[escolhaListaTarefa-1]);
            printf("Entrada: ");
            scanf("%d",&escolha);
            __fpurge(stdin);
            marcarTarefaComoFeita(&conjunto->conjuntoListas[escolhaListaTarefa-1],escolha);
        }
        else if(opcao==4){
            system("clear");
            printf("         Marcar alguma tarefa como não feita em %s\n\n",conjunto->conjuntoListas[escolhaListaTarefa-1].nome);
            if(verificarExisteTarefaNaLista(conjunto->conjuntoListas[escolhaListaTarefa-1])==0){
                printf("Não há nenhuma tarefa na lista escolhida\n");
                printf("Tecle Enter para retornar...");
                getchar();
                system("clear");
                continue;
            }
            int escolha;
            printf("Escolha o numero da tarefa a ser marcada como não feita\n\n");
            exibirTarefas(conjunto->conjuntoListas[escolhaListaTarefa-1]);
            printf("Entrada: ");
            scanf("%d",&escolha);
            __fpurge(stdin);
            marcarTarefaComoNaoFeita(&conjunto->conjuntoListas[escolhaListaTarefa-1],escolha);
        }
        else if(opcao==5){
            system("clear");
            if(verificarExisteTarefaNaLista(conjunto->conjuntoListas[escolhaListaTarefa-1])==0){
                printf("Não há nenhuma tarefa na lista escolhida\n");
                printf("Tecle Enter para retornar...");
                getchar();
                system("clear");
                continue;
            }
            printf("             Mudar prioridade de uma tarefa em %s\n\n",conjunto->conjuntoListas[escolhaListaTarefa-1].nome);
            int escolha;
            printf("Escolha o numero da tarefa para ter a prioridade maxima\n");
            exibirTarefas(conjunto->conjuntoListas[escolhaListaTarefa-1]);
            printf("Entrada: ");
            scanf("%d",&escolha);
            __fpurge(stdin);
            aumentarPrioridadeTarefa(&conjunto->conjuntoListas[escolhaListaTarefa-1],escolha);
        }
        else if(opcao==6){
            system("clear");
            return;
        }
    }
    while(1);
}

/*
 * função que retorna a memória para uma nova lista de tarefas, com um tamanho máximo
 * inicialmente de 10 posições, que podem ser aumentados ou diminuidos dinamicamente
 * durante a execucao do programa
*/
ListaTarefas * alocarListaTarefas(){
    ListaTarefas * todoList = NULL;
    todoList = (ListaTarefas *)malloc(sizeof(struct listaTarefas));
    strcpy(todoList->nome,"");
    strcpy(todoList->descricao,"");
    todoList->tamanhoAtual = 0;
    todoList->tamanhoMaximo = 10;
    todoList->listaTarefas = (Tarefa *)malloc(10 * sizeof(struct tarefa));
    return todoList;
}


/*
 *procedimento auxiliar que realoca o tamanho do de uma lista de tarefas
 *quando ele necessita crescer ou diminuir o tamanho do seu vetor
*/
void realocarListaTarefas(ListaTarefas * todoList, int novoTamanho){
    Tarefa * listaTarefasAuxiliar = (Tarefa *)malloc(novoTamanho * sizeof(struct tarefa));
    for(int i = 0; i < todoList->tamanhoAtual; i++){
        listaTarefasAuxiliar[i] = todoList->listaTarefas[i];
    }
    free(todoList->listaTarefas);
    todoList->listaTarefas = listaTarefasAuxiliar;
    todoList->tamanhoMaximo = novoTamanho;
}

/*
 * procedimento que recebe uma tarefa e uma lista de tarefas por referencia
 * e adiciona essa tarefa na ultima posicao do vetor dessa lista de tarefas
 * por referencia
 */
void adicionarTarefa(ListaTarefas * todoList, Tarefa tarefa){
    if(todoList->tamanhoAtual == todoList->tamanhoMaximo){
        realocarListaTarefas(todoList, todoList->tamanhoMaximo*2);
    }
    strcpy(todoList->listaTarefas[todoList->tamanhoAtual].descricao,tarefa.descricao);
    todoList->listaTarefas[todoList->tamanhoAtual].data.dia = tarefa.data.dia;
    todoList->listaTarefas[todoList->tamanhoAtual].data.mes = tarefa.data.mes;
    todoList->listaTarefas[todoList->tamanhoAtual].data.ano = tarefa.data.ano;
    todoList->listaTarefas[todoList->tamanhoAtual].estado = tarefa.estado;
    todoList->tamanhoAtual++;
}

/*
 * procedimento que imprime todas as contida no vetor da lista de tarefas recebida como parametro
*/
void exibirTarefas(ListaTarefas todoList){
    printf("\n         Tarefas da lista\n");
    printf("-------------------------------------------------\n");
    for(int i=0;i<todoList.tamanhoAtual;i++){

        printf("Tarefa %d\n",i+1);
        printf("Data: %d/%d/%d\n",todoList.listaTarefas[i].data.dia,todoList.listaTarefas[i].data.mes,todoList.listaTarefas[i].data.ano);
        if(todoList.listaTarefas[i].estado == TAREFA_NAO_EXECUTADA){
            printf("Estado: Tarefa Não Executada\n");
        }
        else{
            printf("Estado: Tarefa Executada\n");
        }
        printf("Descricao: - %s",todoList.listaTarefas[i].descricao);
        printf("-------------------------------------------------\n");
    }
    printf("\n");
}

/*
 * funcao que retorna 0 se nao existe uma tarefa na lista de tarefas ou 1 caso exista alguma tarefa
*/
int verificarExisteTarefaNaLista(ListaTarefas todoList){
    if(todoList.tamanhoAtual==0){
        return 0;
    }
    else{
        return 1;
    }
}


/*
 * procedimento que remove uma tarefa de uma lista de tarefas por
 * meio de uma escolha(representado por um numero inteiro que varia de 1
 * ao numero de elementos do vetor da lista de tarefas)
*/
void removerTarefa(ListaTarefas * todoList, int escolha){
    if(escolha <= 0){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    if(escolha > todoList->tamanhoAtual){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    escolha = escolha - 1;
    /*realizando a remocao*/
    for(int i = escolha; i < todoList->tamanhoMaximo - 1; i++){
        todoList->listaTarefas[i] = todoList->listaTarefas[i + 1];
    }
    todoList->tamanhoAtual--;

    if(todoList->tamanhoAtual == todoList->tamanhoMaximo/4){
        realocarListaTarefas(todoList, todoList->tamanhoMaximo/2);
    }
    system("clear");
    printf("Removida com sucesso!\n");
    printf("Tecle Enter para retornar...");
    getchar();
    system("clear");
}


/*
 * procedimento que marca uma tarefa especifica selecionada por
 * meio de uma escolha(representado por um numero inteiro que varia de 1
 * ao numero de elementos do vetor da lista de tarefas) como feita.
 * esse processo e realizado por referencia no vetor da lista de tarefas
*/
void marcarTarefaComoFeita(ListaTarefas * todoList, int escolha){
    if(escolha <= 0){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    if(escolha > todoList->tamanhoAtual){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    escolha = escolha - 1;
    if(todoList->listaTarefas[escolha].estado == TAREFA_EXECUTADA){
        system("clear");
        printf("Essa tarefa já estava marcada como executada! Não foi possível modificar\n");
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    todoList->listaTarefas[escolha].estado = TAREFA_EXECUTADA;
    system("clear");
    printf("Modificado com sucesso!\n");
    printf("Tecle Enter para retornar...");
    getchar();
    system("clear");
}

/*
 * procedimento que marca uma tarefa especifica selecionada por
 * meio de uma escolha(representado por um numero inteiro que varia de 1
 * ao numero de elementos do vetor da lista de tarefas) como nao feita.
 * esse processo e realizado por referencia no vetor da lista de tarefas
*/
void marcarTarefaComoNaoFeita(ListaTarefas * todoList, int escolha){
    if(escolha <= 0){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    if(escolha > todoList->tamanhoAtual){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    escolha = escolha - 1;
    if(todoList->listaTarefas[escolha].estado == TAREFA_NAO_EXECUTADA){
        system("clear");
        printf("Essa tarefa já estava marcada como não executada! Não foi possível modificar\n");
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    todoList->listaTarefas[escolha].estado = TAREFA_NAO_EXECUTADA;
    system("clear");
    printf("Modificado com sucesso!\n");
    printf("Tecle Enter para retornar...");
    getchar();
    system("clear");
}

/*
 * procedimento que seleciona uma tarefa especifica por
 * meio de uma escolha(representado por um numero inteiro que varia de 1
 * ao numero de elementos do vetor da lista de tarefas) e realiza um deslocamento
 * circular para direita dentro desse vetor, colocando a tarefa da escolha
 * dentro do indice 0 e as outras tarefas uma posicao para a direita
*/
void aumentarPrioridadeTarefa(ListaTarefas * todoList, int escolha){
    if(escolha <= 0){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    if(escolha > todoList->tamanhoAtual){
        system("clear");
        printf("A posição escolhida %d não existe na lista\n",escolha);
        printf("Tecle Enter para retornar...");
        getchar();
        system("clear");
        return;
    }
    /*adequando o escolha para o mundo dos vetores (0 a numero de elementos - 1)*/
    escolha = escolha - 1;

    /*Realizando um deslocamento para a direita nos elementos do vetor (0 ao escolha)*/
    Tarefa aux = todoList->listaTarefas[escolha];
    for(int i=escolha;i>0;i--){
        todoList->listaTarefas[i]=todoList->listaTarefas[i-1];
    }
    todoList->listaTarefas[0]=aux;
    system("clear");
    printf("Trocado com sucesso!\n");
    printf("Tecle Enter para retornar...");
    getchar();
    system("clear");
}

/*
 * procedimento para a liberacao da memoria alocada para o conjunto de listas e suas listas de tarefas
*/
void liberarMemoriaAlocada(ConjuntoListasTarefas * conjunto){
    if(conjunto == NULL){
        return;
    }else{
        free(conjunto);
    }
}


