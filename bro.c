#define _REENTRANT
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

void handler()
{
    printf("Handled SIGINT\n");
}
void *thread_routine(void *arg)
{
    if (jobs[tid] == 0)
        continue; // no job
    if (jobs[tid] == JOBS_1)
    {
        jobs1();
        jobs[tid] = 0; // go back to idle state
        pthread_mutex_lock(&th_mutex);
        pthread_mutex_lock(&m_mutex);
        --busyThreads;                // one less worker
        pthread_cond_signal(&m_cond); // signal main to check progress
        pthread_mutex_unlock(&m_mutex);
        pthread_cond_wait(&th_cond, &th_mutex); // wait for next job
        pthread_mutex_unlock(&th_mutex);
    }
    if (jobs[tid] == JOBS_2)
    {
        printf("Started thread_routine\n");

        sleep(5);

        printf("Ending thread_routine\n");
        return arg;
    }
}
int main(int argc, char *argv[])
{
    int status;
    pthread_t thread_id;
    void *thread_result;
    struct sigaction act;

    memset(&act, '\0', sizeof(sigaction));
    act.sa_handler = handler;
    sigaction(SIGINT, &act, NULL);

    status = pthread_create(&thread_id, NULL, thread_routine, NULL);
    if (status != 0)
    {
        printf("pthread_create status = %d\n", status);
        return 0;
    }
    sleep(1); /* Give child thread time to get started */

    pthread_kill(thread_id, SIGINT);

    printf("Before sleep\n");
    pthread_join(thread_id, &thread_result);

    sleep(1); /* Give child thread time to terminate */
    printf("After sleep\n");

    return 0;
}