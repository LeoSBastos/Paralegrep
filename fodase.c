#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define cont 3

sem_t semaphore;
pthread_cond_t th_cond;   // threads wait on this
pthread_mutex_t th_mutex; // mutex to protect the signal
int busyThreads = 3;
pthread_cond_t m_cond;   // main thread waits on this
pthread_mutex_t m_mutex; // mutex to protect main signal

thread_execute(int i)
{
    while (i > 0)
    {
        printf("Thread %d iniciada", i + 1);
        pthread_mutex_lock(&th_mutex);
        --busyThreads;
        printf("Esperando Sinal porque Thread %d vai dormir", i + 1);
        pthread_cond_wait(&th_cond, &th_mutex);
        printf("Sinal recebido");
        pthread_mutex_unlock(&th_mutex);
        i = 0;
    }

    pthread_exit(NULL);
}

int main()
{
    sem_init(&semaphore, 0, 0);
    spawn_threads();

    // Dispatch first job
    int semvalue = 0;

    pthread_mutex_lock(&m_mutex);
    while (busyThreads > 0) // check number of active workers
        pthread_cond_wait(&m_cond, &m_mutex);
    pthread_mutex_unlock(&m_mutex);

    busyThreads = MAX_THREADS;
    pthread_mutex_lock(&th_mutex);
    printf("Enviando sinal");
    pthread_cond_broadcast(&th_cond); // signal all workers to resume
    pthread_mutex_unlock(&th_mutex);

    // same for JOBS_2;

    jobs[0...MAX_THREADS] = -1; // No more jobs
    pthread_join();
    return 0;
}