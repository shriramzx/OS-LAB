#include <stdio.h>
#include <pthread.h>

int record = 0;

void *reader(void *arg)
{
    printf("Patient record = %d\n", record);

    return NULL;
}

void *writer(void *arg)
{
    record++;

    printf("Doctor updated record = %d\n", record);

    return NULL;
}

int main()
{
    pthread_t r1, r2, r3, w;

    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&r2, NULL, reader, NULL);
    pthread_create(&r3, NULL, reader, NULL);
    pthread_create(&w, NULL, writer, NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w, NULL);

    return 0;
}
