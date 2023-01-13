#include "local.h"
int generate_waiting_time(int lower, int upper) {
    int s, numb;
    FILE *f;
    f = fopen("/dev/urandom", "rb");
    fread(&s, sizeof(int), 1, f);
    fclose(f);
    srand(s);
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void *line1(void *arg){
    employees c = *(employees *)arg;
    pthread_mutex_lock(&typeA_l1_mutex);
    cout << GREEN << c.line << endl;
    cout << GREEN << c.worker << endl;
    cout << BLUE << pthread_self() << endl;
    fflush(stdout);
    pthread_mutex_unlock(&typeA_l1_mutex);
    free(arg);
    return NULL;
}
int main() {
    /*
     * line 1, 2, 3 type A
     * line 4, 5 type B
     * line 5, 6 type C
     *
     * type A has 8 employees
     * type B has 6 employees
     * type C has 5 employees
     */
    pthread_mutex_init(&typeA_l1_mutex, NULL);
    pthread_cond_init(&typeA_l1_cond, NULL);
    pthread_t thread[8];
    for (int i = 0; i < 8; ++i) {
        employees x;
        x.line = 1;
        x.worker = i; //at ane step
        employees *emp = (employees *)malloc(sizeof(employees));
        *emp = x;
        if(pthread_create(thread+i, NULL, &line1, emp) != 0){
            perror("pthread_create");
            exit(-1);
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (pthread_join(thread[i], NULL) != 0){
            perror("pthread_create");
            exit(-1);
        }
    }
    pthread_mutex_destroy(&typeA_l1_mutex);
    pthread_cond_destroy(&typeA_l1_cond);
    return 0;
}
