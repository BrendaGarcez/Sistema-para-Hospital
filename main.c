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
///arrumar daqui para baixo
No *buscarNo(No *raiz, int chave);
No *buscarNoRec(No *raiz, int chave);
void preOrdem(No *raiz);
void emOrdem(No *raiz);
void posOrdem(No *raiz);
//No *remover(No *raiz, int chave);
No **buscaPai(No **raiz, int k);
void removeNo(No **raiz, int k);
No **ppMenor(No **raiz);

int main()
{
    No *raiz=NULL, *achouId=NULL, **achouPai=NULL;
    int op=1, id, idade;
    char nome[20], condicaoMed[20];
    while(op!=5)
    {
        printf("\n1-Cadastro de Paciente \n 2-Buscar por ID \n 3-Buscar por Nome \n 4-Remover Paciente\n 5-Sair:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:{
                printf("\nInforme o ID do paciente: ");
                scanf("%d",&id);
                printf("\nInforme o nome do paciente: ");
                scanf("%s", &nome);
                printf("\nInforme a idade do paciente: ");
                scanf("%d",&idade);
                printf("\nInforme a condição médica do paciente: ");
                scanf("%s", &condicaoMed);

                raiz = insereNoRec(raiz, id, nome, idade, condicaoMed);
            }break;
            case 2:{
                printf("\nInforme o ID:");
                scanf("%d", &id);
                achouId = buscarNoRec(raiz, id);
                if(achouId)
                {
                    printf("Paciente: %s", achouId->nome);
                }
                else
                    printf("\nPaciente nao encontrado!");

            }break;
            case 3:{
                printf("\nInforme o nome do paciente: ");
                scanf("%s", &nome);
                achouId = buscarNoRec(raiz, nome);
                if(achouId)
                {
                    printf("Paciente: %s", achouId->nome);
                }
                else
                    printf("\nPaciente nao encontrado!");

            }break;
            case 4:{
                printf("Informe o ID do paciente a ser removido: ");
                scanf("%d",&id);
                removeNo(&raiz, id);
            }break;
        }
    }

}

No *alocaNoNo(int id, char nome[], int idade, char condicaoMed[])
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
        return novo;
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
    printf("\n\nInserido com sucesso!!");
}

No *buscarNo(No *raiz, int id)
{
    //NO *aux=raiz;
    if(raiz == NULL)
        return NULL;
    else
    {
       while(raiz)
       {
           if(raiz->id == id)
              return raiz;
           else
           {
               if(id < raiz->id)
                    raiz = raiz->esq;
               else
                    raiz = raiz->dir;
           }
       }
    }
}

No *buscarNoRec(No *raiz, int id)
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
            return buscarNoRec(raiz->esq, id);
        else
            return buscarNoRec(raiz->dir, id);
    }
}
//esq, raiz, dir
void emOrdem(No *raiz){
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("ID:%d | Paciente:%s | Idade:%d | Condição Médica: %s", raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        emOrdem(raiz->dir);
    }
}

No **buscaPai(No **raiz, int k)
{
  if (*raiz == NULL)
    return NULL;
  while(*raiz!=NULL)
  {
      if((*raiz)->id == k)
        return raiz;
      if((*raiz)->id < k)
        raiz = &((*raiz)->dir);
      else
        raiz = &((*raiz)->esq);
  }
}

void removeNo(No **raiz, int k)
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
        if(((*pai)->esq != NULL) ^ (*pai)->dir !=NULL)
        {
            if((*pai)->esq != NULL)
            {
                No *paux=(*pai)->esq; //guardando end. filho
                free((*pai));
                *pai = paux;
                /*
                No *paux=(*pai);
                *pai = (*pai)->esq;
                free(*paux);
                */
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
}

No **ppMenor(No **raiz)//a entrada � o lado direito da �rvore
{
    No **pmenor=raiz;
    while((*pmenor)->esq)
    {
        printf("\n%d", (*pmenor)->id);
        pmenor = &(*pmenor)->esq;
    }
    return pmenor;
}