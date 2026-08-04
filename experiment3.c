#include <stdio.h>
#include <pthread.h>

void *reader(void *arg)
{
    printf("Reader Thread Started\n");
    return NULL;
}

void *writer(void *arg)
{
    printf("Writer Thread Started\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, reader, NULL);
    pthread_create(&t2, NULL, writer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main Thread Finished\n");

    return 0;
}