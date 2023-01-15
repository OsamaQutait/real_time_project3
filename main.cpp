#include "local.h"

void read_file() {
    char tmp[30];
    FILE *arguments;
    arguments = fopen("inputData.txt", "r");
    if (arguments == NULL) {
        perror("CANT OPEN FILE");
        exit(1);
    }
    fscanf(arguments, "%s %s %d %d\n", tmp, tmp, &minA, &maxA);
    fscanf(arguments, "%s %s %d %d\n", tmp, tmp, &minB, &maxB);
    fscanf(arguments, "%s %s %d %d\n", tmp, tmp, &minC, &maxC);
    fscanf(arguments, "%s %d\n", tmp, &number_of_line);
    fscanf(arguments, "%s %d\n", tmp, &number_of_employee_of_typeA);
    fscanf(arguments, "%s %d\n", tmp, &number_of_employee_of_typeB);
    fscanf(arguments, "%s %d\n", tmp, &number_of_employee_of_typeC);
}

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

void *line1(void *arg) {
    sleep(1);
    employees c = *(employees *) arg;
    if (c.worker == 0) {
        int z = 1;
        while (1) {
            chocolate coco;
            coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
            pthread_mutex_lock(&coco.chocolate_mutex);
            coco.chocolate_id = z;
            coco.type = 'A';
            coco.finished_steps = 1;
            sleep(generate_waiting_time(minA, maxA));
            queue1[c.line][c.worker].push(coco);
            cout << GREEN << "employee " << c.worker << " produce item with step "
                 << queue1[c.line][c.worker].back().finished_steps << " id " << z << endl;
            fflush(stdout);
            z += 1;
            pthread_mutex_unlock(&coco.chocolate_mutex);
        }
    }
    if (c.worker == 1) {
        while (1) {
            if (!queue1[c.line][c.worker - 1].empty()) {
                chocolate coco = queue1[c.line][c.worker - 1].front();
                queue1[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minA, maxA));
                coco.finished_steps++;
                cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                     << coco.chocolate_id << endl;
                fflush(stdout);
                queue1[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 2) {
        while (1) {
            if (!queue1[c.line][c.worker - 1].empty()) {
                chocolate coco = queue1[c.line][c.worker - 1].front();
                queue1[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minA, maxA));
                coco.finished_steps++;
                cout << BLUE << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                     << coco.chocolate_id << endl;
                fflush(stdout);
                queue1[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 3) {
        while (1) {
            if (!queue1[c.line][c.worker - 1].empty()) {
                chocolate coco = queue1[c.line][c.worker - 1].front();
                queue1[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minA, maxA));
                coco.finished_steps++;
                cout << YELLOW << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                     << coco.chocolate_id << endl;
                fflush(stdout);
                queue1[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 4 || c.worker == 5 || c.worker == 6 || c.worker == 7){
        pthread_mutex_lock(&typeA_l1_mutex[c.line]);
        order[c.line]++;
        pthread_mutex_unlock(&typeA_l1_mutex[c.line]);

        if (order[c.line] == 1){
            while (1){
                if (!queue1[c.line][3].empty()) {
                    chocolate coco = queue1[c.line][3].front();
                    queue1[c.line][3].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    cout << GREEN << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                         << coco.chocolate_id << endl;
                    fflush(stdout);
                    queue1[c.line][4].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 2){
            while (1){
                if (!queue1[c.line][4].empty()) {
                    chocolate coco = queue1[c.line][3].front();
                    queue1[c.line][4].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                         << coco.chocolate_id << endl;
                    fflush(stdout);
                    queue1[c.line][5].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 3){
            while (1){
                if (!queue1[c.line][5].empty()) {
                    chocolate coco = queue1[c.line][3].front();
                    queue1[c.line][5].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                         << coco.chocolate_id << endl;
                    fflush(stdout);
                    queue1[c.line][6].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 4){
            while (1){
                if (!queue1[c.line][6].empty()) {
                    chocolate coco = queue1[c.line][3].front();
                    queue1[c.line][6].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    coco.type = 'A';
                    cout << BLUE << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
                         << coco.chocolate_id << endl;
                    fflush(stdout);
                    queue1[c.line][7].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
    }

    free(arg);
    return NULL;
}

int main() {
    read_file();
    memset(order, 0, sizeof(order));
    pthread_t thread[8];
    for (int i = 0; i < 4; ++i) {
        typeA_l1_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
    }
    for (int i = 0; i < 8; ++i) {
        employees x;
        x.line = 0;
        x.worker = i; //at ane step
        employees *emp = (employees *) malloc(sizeof(employees));
        *emp = x;
        if (pthread_create(thread + i, NULL, &line1, emp) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }
    return 0;
}
