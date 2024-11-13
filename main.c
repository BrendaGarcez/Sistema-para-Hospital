
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int id;
    char nome[20];
    int idade;
    char condicaoMed[20];
    struct no *dir;
    struct no *esq;
}No;

No *alocaNo(int id, char nome[], int idade, char condicaoMed[]);
No **ppMenor(No **raiz);
void emOrdem(No *raiz, int *i);
void emOrdemArquivo(No *raiz, FILE *arquivo, int *i);
void desalocarArvore(No *no);
int geraNovoId(No* raiz, int id);
//// Funções de ID
No *insereNoRecId(No *raiz, int id, char nome[], int idade, char condicaoMed[]);
No *buscarNoRecId(No *raiz, int id);
int idExistente(No *raiz, int id);
No **buscaPaiId(No **raiz, int k);
void removeNoId(No **raiz, int k);
//// Funções de Nome
No *insereNoRecNome(No *raiz, int id, char nome[], int idade, char condicaoMed[]);
No *buscarNoRecNome(No *raiz, char nome[]);
No **buscaPaiNome(No **raiz, char nome[]);
void removeNoNome(No **raiz, char nome[]);

int main()
{
    No *raizId = NULL, *raizNome=NULL, *achouId=NULL, *achouNome=NULL;
    int op=1, op2, op3 = 0, id, idade, totalPacientes, i = 0;
    char nome[20], condicaoMed[20];

    FILE *log = NULL, *arq = NULL;
    
    arq = fopen("Arquivo de Entrada.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    log = fopen("Arquivo de saida.txt", "w");
    if (!log) {
        printf("Erro ao abrir o arquivo de saida.\n");
        return 1;
    }

    ///Menu de inserção para escolha de Árvore
    while (op3 == 0){
        printf("Deseja inserir por:\n");
        printf(" 1- ID \n 2- Nome\n");
        scanf("%d", &op2);
        switch(op2)
        {
        case 1:{
            printf("\nRecebendo total de pacientes: ");
            fscanf(arq,"%d", &totalPacientes);
            printf("%d", totalPacientes);
            printf("\nDados do paciente: ");
            printf("\nID | Nome | Idade | Condicao Medica");
            int res;
            while(i < totalPacientes && (res = fscanf(arq, "%d %s %d %s", &id, nome, &idade, condicaoMed ))== 4)
            {
                printf("\n%d %s %d %s", id, nome, idade, condicaoMed);
                raizId = insereNoRecId(raizId, id, nome, idade, condicaoMed);
                i++;
            }
            if (res != 4) {
                printf("\nErro: numero de registros no arquivo e menor que o total de pacientes informado.\n");
                break;
            }
                if (i < totalPacientes) {
                    printf("\nAviso: Nem todos os pacientes informados foram processados. Total no arquivo menor que o informado.\n");
                }
                if (res == EOF && !feof(arq)) {
                    int op4 = 1;
                    printf("\nAviso: O arquivo contem mais registros que o total de pacientes informado. Deseja adicionar?(1 - Sim 2 - Nao)\n");
                    scanf("%d", &op4);
                    if (op4 == 1) {

                        while (fscanf(arq, "%d %s %d %s", &id, nome, &idade, condicaoMed) == 4) {
                            printf("\n%d | %s | %d | %s", id, nome, idade, condicaoMed);
                            raizId = insereNoRecId(raizId, id, nome, idade, condicaoMed);
                        }
                    } else {
                        printf("\nRegistros adicionais incompletos.\n");
                    }
                }
            printf("\nTotal de pacientes registrados: %d\n", i);
            op3 = 1;
        }
        break;
        case 2:{
            printf("\nRecebendo total de pacientes: ");
            fscanf(arq,"%d", &totalPacientes);
            printf("%d", totalPacientes);
            printf("\nDados dos pacientes: ");
            printf("ID | Nome | Idade | Condicao Medica");
            int res;
            while(i < totalPacientes && (res = fscanf(arq, "%d %s %d %s", &id, nome, &idade, condicaoMed ))== 4)
            {
                printf("\n%d %s %d %s", id, nome, idade, condicaoMed);
                raizNome = insereNoRecNome(raizNome, id, nome, idade, condicaoMed);
                i++;
            }
            if (res != 4) {
                printf("\nErro: numero de registros no arquivo e menor que o total de pacientes informado.\n");
                break;
            }
                if (i < totalPacientes) {
                    printf("\nAviso: Nem todos os pacientes informados foram processados. Total no arquivo menor que o informado.\n");
                }
                if (res == EOF && !feof(arq)) {
                    int op4 = 1;
                    printf("\nAviso: O arquivo contem mais registros que o total de pacientes informado. Deseja adicionar?(1 - Sim 2 - Nao)\n");
                    scanf("%d", &op4);
                    if (op4 == 1) {

                        while (fscanf(arq, "%d %s %d %s", &id, nome, &idade, condicaoMed) == 4) {
                            printf("\n%d | %s | %d | %s", id, nome, idade, condicaoMed);
                            raizNome = insereNoRecNome(raizNome, id, nome, idade, condicaoMed);
                        }
                    } else {
                        printf("\nRegistros adicionais incompletos.\n");
                    }
                }
            printf("\nTotal de pacientes registrados: %d\n", i);
            op3 = 1;
        }
        break;
        default:
            printf("\nFalha na insercao!!\n");
            break;
        }
    }
    ///Menu para manipulação de informações
    int gravado = 0;
    while(op!=6)
    {
        printf("\n 1-Cadastro de Paciente | 2-Buscar | 3-Remover Paciente | 4-Lista Pacientes | 5- Gravar em Arquivo de Texto | 6- Sair \n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:{
                printf("\nInforme o ID do paciente: ");
                scanf("%d",&id);
                printf("\nInforme o nome do paciente: ");
                scanf("%s", nome);
                printf("\nInforme a idade do paciente: ");
                scanf("%d",&idade);
                printf("\nInforme a condicao medica do paciente: ");
                scanf("%s", condicaoMed);
                if(op2 == 1){
                    raizId = insereNoRecId(raizId, id, nome, idade, condicaoMed);
                }else if(op2 == 2){
                    raizNome = insereNoRecNome(raizNome, id, nome, idade, condicaoMed);
                }
            }break;
            case 2:{
                if(op2 == 1){
                    printf("\nInforme o ID:");
                    scanf("%d", &id);
                    achouId = buscarNoRecId(raizId, id);
                    if(achouId)
                    {
                        printf(" ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n", achouId->id, achouId->nome, achouId->idade, achouId->condicaoMed);
                    }
                    else{
                        printf("\nPaciente nao encontrado!");
                    }
                }else if(op2 == 2){
                    printf("\nInforme o nome do paciente: ");
                    scanf("%s", nome);
                    achouNome = buscarNoRecNome(raizNome, nome);
                    if(achouNome)
                    {
                        printf(" ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n", achouNome->id, achouNome->nome, achouNome->idade, achouNome->condicaoMed);
                    }
                    else{
                        printf("\nPaciente nao encontrado!");
                    }
                }
            }break;
            case 3:{
                if(op2 == 1){
                    printf("Informe o ID do paciente a ser removido: ");
                    scanf("%d",&id);
                    removeNoId(&raizId, id);
                }else if(op2 == 2){
                    printf("Informe o nome do paciente a ser removido: ");
                    scanf("%s", nome);
                    removeNoNome(&raizNome, nome);

                }
            }break;
            case 4:{
                int j = 0;
                if(op2 == 1){
                    printf("\n Lista por ID: \n");
                    emOrdem(raizId, &j);
                    printf("Total de pacientes: %d \n", j);
                }else if(op2 == 2){
                    printf("\n Lista por nome: \n");
                    emOrdem(raizNome, &j);
                    printf("Total de pacientes: %d \n", j);
                }
            }break;
            case 5:{
                int j = 0;
                if(op2 == 1){
                    emOrdemArquivo(raizId, log, &j);
                }else if(op2 == 2){
                    emOrdemArquivo(raizNome, log, &j);
                }
                printf("\nGravando lista em arquivo....");
                fprintf(log, "Total de Pacientes %d", j);
                gravado = 1;
            }break;
            default:
                printf("tchau! :)");
            break;
        }
    }

    ///Caso a gravação em arquivo de saida do menu não seja ativada 
    int j = 0;
    if (gravado == 0) {
        if(op2 == 1){
            emOrdemArquivo(raizId, log, &j);
        }else if(op2 == 2){
            emOrdemArquivo(raizNome, log, &j);
        }
        printf("\nGravando lista em arquivo....");
        fprintf(log, "Total de Pacientes %d", j);
    }

    desalocarArvore(raizId);
    desalocarArvore(raizNome);
    fclose(log);
    fclose(arq);
    return 0;
}

