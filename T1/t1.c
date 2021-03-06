#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 50

void leAlunos(int *matAlunos, char nomes[][TAM]){

    FILE *arq;

    int mat, i, linha;
    char c, nome[TAM];

    arq = fopen("alunos.txt", "r");
    if(arq==NULL)
        printf("Erro ao abrir o arquivo alunos.txt. Verifique se o arquivo est� com o nome correto ou se ele existe.");
    else{
        linha = 0;
        while(feof(arq)==0){
            if(fscanf(arq, "%i", &mat) != 1)
                break;

            i = 0;
            c = fgetc(arq);
            while(c==' ')
                c = fgetc(arq);

            while(c!='\n' && feof(arq)==0){
                nome[i] = c;
                i++;
                c = fgetc(arq);
            }

            nome[i] = '\0';
            matAlunos[linha] = mat;
            strcpy(nomes[linha], nome);
            linha++;
        }
    }
    matAlunos[linha] = 0;
    fclose(arq);
}

void leNotas(int *matNotas, float *notas){
    FILE *arq;

    int i, mat;
    float a, b;
    arq = fopen("notas.txt", "r");

    if(arq==NULL)
        printf("Erro ao abrir o arquivo notas.txt. Verifique se o arquivo est� com o nome correto ou se ele existe.");
    else{
        i = 0;
        while(feof(arq)==0){
            if(fscanf(arq, "%i %f %f\n", &mat, &a, &b) != 3)
                break;

            matNotas[i] = mat;
            notas[i] = (a+b)/2;
            i++;
        }
    }
    fclose(arq);
}

void imprimeMedia(int *matAlunos, int *matNotas, char nomes[][TAM], float *notas, char *nomeBusca){

    int i, j, flag;
    char temp[TAM];
    i = flag = 0;

    strupr(nomeBusca);

    while(matAlunos[i]>0){
        j = 0;
        strcpy(temp, nomes[i]);
        if(strstr(strupr(temp), nomeBusca)!=NULL){
            flag++;
            while(matAlunos[i] != matNotas[j])
                j++;
            if(flag==1)
                printf("\n MEDIA ..... NOME\n");
            printf("  %.2f ..... %s\n", notas[j], nomes[i]);
        }
        i++;
    }
    if(flag==0)
        printf(" Nenhum resultado encontrado");

}

main(int argc, char **argv){

    int matAlunos[TAM], matNotas[TAM];
    float notas[TAM];
    char nomes[TAM][TAM], *nomeBusca;

    nomeBusca = (char*) malloc(TAM*sizeof(char));

    if(argc > 1){
        strcpy(nomeBusca, argv[1]);
        printf(" Resultado da busca feita por: %s \n", nomeBusca);
    }

    leAlunos(matAlunos, nomes);
    leNotas(matNotas, notas);
    imprimeMedia(matAlunos, matNotas, nomes, notas, nomeBusca);

    free(nomeBusca);

    return 0;
}
