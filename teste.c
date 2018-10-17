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

int fd[2];

node **criarNo(int val, char *filename)
{
    node *temp = NULL;
    temp = (node *)malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->data = val;
    temp->fileName = filename;
    return &temp;
}
insert(&root, criarNo(9, "fodase"));
insert(&root, criarNo(4, "fodase2"));
insert(&root, criarNo(15, "fodas3"));
insert(&root, criarNo(6, "fod4se"));
insert(&root, criarNo(12, "foda5e"));
insert(&root, criarNo(17, "foda6"));
insert(&root, criarNo(2, "fodase7"));

void *operaria(char *file)
{
    FILE *fptr;
    char path[100];
    char word[50];
    int wCount;

    printf("word:\n");
    scanf("%s", word);

    fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }

    char str[BUFFER_SIZE];
    char *pos;
    int index, count;
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

    printf("'%s' is found %d times in file.\n", word, count);
    fclose(fptr);
    pause();
}

void main()
{
    char file[100] = "teste.txt";
    int len = strlen(file) + 1;
    write(fd[1], file, len);
    ler(arquivo(len));

    pthread_t operarias[10];
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&operarias, NULL, operaria("./fileset/teste.txt"), NULL);
    }
    //pthread_kill(operaria, SIGCONT);
}