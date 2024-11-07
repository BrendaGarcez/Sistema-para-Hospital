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
void emOrdemArquivo(No *raiz, FILE *arquivo);
void desalocarArvore(No *no);
///arrumar daqui para baixo
///renomear busca pai para buscaporID
No **buscaPai(No **raiz, int k);
void removeNo(No **raiz, int k);
No **ppMenor(No **raiz);

int main()
{
    No *raizId = NULL, *raizNome=NULL, *achouId=NULL, *achouNome=NULL;
    int op=1, op2, op3 = 0, id, idade, totalPacientes, i = 0;
    char nome[20], condicaoMed[20];

        FILE *log = NULL, *arq = NULL;
        log = fopen("Arquivo de saida.txt", "w");
        if (!log) { 
            printf("Erro ao abrir o arquivo de saida.\n");
            return 1;
        }
        arq = fopen("Arquivo de Entrada.txt", "r");
        if (arq == NULL) { 
            printf("Erro ao abrir o arquivo de entrada.\n");
            return 1;
        }
    while (op3 == 0){
        printf("Deseja inserir por:\n");
        printf(" 1- ID \n 2- Nome\n");
        scanf("%d", &op2);
        switch(op2)
        {
        case 1:{
            printf("\nTotal de pacientes: ");
            fscanf(arq,"%d", &totalPacientes);
            printf("%d", totalPacientes);
            while(i < totalPacientes){
                printf("\nDados do paciente: ");
                fscanf(arq,"%d %s %d %s", &id, nome, &idade, condicaoMed);
                printf("\n%d %s %d %s", id, nome, idade, condicaoMed);
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
            printf("%d", totalPacientes);
            printf("ID | Nome | Idade | Condicao Medica");
            while(i < totalPacientes){
                printf("\nInforme os dados do paciente: ");
                fscanf(arq,"%d %s %d %s", &id, nome, &idade, condicaoMed);
                printf("\n%d %s %d %s", id, nome, idade, condicaoMed);
                raizNome = insereNoRecNome(raizId, id, nome, idade, condicaoMed);
                i++;
                }
            op3 = 1;   
        }
        break;
        default:
            printf("\nFalha na insercao!!\n");
            break;
        }
    }

    while(op!=5)
    {
        printf("\n 1-Cadastro de Paciente | 2-Buscar | 3-Remover Paciente | 4-Lista Pacientes | 5-Sair \n");
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
                    raizId = insereNoRec(raizId, id, nome, idade, condicaoMed);
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
                }else if(op2 ==2){
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
                    removeNo(&raizId, id);
                }else if(op2 == 2){
                    printf("Informe o nome do paciente a ser removido: ");
                    scanf("%s", nome);
                }
            }break;
            case 4:{
                if(op2 == 1){
                    printf("\n Lista por ID: \n");
                    emOrdem(raizId);
                }else if(op2 == 2){
                    printf("\n Lista por nome: \n");
                    emOrdem(raizNome);
                }
            }break;
            default:
                printf("tchau! :)");
        }
    }

    if(op2 == 1){    
        emOrdemArquivo(raizId, log);
        printf("\nGravando lista em arquivo....");
    }else if(op2 == 2){
        emOrdemArquivo(raizNome, log);
        printf("\nGravando lista em arquivo....");
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
        printf(" ID:%d | Paciente:%s | Idade:%d | Condicao Medica: %s\n", raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        emOrdem(raiz->dir);
    }
}
void emOrdemArquivo(No *raiz, FILE *arquivo) {
    if (raiz != NULL) {
        emOrdemArquivo(raiz->esq, arquivo);
        fprintf(arquivo, "ID: %d | Paciente: %s | Idade: %d | Condicao Medica: %s\n",
                raiz->id, raiz->nome, raiz->idade, raiz->condicaoMed);
        emOrdemArquivo(raiz->dir, arquivo);
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
      if((*raiz)->id < k){
        raiz = &((*raiz)->dir);
      }else
        raiz = &((*raiz)->esq);
  }
  return raiz;
}
No **ppMenor(No **raiz)//a entrada e o lado direito da �rvore
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