No *alocaNo(int id, char nome[], int idade, char condicaoMed[])
{
    No *novo=NULL;
    novo = (No *)malloc(sizeof(No));
    if(novo)
    {
        novo->id = id;
        strcpy(novo->nome, nome);
        novo->idade = idade;
        strcpy(novo->condicaoMed, condicaoMed);
        novo->dir = NULL;
        novo->esq = NULL;
    }
    return novo;
}
//a entrada e o lado direito da arvore
No **ppMenor(No **raiz)
{
    No **pmenor=raiz;
    while((*pmenor)->esq)
    {
        pmenor = &(*pmenor)->esq;
    }
    return pmenor;
}
//esq, raiz, dir
void emOrdem(No *raiz, int *i){
    if (raiz != NULL) {
        emOrdem(raiz->esq, i);
        printf(" ID:%d | Paciente:%s | Idade:%d | Condicao Medica: %s\n", raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        (*i)++;
        emOrdem(raiz->dir, i);
    }
}
/// Listagem de Pacientes em Arquivo in-order
void emOrdemArquivo(No *raiz, FILE *arquivo, int *i) {
    if (raiz != NULL) {
        emOrdemArquivo(raiz->esq, arquivo, i);
        fprintf(arquivo, "ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n",
                raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        (*i)++;
        emOrdemArquivo(raiz->dir, arquivo, i);
    }
}

void desalocarArvore(No *no) {
    if (no == NULL) {
        return;
    }
    desalocarArvore(no->esq);
    desalocarArvore(no->dir);
    free(no);
    no = NULL;
}

///Funcoes ID
No *insereNoRecId(No *raiz, int id, char nome[], int idade, char condicaoMed[]) {
    if (raiz == NULL) {
        return alocaNo(id, nome, idade, condicaoMed);
    } else {
        if(strcmp(raiz->nome, nome) == 0){
            printf("\n Paciente ja inserido\n");
            return raiz;
        }
        if (id == raiz->id) {
            if (strcmp(raiz->nome, nome) == 0) {
                printf("Erro: O nome '%s' ja existe com o ID %d. Nao foi possivel inserir.\n", nome, id);
                return raiz;
            } else {
                int novoId = id;
                do {
                    novoId++;
                    printf("\nO ID ja existe. Tentando o ID %d...\n", novoId);
                } while (idExistente(raiz, novoId));
                novoId = geraNovoId(raiz, novoId);

                printf("Novo ID disponivel: %d. Inserindo o paciente com esse ID.\n", novoId);
                if (novoId < raiz->id) {
                    raiz->esq = insereNoRecId(raiz->esq, novoId, nome, idade, condicaoMed);
                } else {
                    raiz->dir = insereNoRecId(raiz->dir, novoId, nome, idade, condicaoMed);
                }
                printf("%d %s %d %s", novoId, nome, idade, condicaoMed);
                return raiz;
            }
        } else if (id < raiz->id) {
            raiz->esq = insereNoRecId(raiz->esq, id, nome, idade, condicaoMed);
        } else {
            raiz->dir = insereNoRecId(raiz->dir, id, nome, idade, condicaoMed);
        }
    }
    return raiz;
}

No *buscarNoRecId(No *raiz, int id)
{
    //caso base 1
    if(raiz == NULL)
        return NULL;
    //caso base 2
    if(id == raiz->id)
        return raiz;
    else
    {
        if(id < raiz->id)
            return buscarNoRecId(raiz->esq, id);
        else
            return buscarNoRecId(raiz->dir, id);
    }
}
/// Verifica tanto na inserção de nome quanto de ID se os IDs já estão na lista
int idExistente(No *raiz, int id) {
    if (raiz == NULL) {
        return 0;
    }
    if (raiz->id == id) {
        return 1;
    }
    return (id < raiz->id) ? idExistente(raiz->esq, id) : idExistente(raiz->dir, id);
}

/// Usada na remoção
No **buscaPaiId(No **raiz, int k)
{
  if (*raiz == NULL)
    return NULL;
  while(*raiz!=NULL)
  {
      if((*raiz)->id == k)
        return raiz;
      if((*raiz)->id < k){
        raiz = &((*raiz)->dir);
      }else
        raiz = &((*raiz)->esq);
  }
  return raiz;
}

void removeNoId(No **raiz, int k)
{
    No **pai=NULL;
    if((*raiz) == NULL)
        return;
    pai = buscaPaiId(raiz, k);
    //1o caso --> remover no folha
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
    {
        free(*pai);
        *pai = NULL;
        return;
    }
    //2o caso --> remover pai com 1 filho apenas
    else if((((*pai)->esq == NULL ) && ((*pai)->dir !=NULL)) || (((*pai)->esq != NULL) && ((*pai)->dir ==NULL))){
            if((*pai)->esq != NULL)
            {
                No *paux=(*pai);
                *pai = (*pai)->esq;
                free(paux);
                paux = NULL;
            }
            if((*pai)->dir != NULL)
            {
                No *paux=(*pai);
                *pai = (*pai)->dir;
                printf("Paciente sendo removido: %s\n", paux->nome);
                free(paux);
                paux = NULL;
                if(paux){
                    printf("a Remocao deu errado!\n");
                }else
                printf("Remocao realizada!\n");
            }
            return;
    }
    //    3o caso --> remover pai com 2 filhos
    else{
            if((*pai)->esq != NULL && (*pai)->dir!=NULL)
            {
                No **paux = ppMenor(&(*pai)->dir);
                printf("\n %d", (*paux)->id);
                (*pai)->id = (*paux)->id;
                strcpy((*pai)->nome, (*paux)->nome);
                (*pai)->idade = (*paux)->idade;
                strcpy((*pai)->condicaoMed, (*paux)->condicaoMed);
                removeNoId(paux, (*paux)->id);
            }
            printf("\nRemovido com Sucesso!\n");
        }
}
/// Gera novos Ids para evitar duplicatas
int geraNovoId(No* raiz, int id) {
    int novoId = id;
    while (idExistente(raiz, novoId)) {
        printf("ID ja existente. Atribuindo ID: %d...\n", novoId++);
        novoId++;
    }
    return novoId;
}

/// Funcoes NOME
///Não aceita pacientes com nomes iguais mesmo, o projeto pede que não tenha nomes iguais
No* insereNoRecNome(No *raiz, int id, char nome[], int idade, char condicaoMed[]) {
    if (raiz == NULL) {
        return alocaNo(id, nome, idade, condicaoMed);
    }

    if (strcmp(nome, raiz->nome) == 0) {  
            printf("\nPaciente ja inserido!\n");
            return raiz;
    }
    if (idExistente(raiz, id)) {
        id = geraNovoId(raiz, id);
    }
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0) {
        raiz->esq = insereNoRecNome(raiz->esq, id, nome, idade, condicaoMed);
    } else {
        raiz->dir = insereNoRecNome(raiz->dir, id, nome, idade, condicaoMed);
    }
    return raiz;
}


No *buscarNoRecNome(No *raiz, char nome[])
{
    //caso base 1
    if(raiz == NULL)
        return NULL;
    //caso base 2
    if(strcmp(nome, raiz->nome) == 0)
        return raiz;
    else
    {
        if(strcmp(nome, raiz->nome) < 0)
            return buscarNoRecNome(raiz->esq, nome);
        else
            return buscarNoRecNome(raiz->dir, nome);
    }
}

No **buscaPaiNome(No **raiz, char nome[])
{
  if (*raiz == NULL)
    return NULL;
  while(*raiz!=NULL)
  {
      if(strcmp((*raiz)->nome, nome) == 0)
        return raiz;
      if(strcmp((*raiz)->nome, nome) < 0){
        raiz = &((*raiz)->dir);
      }else
        raiz = &((*raiz)->esq);
  }
  return raiz;
}

void removeNoNome(No **raiz, char nome[])
{
    No **pai=NULL;
    if((*raiz) == NULL)
        return;
    pai = buscaPaiNome(raiz, nome);
    //1o caso --> remover no folha
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
    {
        free(*pai);
        *pai = NULL;
        return;
    }
    //2o caso --> remover pai com 1 filho apenas
    else{
        if((((*pai)->esq == NULL ) && ((*pai)->dir !=NULL)) || (((*pai)->esq != NULL) && ((*pai)->dir ==NULL)))
        {
            if((*pai)->esq != NULL)
            {
                No *paux=(*pai);
                *pai = (*pai)->esq;
                free(paux);
                paux = NULL;
                printf("Remocao realizada!\n");
            }
            if((*pai)->dir != NULL)
            {
                No *paux=(*pai);
                *pai = (*pai)->dir;
                printf("Paciente sendo removido: %s\n", paux->nome);
                free(paux);
                paux = NULL;
                if(paux){
                    printf("a Remocao deu errado!\n");
                }else
                printf("Remocao realizada!\n");
            }
            return;
        }
        //    3o caso --> remover pai com 2 filhos
        else{
            if((*pai)->esq != NULL && (*pai)->dir!=NULL)
            {
                No **paux = ppMenor(&(*pai)->dir);
                printf("\n %d", (*paux)->id);
                (*pai)->id = (*paux)->id;
                strcpy((*pai)->nome, (*paux)->nome);
                (*pai)->idade = (*paux)->idade;
                strcpy((*pai)->condicaoMed, (*paux)->condicaoMed);
                removeNoNome(paux, (*paux)->nome);
            }
            printf("\nRemovido com Sucesso!\n");
        }
    }
}
