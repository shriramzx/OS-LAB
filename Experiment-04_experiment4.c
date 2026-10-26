#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 10000;

pthread_mutex_t atm_lock;

void *atm_transaction(void *arg)
{
    int id = *(int *)arg;
    int withdraw = 2000;

    pthread_mutex_lock(&atm_lock);

    printf("ATM %d accessing account...\n", id);
    printf("Current Balance: Rs.%d\n", balance);

    if (balance >= withdraw)
    {
        balance -= withdraw;

        printf("ATM %d withdrew Rs.%d\n", id, withdraw);
        printf("Remaining Balance: Rs.%d\n\n", balance);
    }
    else
    {
        printf("ATM %d: Insufficient Balance\n\n", id);
    }

    pthread_mutex_unlock(&atm_lock);

    return NULL;
}

int main()
{
    pthread_t atm1, atm2;

    int id1 = 1;
    int id2 = 2;

    pthread_mutex_init(&atm_lock, NULL);

    printf("ATM Machine - Mutual Exclusion\n\n");

    pthread_create(&atm1, NULL, atm_transaction, &id1);
    pthread_create(&atm2, NULL, atm_transaction, &id2);

    pthread_join(atm1, NULL);
    pthread_join(atm2, NULL);

    printf("Final Account Balance: Rs.%d\n", balance);

    pthread_mutex_destroy(&atm_lock);

    return 0;
}
