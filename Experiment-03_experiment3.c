#include <pthread.h>
#include <stdio.h>

typedef struct {
    int first;
    int last;
    long long sum;
} ThreadData;

static void *sum_range(void *argument)
{
    ThreadData *data = argument;
    data->sum = 0;
    for (int value = data->first; value <= data->last; ++value)
        data->sum += value;
    return NULL;
}

int main(void)
{
    enum { THREADS = 4, MAX_VALUE = 1000 };
    pthread_t threads[THREADS];
    ThreadData data[THREADS];
    const int chunk = MAX_VALUE / THREADS;
    long long total = 0;

    for (int i = 0; i < THREADS; ++i) {
        data[i].first = i * chunk + 1;
        data[i].last = (i + 1) * chunk;
        if (pthread_create(&threads[i], NULL, sum_range, &data[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
        printf("Thread %d sum = %lld\n", i + 1, data[i].sum);
        total += data[i].sum;
    }

    printf("Total sum = %lld\n", total);
    return 0;
}
