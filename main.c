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
No *insereNoRec(No *raiz, int id, char nome[], int idade, char condicaoMed[]);
No *insereNoRecNome(No *raiz, int id, char nome[], int idade, char condicaoMed[]);
No *buscarNoRecId(No *raiz, int id);
No *buscarNoRecNome(No *raiz, char nome[]);
void emOrdem(No *raiz);
///arrumar daqui para baixo
//No *remover(No *raiz, int chave);
//No **buscaPai(No **raiz, int k);
//void removeNo(No **raiz, int k);
No **ppMenor(No **raiz);

int main()
{
    No *raizId=NULL, *raizNome=NULL, *achouId=NULL, **achouNome=NULL;
    int op=1, id, idade;
    char nome[20], condicaoMed[20];
    while(op!=8)
    {
        printf(" 0-Informe quantos pacientes irá cadastrar \n 1-Cadastro de Paciente \n 2-Buscar por ID \n 3-Buscar por Nome \n 4-Remover Paciente \n 5-Remover paciente por Nome: \n 6-Listar Pacientes por Id \n 7-Lista Pacientes por nome \n 8-Sair \n");
        scanf("%d",&op);
        switch(op)
        {
            case 0:{
                ////para o for
            }break;
            case 1:{
                printf("\nInforme o ID do paciente: ");
                scanf("%d",&id);
                printf("\nInforme o nome do paciente: ");
                scanf("%s", nome);
                printf("\nInforme a idade do paciente: ");
                scanf("%d",&idade);
                printf("\nInforme a condição médica do paciente: ");
                scanf("%s", condicaoMed);

                raizId = insereNoRec(raizId, id, nome, idade, condicaoMed);
                raizNome = insereNoRecNome(raizNome, id, nome, idade, condicaoMed);

            }break;
            case 2:{
                printf("\nInforme o ID:");
                scanf("%d", &id);
                achouId = buscarNoRecId(raizId, id);
                if(achouId)
                {
                    printf(" ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n", achouId->id, achouId->nome, achouId->idade, achouId->condicaoMed);
                }
                else
                    printf("\nPaciente nao encontrado!");

            }break;
            case 3:{
                printf("\nInforme o nome do paciente: ");
                scanf("%s", nome);
                *achouNome = buscarNoRecNome(raizNome, nome);
                if(achouId)
                {
                    printf(" ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n", achouId->id, achouId->nome, achouId->idade, achouId->condicaoMed);
                }
                else
                    printf("\nPaciente nao encontrado!");

            }break;
            case 4:{
                printf("Informe o ID do paciente a ser removido: ");
                scanf("%d",&id);
                //removeNo(&raizId, id);
            }break;
            case 5:{
                printf("Informe o nome do paciente a ser removido: ");
                scanf("%s", nome);
            }break;
            case 6:{
                printf("\n Lista por ID: ");
                emOrdem(raizId);
            }break;
            case 7:{
                printf("\n Lista por nome: ");
                emOrdem(raizNome);
            }break;
        }
    }
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

No *insereNoRec(No *raiz, int id, char nome[], int idade, char condicaoMed[])
{
    if(raiz == NULL)
        return alocaNo(id, nome, idade, condicaoMed);
    else
    {
        if(id < raiz->id)
            raiz->esq = insereNoRec(raiz->esq, id, nome, idade, condicaoMed);
        else
            raiz->dir = insereNoRec(raiz->dir, id, nome, idade, condicaoMed);
    }
    return raiz;
}
No *insereNoRecNome(No *raiz, int id, char nome[], int idade, char condicaoMed[])
{
    if(raiz == NULL)
        return alocaNo(id, nome, idade, condicaoMed);
    else
    {
        if(nome < raiz->nome)
            raiz->esq = insereNoRec(raiz->esq, id, nome, idade, condicaoMed);
        else
            raiz->dir = insereNoRec(raiz->dir, id, nome, idade, condicaoMed);
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
No *buscarNoRecNome(No *raiz, char nome[])
{
    //caso base 1
    if(raiz == NULL)
        return NULL;
    //caso base 2
    if(nome == raiz->nome)
        return raiz;
    else
    {
        if(nome < raiz->nome)
            return buscarNoRecNome(raiz->esq, nome);
        else
            return buscarNoRecNome(raiz->dir, nome);
    }
}
//esq, raiz, dir
void emOrdem(No *raiz){
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf(" ID:%d | Paciente:%s | Idade:%d | Condição Médica: %s\n", raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        emOrdem(raiz->dir);
    }
}

/*void removeNo(No **raiz, int k)
{
    No **pai=NULL;
    if((*raiz) == NULL)
        return;
    pai = buscaPai(raiz, k);
    //1o caso --> remover no folha
    if((*pai)->esq == NULL && (*pai)->dir == NULL)
    {
        free(*pai);
        *pai = NULL;
        return;
    }
    //2o caso --> remover pai com 1 filho apenas
    else{
        if(((*pai)->esq != NULL) != ((*pai)->dir !=NULL))
        {
            if((*pai)->esq != NULL)
            {
                No *paux=(*pai)->esq; //guardando end. filho
                free((*pai));
                *pai = paux;
                
                No *paux=(*pai);
                *pai = (*pai)->esq;
                free(*paux);
                
            }
            if((*pai)->dir != NULL)
            {
                No *paux=(*pai)->dir; //guardando end. filho
                free((*pai));
                *pai = paux;
            }
            return;
        }
        //    3o caso --> remover pai com 2 filhos
        else{
           // if((*pai)->esq != NULL && (*pai)->dir!=NULL)
            {
                No **paux = ppMenor(&(*pai)->dir);
                printf("\n %d", (*paux)->id);
                printf("\nMenor %d %p", (*paux)->id, paux);
                //substituiDados
                (*pai)->id = (*paux)->id;
                printf("\ntrocou chave...");
                removeNo(paux, (*paux)->id);
            }
        }
    }
}*/
