#include <stdio.h>
#include <omp.h>

/* 銀行口座 */
typedef struct {
    char* name;    /* 名前 */
    int   balance; /* 残高 */
    omp_lock_t lock; /* ロック */
} Account;

/* sender から receiver に amount 円を送金する */
static void transfer(Account* sender, Account* receiver, int amount)
{
    // 両方のアカウントをロックするための効果的な方法を選択する
    omp_set_lock(&sender->lock);
    omp_set_lock(&receiver->lock);

    if (sender->balance < amount) {
        omp_unset_lock(&sender->lock);
        omp_unset_lock(&receiver->lock);
        return;
    }
    sender->balance -= amount;
    receiver->balance += amount;

    omp_unset_lock(&sender->lock);
    omp_unset_lock(&receiver->lock);
}

int main()
{
    Account alice = {
        .name = "Alice",
        .balance = 1000,
    };
    Account bob = {
        .name = "Bob",
        .balance = 2000,
    };
    omp_init_lock(&alice.lock);
    omp_init_lock(&bob.lock);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i=0; i<100; i++) {
                transfer(&alice, &bob, 10); /* AliceからBobに10*100円を送金 */
            }
        }

        #pragma omp section
        {
            for (int i=0; i<100; i++) {
                transfer(&bob, &alice, 20); /* BobからAliceに20*100円を送金 */
            }
        }
    }

    printf("Alice: %d yen, Bob: %d yen\n", alice.balance, bob.balance);

    omp_destroy_lock(&alice.lock);
    omp_destroy_lock(&bob.lock);
    return 0;
}