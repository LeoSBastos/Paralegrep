#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include "arvore.h"
#define BUFFER_SIZE 1000

int pipeoptoran[2];

void *operaria(char *filename)
{
    FILE *fptr;
    char path[100] = "./fileset/";
    char word[50] = "foda";
    strcat(path, filename);
    //printf("word:\n");
    //scanf("%s", word);
    fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }

    char str[BUFFER_SIZE];
    char *pos;
    int index, count, deucerto;
    count = 0;
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        index = 0;
        while ((pos = strstr(str + index, word)) != NULL)
        {
            index = (pos - str) + 1;
            count++;
        }
    }
    printf("'%s' foi encontrado %d vezes no arquivo.\n", word, count);
    Data dados;
    dados.filename = filename;
    dados.data = count;
    printf("%s -> %d\n", dados.filename, dados.data);
    deucerto = write(pipeoptoran[1], &dados, sizeof(dados));
    if (deucerto != 1)
    {
        perror("write");
        exit(2);
    }
    fclose(fptr);
    close(pipeoptoran[1]);
    exit(1);
}

void *ranking()
{
    printf("cuzao");
    int deucerto;
    node *arvore = NULL;
    Data dados;
    deucerto = read(pipeoptoran[0], &dados, sizeof(dados));
    printf("%d", deucerto);

    // if (deucerto != 1)
    // {
    //     perror("read");
    //     exit(3);
    // }
    printf("%s -> %d", dados.filename, dados.data);
    insert(&arvore, dados);
    print_inorder(arvore);
    close(pipeoptoran[0]);
}

void main()
{
    int t;
    t = pipe(pipeoptoran);
    if (t < 0)
    {
        perror("pipe ");
        exit(1);
    }
    // char file[100] = "teste.txt";
    // int len = strlen(file) + 1;
    // write(fd[1], file, len);
    // ler(arquivo(len));
    pthread_t rankthread;
    pthread_t operarias;
    // for(int i=0;i<10;i++){
    // pthread_create(&operarias, NULL, operaria, NULL);
    // }
    pthread_create(&operarias, NULL, operaria("teste.txt"), NULL);
    pthread_create(&rankthread, NULL, ranking(), NULL);
    //pthread_kill(operaria, SIGCONT);
}