#include <stdio.h>
#include <pthread.h>

void *charging(void *arg)
{
    int ev = *(int *)arg;

    printf("EV %d waiting for charging connectors\n", ev);
    printf("EV %d is charging\n", ev);
    printf("EV %d finished charging and released connectors\n", ev);

    return NULL;
}

int main()
{
    pthread_t t[5];
    int ev[5];

    printf("EV Charging Station Started\n");

    for (int i = 0; i < 5; i++)
    {
        ev[i] = i + 1;
        pthread_create(&t[i], NULL, charging, &ev[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(t[i], NULL);
    }

    return 0;
}
