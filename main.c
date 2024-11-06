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
No *buscarNoRecId(No *raiz, int id);
No *insereNoRecNome(No *raiz, int id, char nome[], int idade, char condicaoMed[]);
No *buscarNoRecNome(No *raiz, char nome[]);
void emOrdem(No *raiz);
void desalocarArvore(No *no);
///arrumar daqui para baixo
///renomear busca pai para buscaporID
No **buscaPai(No **raiz, int k);
void removeNo(No **raiz, int k);
No **ppMenor(No **raiz);

int main()
{
    No *raizId = NULL, *raizNome=NULL, *achouId=NULL, *achouNome=NULL;
    int op=1, op2, op3 = 0, id, idade, totalPacientes, i;
    char nome[20], condicaoMed[20];

        FILE *log = NULL, *arq = NULL;
        log = fopen("Arquivo de saida.txt", "w");
        if (!log) { 
            printf("Erro ao abrir o arquivo de saida.\n");
            return 1;
        }
        arq = fopen("Arquivo de entrada.txt", "r");
        if (!arq) { 
            printf("Erro ao abrir o arquivo de entrada.\n");
            return 1;
        }
    while (op3 == 0){
        printf("Deseja inserir por:\n");
        printf(" 1 - ID\n 2-Nome\n");
        scanf("%d", &op2);
        switch(op2)
        {
        case 1:{
                printf("\n Total de pacientes: ");
                fscanf(arq,"%d", &totalPacientes);
                while(i < totalPacientes){
                    printf("\nInforme o ID do paciente: ");
                    fscanf(arq,"%d",&id);
                    printf("\nInforme o nome do paciente: ");
                    fscanf(arq,"%s", nome);
                    printf("\nInforme a idade do paciente: ");
                    fscanf(arq,"%d",&idade);
                    printf("\nInforme a condição médica do paciente: ");
                    fscanf(arq,"%s", condicaoMed);
                    raizId = insereNoRec(raizId, id, nome, idade, condicaoMed);
                    i++;
                }
            op3 = 1;    
        }
        break;
        case 2:{
            i = 0;
            printf("\n Total de pacientes: ");
            fscanf(arq,"%d", &totalPacientes);
            while(i < totalPacientes){
                printf("\nInforme o ID do paciente: ");
                fscanf(arq,"%d",&id);
                printf("\nInforme o nome do paciente: ");
                fscanf(arq,"%s", nome);
                printf("\nInforme a idade do paciente: ");
                fscanf(arq,"%d",&idade);
                printf("\nInforme a condição médica do paciente: ");
                fscanf(arq,"%s", condicaoMed);
                raizNome = insereNoRecNome(raizId, id, nome, idade, condicaoMed);
                i++;
                }
            op3 = 1;   
        }
        break;
        default:
            printf("\nFalha na inserção!!\n");
            break;
        }
    }

    system("cls");
    /////rodara para talvez outra inserçao e busca e remoção
    while(op!=9)
    {
        printf("\n 1-Cadastro de Paciente por ID | 2-Cadastro de Paciente por Nome | 3-Buscar por ID | 4-Buscar por Nome | 5-Remover Paciente | 6-Remover paciente por Nome: | 7-Listar Pacientes por Id | 8-Lista Pacientes por nome | 9-Sair \n");
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
                printf("nao feito ainda");
            }break;
            case 3:{
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
            case 4:{
                printf("\nInforme o nome do paciente: ");
                scanf("%s", nome);
                achouNome = buscarNoRecNome(raizNome, nome);
                if(achouNome)
                {
                    printf(" ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n", achouNome->id, achouNome->nome, achouNome->idade, achouNome->condicaoMed);
                }
                else
                    printf("\nPaciente nao encontrado!");

            }break;
            case 5:{
                printf("Informe o ID do paciente a ser removido: ");
                scanf("%d",&id);
                removeNo(&raizId, id);
            }break;
            case 6:{
                printf("Informe o nome do paciente a ser removido: ");
                scanf("%s", nome);
            }break;
            case 7:{
                printf("\n Lista por ID: ");
                emOrdem(raizId);
            }break;
            case 8:{
                printf("\n Lista por nome: ");
                emOrdem(raizNome);
            }break;
            default:
            printf("tchau! :)");
        }
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
        if(strcmp(nome, raiz->nome) < 0)
            raiz->esq = insereNoRecNome(raiz->esq, id, nome, idade, condicaoMed);
        else
            raiz->dir = insereNoRecNome(raiz->dir, id, nome, idade, condicaoMed);
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
//esq, raiz, dir
void emOrdem(No *raiz){
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf(" ID:%d | Paciente:%s | Idade:%d | Condição Médica: %s\n", raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        emOrdem(raiz->dir);
    }else
    printf("A lista está vazia!\n");
    
}

No **buscaPai(No **raiz, int k)
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
No **ppMenor(No **raiz)//a entrada � o lado direito da �rvore
{
    No **pmenor=raiz;
    while((*pmenor)->esq)
    {
        pmenor = &(*pmenor)->esq;
    }
    return pmenor;
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
        if((((*pai)->esq == NULL ) && ((*pai)->dir !=NULL)) || (((*pai)->esq != NULL) && ((*pai)->dir ==NULL)))
        {
            if((*pai)->esq != NULL)
            {
                No *paux=(*pai);
                *pai = (*pai)->esq;
                free(paux);
                
            }
            if((*pai)->dir != NULL)
            {
                No *paux=(*pai);
                *pai = (*pai)->dir;
                printf("Paciente sendo removido: %s\n", paux->nome);
                free(paux);
                if(paux){
                    printf("a Remoção deu errado!\n");
                }else
                printf("Remoção realizada!\n");
            }
            return;
        }
        //    3o caso --> remover pai com 2 filhos
        else{
            if((*pai)->esq != NULL && (*pai)->dir!=NULL)
            {
                No **paux = ppMenor(&(*pai)->dir);
                printf("\n %d", (*paux)->id);
                printf("\nMenor %d %p", (*paux)->id, paux);
                //substituiDados
                (*pai)->id = (*paux)->id;
                printf("\ntrocou chave...");
                removeNo(paux, (*paux)->id);
            }
            printf("\nRemovido com Sucesso!\n");
        }
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