#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t *mutex;
int balance = 1000;

void *withdraw_money(void *arg)
{
    int amount = *(int *)arg;

    sem_wait(mutex);

    if (balance >= amount) {
        int before = balance;
        balance -= amount;
        printf("Withdrawal: %d\n", amount);
        printf("Balance: %d -> %d\n", before, balance);
    } else {
        printf("Withdrawal of %d declined. Balance = %d\n",
               amount, balance);
    }

    sem_post(mutex);
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int amount1 = 700, amount2 = 500;

    mutex = sem_open("/atm_mutex_oslab", O_CREAT, 0600, 1);
    if (mutex == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    pthread_create(&t1, NULL, withdraw_money, &amount1);
    pthread_create(&t2, NULL, withdraw_money, &amount2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final balance = %d\n", balance);

    sem_close(mutex);
    sem_unlink("/atm_mutex_oslab");
    return 0;
}
