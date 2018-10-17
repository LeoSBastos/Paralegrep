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
    char path[100] = "./fileset";
    char word[50] = "foda";
    int wCount;
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
    //criaDados("");
    fclose(fptr);

    pause();
}

void ranking()
{
    while (1)
    {
        //pipeoptoran[0]
    }
}

void main()
{
    // char file[100] = "teste.txt";
    // int len = strlen(file) + 1;
    // write(fd[1], file, len);
    // ler(arquivo(len));
    //*pthread_t ranking;
    pthread_t operarias;
    // for(int i=0;i<10;i++){
    // pthread_create(&operarias, NULL, operaria, NULL);
    // }
    pthread_create(&operarias, NULL, operaria("teste.txt"), NULL);
    //*wait(10);
    //*pthread_create(ranking, NULL, ranking(), NULL);
    //pthread_kill(operaria, SIGCONT);
}