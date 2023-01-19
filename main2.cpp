#include "local.h"
//#include <bits/stdc++.h>

void read_file();

int generate_waiting_time(int lower, int upper);

void *typeA(void *arg);

void *typeB(void *arg);

void *typeC(void *arg);

void *line_8(void *arg);

void *containers(void *arg);

void *carton_boxes(void *arg);

void *storage_boxes(void *arg);

void *trucks(void *arg);

void startOpenGl();

void display();

void reshape(int w, int h);

void renderBitMap(char *string, void *font, float x, float y);

void border();

void Arrow(int x, int y);

void Arrow2(int x, int y);

void TypesManuRooms();

void ExpirationDManuline();

void ContainersSection();

void Boxes();

void Storage();

void LoadingIntoTrucks();

char TypeAcountsSting[256];
char TypeBcountsSting[256];
char TypeCcountsSting[256];
char PatchNumSting[256];
char title[100];
char ExpNumASting[256];
char ExpNumBSting[256];
char ExpNumCSting[256];

char ContACapString[256];
char ContBCapString[256];
char ContCCapString[256];

char FullCartonANumSting[256];
char FullCartonBNumSting[256];
char FullCartonCNumSting[256];

char FullCartonNumSting[256];
char CartonNumSting[256];
char T1CapacitySting[256];
char T2CapacitySting[256];
char T3CapacitySting[256];
int PatchNum = 10;


int FullCartonANum = 10;
int FullCartonBNum = 10;
int FullCartonCNum = 10;
int CartonNum = 10;
int T1Capacity = 10;
int T2Capacity = 10;
int T3Capacity = 10;

bool typeA_employee_working[3][8];
bool typeB_employee_working[2][6];
bool typeC_employee_working[2][5];

void init() {
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
}


int main(int argc, char **argv) {

    read_file();

    memset(order, 0, sizeof(order));
    memset(order1, 0, sizeof(order1));

    total_queue = PTHREAD_MUTEX_INITIALIZER;
    total_queue_printing = PTHREAD_MUTEX_INITIALIZER;
    carton_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_cond_init(&line8_cond, NULL);
    pthread_cond_init(&storage_area_cond, NULL);
    for (int i = 0; i < 4; ++i) {
        typeA_l1_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
    }
    for (int i = 0; i < 2; ++i) {
        typeC_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
    }
    // type A
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 8; ++i) {
            employees x;
            x.line = j;
            x.worker = i; //at ane step
            employees *emp = (employees *) malloc(sizeof(employees));
            *emp = x;
            if (pthread_create(&thread[j][i], NULL, &typeA, emp) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }
    // type B
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 6; ++i) {
            employees x;
            x.line = j;
            x.worker = i; //at ane step
            employees *emp = (employees *) malloc(sizeof(employees));
            *emp = x;
            if (pthread_create(&thread1[j][i], NULL, &typeB, emp) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }
    // type C
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 5; ++i) {
            employees x;
            x.line = j;
            x.worker = i; //at ane step
            employees *emp = (employees *) malloc(sizeof(employees));
            *emp = x;
            if (pthread_create(&thread2[j][i], NULL, &typeC, emp) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }
    // TWO EMPLOYEE FOR DATE
    for (int i = 0; i < 2; ++i) {
        employees x;
        x.line = 8;
        x.worker = i; //at ane step
        employees *emp = (employees *) malloc(sizeof(employees));
        *emp = x;
        if (pthread_create(&thread3[i], NULL, &line_8, emp) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }

    //containers employee

    for (int i = 0; i < 3; ++i) {
        employees x;
        x.worker = i; //at ane step
        employees *emp = (employees *) malloc(sizeof(employees));
        *emp = x;
        if (pthread_create(&thread4[i], NULL, &containers, emp) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }
    // boxes employee
    for (int i = 0; i < 3; ++i) {
        employees x;
        x.worker = i; //at ane step
        employees *emp = (employees *) malloc(sizeof(employees));
        *emp = x;
        if (pthread_create(&thread5[i], NULL, &carton_boxes, emp) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }

    // storage employee
    for (int i = 0; i < 2; ++i) {
        employees x;
        x.worker = i; //at ane step
        employees *emp = (employees *) malloc(sizeof(employees));
        *emp = x;
        if (pthread_create(&thread6[i], NULL, &storage_boxes, emp) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }

    // storage employee
    for (int i = 0; i < 2; ++i) {
        employees x;
        x.worker = i; //at ane step
        employees *emp = (employees *) malloc(sizeof(employees));
        *emp = x;
        if (pthread_create(&thread7[i], NULL, &trucks, emp) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }

    glutInit(&argc, argv);
    startOpenGl();

    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 8; ++i) {
            if (pthread_join(thread[j][i], NULL) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 6; ++i) {
            if (pthread_join(thread1[j][i], NULL) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 5; ++i) {
            if (pthread_join(thread2[j][i], NULL) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (pthread_join(thread3[i], NULL) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (pthread_join(thread4[i], NULL) != 0) {
            perror("pthread_create");
            exit(-1);
        }

        for (int i = 0; i < 3; ++i) {
            if (pthread_join(thread5[i], NULL) != 0) {
                perror("pthread_create");
                exit(-1);
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (pthread_join(thread6[i], NULL) != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }

    pthread_cond_destroy(&line8_cond);
    pthread_cond_destroy(&storage_area_cond);

    return 0;
}

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
    fscanf(arguments, "%s %d\n", tmp, &carton_capacity);
    fscanf(arguments, "%s %d %d\n", tmp, &time_to_place_the_carton_in_the_storage_area_min,
           &time_to_place_the_carton_in_the_storage_area_max);
    fscanf(arguments, "%s %d\n", tmp, &storage_area_capacity);

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

void *typeA(void *arg) {
    employees c = *(employees *) arg;
    if (c.worker == 0) {
        typeA_employee_working[c.line][c.worker] = true;
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
            z += 1;
            typeA_employee_working[c.line][c.worker] = false;
            usleep(50000);
            pthread_mutex_unlock(&coco.chocolate_mutex);
        }
    }
    if (c.worker == 1) {
        typeA_employee_working[c.line][c.worker] = true;
        while (1) {
            if (!queue1[c.line][c.worker - 1].empty()) {
                chocolate coco = queue1[c.line][c.worker - 1].front();
                queue1[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minA, maxA));
                coco.finished_steps++;
                queue1[c.line][c.worker].push(coco);
                typeA_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeA_employee_working[c.line][c.worker] = true;

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 2) {
        typeA_employee_working[c.line][c.worker] = true;
        while (1) {
            if (!queue1[c.line][c.worker - 1].empty()) {
                chocolate coco = queue1[c.line][c.worker - 1].front();
                queue1[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minA, maxA));
                coco.finished_steps++;
                queue1[c.line][c.worker].push(coco);
                typeA_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeA_employee_working[c.line][c.worker] = true;

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 3) {
        typeA_employee_working[c.line][c.worker] = true;
        while (1) {
            if (!queue1[c.line][c.worker - 1].empty()) {
                chocolate coco = queue1[c.line][c.worker - 1].front();
                queue1[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minA, maxA));
                coco.finished_steps++;
                queue1[c.line][c.worker].push(coco);
                typeA_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeA_employee_working[c.line][c.worker] = true;

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 4 || c.worker == 5 || c.worker == 6 || c.worker == 7) {
        pthread_mutex_lock(&typeA_l1_mutex[c.line]);
        order[c.line]++;
        pthread_mutex_unlock(&typeA_l1_mutex[c.line]);

        if (order[c.line] == 1) {
            typeA_employee_working[c.line][c.worker] = true;

            while (1) {
                if (!queue1[c.line][3].empty()) {
                    chocolate coco = queue1[c.line][3].front();
                    queue1[c.line][3].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    queue1[c.line][4].push(coco);
                    typeA_employee_working[c.line][c.worker] = false;
                    usleep(500000);
                    typeA_employee_working[c.line][c.worker] = true;

                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 2) {
            typeA_employee_working[c.line][c.worker] = true;

            while (1) {
                if (!queue1[c.line][4].empty()) {
                    chocolate coco = queue1[c.line][4].front();
                    queue1[c.line][4].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    queue1[c.line][5].push(coco);
                    typeA_employee_working[c.line][c.worker] = false;
                    usleep(500000);
                    typeA_employee_working[c.line][c.worker] = true;

                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 3) {
            typeA_employee_working[c.line][c.worker] = true;

            while (1) {
                if (!queue1[c.line][5].empty()) {

                    chocolate coco = queue1[c.line][5].front();
                    queue1[c.line][5].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    queue1[c.line][6].push(coco);
                    typeA_employee_working[c.line][c.worker] = false;
                    usleep(500000);
                    typeA_employee_working[c.line][c.worker] = true;

                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 4) {
            typeA_employee_working[c.line][c.worker] = true;

            while (1) {
                if (!queue1[c.line][6].empty()) {

                    chocolate coco = queue1[c.line][6].front();
                    queue1[c.line][6].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    coco.type = 'A';

                    pthread_mutex_lock(&total_queue);
                    list_of_chocolate.push(coco);
                    pthread_mutex_unlock(&total_queue);

                    typeA_total_number++;
                    typeA_employee_working[c.line][c.worker] = false;
                    usleep(500000);
                    typeA_employee_working[c.line][c.worker] = true;

                    pthread_mutex_unlock(&coco.chocolate_mutex);
                    pthread_cond_broadcast(&line8_cond);

                }
            }
        }
    }

    free(arg);
    return NULL;
}

void *typeB(void *arg) {
    employees c = *(employees *) arg;
    if (c.worker == 0) {
        typeB_employee_working[c.line][c.worker] = true;
        int z = 1;
        while (1) {
            chocolate coco;
            coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
            pthread_mutex_lock(&coco.chocolate_mutex);
            coco.chocolate_id = z;
            coco.type = 'B';
            coco.finished_steps = 1;
            sleep(generate_waiting_time(minB, maxB));
            queue2[c.line][c.worker].push(coco);
            z += 1;
            typeB_employee_working[c.line][c.worker] = false;
            usleep(500000);
            typeB_employee_working[c.line][c.worker] = true;
            pthread_mutex_unlock(&coco.chocolate_mutex);
        }
    }

    if (c.worker == 1) {
        typeB_employee_working[c.line][c.worker] = true;
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
                queue2[c.line][c.worker].push(coco);
                typeB_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeB_employee_working[c.line][c.worker] = true;

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 2) {
        typeB_employee_working[c.line][c.worker] = true;

        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
                queue2[c.line][c.worker].push(coco);
                typeB_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeB_employee_working[c.line][c.worker] = true;

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 3) {
        typeB_employee_working[c.line][c.worker] = true;
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
                queue2[c.line][c.worker].push(coco);
                typeB_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeB_employee_working[c.line][c.worker] = true;
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    if (c.worker == 4) {
        typeB_employee_working[c.line][c.worker] = true;

        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
                queue2[c.line][c.worker].push(coco);
                typeB_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeB_employee_working[c.line][c.worker] = true;

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    if (c.worker == 5) {
        typeB_employee_working[c.line][c.worker] = true;
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
                pthread_mutex_lock(&total_queue);
                list_of_chocolate.push(coco);
                pthread_mutex_unlock(&total_queue);

                typeB_total_number++;
                typeB_employee_working[c.line][c.worker] = false;
                usleep(500000);
                typeB_employee_working[c.line][c.worker] = true;
                pthread_mutex_unlock(&coco.chocolate_mutex);
                pthread_cond_broadcast(&line8_cond);


            }
        }
    }
    free(arg);
    return NULL;
}

void *typeC(void *arg) {
    employees c = *(employees *) arg;
    if (c.worker == 0) {
        typeC_employee_working[c.line][c.worker] = true;

        int z = 1;
        while (1) {
            chocolate coco;
            coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
            pthread_mutex_lock(&coco.chocolate_mutex);
            coco.chocolate_id = z;
            coco.type = 'C';
            coco.finished_steps = 1;
            sleep(generate_waiting_time(minC, maxC));
            queue3[c.line][c.worker].push(coco);
            z += 1;
            typeC_employee_working[c.line][c.worker] = false;
            usleep(500000);
            pthread_mutex_unlock(&coco.chocolate_mutex);
        }
    }
    if (c.worker == 1) {
        typeC_employee_working[c.line][c.worker] = true;

        while (1) {
            if (!queue3[c.line][c.worker - 1].empty()) {
                chocolate coco = queue3[c.line][c.worker - 1].front();
                queue3[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minC, maxC));
                coco.finished_steps++;
                queue3[c.line][c.worker].push(coco);
                typeC_employee_working[c.line][c.worker] = false;
                usleep(500000);

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    if (c.worker == 2) {
        typeC_employee_working[c.line][c.worker] = true;

        while (1) {
            if (!queue3[c.line][c.worker - 1].empty()) {
                chocolate coco = queue3[c.line][c.worker - 1].front();
                queue3[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minC, maxC));
                coco.finished_steps++;
                queue3[c.line][c.worker].push(coco);
                typeC_employee_working[c.line][c.worker] = false;
                usleep(500000);

                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 3 || c.worker == 4) {
        pthread_mutex_lock(&typeC_mutex[2 - c.line]);
        order1[c.line]++;
        pthread_mutex_unlock(&typeC_mutex[2 - c.line]);
        if (order1[c.line] == 1) {
            typeC_employee_working[c.line][c.worker] = true;

            while (1) {
                if (!queue3[c.line][2].empty()) {
                    chocolate coco = queue3[c.line][2].front();
                    queue3[c.line][2].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minC, maxC));
                    coco.finished_steps++;
                    queue3[c.line][3].push(coco);
                    typeC_employee_working[c.line][c.worker] = false;
                    usleep(500000);
                    // typeC_employee_working[c.line][c.worker] = true;

                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order1[c.line] == 2) {
            typeC_employee_working[c.line][c.worker] = true;

            while (1) {
                if (!queue3[c.line][3].empty()) {
                    chocolate coco = queue3[c.line][3].front();
                    queue3[c.line][3].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minC, maxC));
                    coco.finished_steps++;

                    pthread_mutex_lock(&total_queue);
                    list_of_chocolate.push(coco);
                    pthread_mutex_unlock(&total_queue);

                    typeC_total_number++;
                    typeC_employee_working[c.line][c.worker] = false;
                    usleep(500000);

                    pthread_mutex_unlock(&coco.chocolate_mutex);
                    pthread_cond_broadcast(&line8_cond);
                }
            }
        }
    }

    free(arg);
    return NULL;
}

void *line_8(void *arg) {
    employees c = *(employees *) arg;
    sleep(1);
    if (c.worker == 0) {
        while (1) {
            if (flag) {
                pthread_mutex_lock(&total_queue);
                while (list_of_chocolate.size() < 11) {
                    pthread_cond_wait(&line8_cond, &total_queue);
                }
                for (int i = 0; i < 10; ++i) {
                    if (list_of_chocolate.front().type == 'A') {
                        printing_expiration_date_typeA++;
                        typeA_total_number--;
                    } else if (list_of_chocolate.front().type == 'B') {
                        printing_expiration_date_typeB++;
                        typeB_total_number--;
                    } else if (list_of_chocolate.front().type == 'C') {
                        printing_expiration_date_typeC++;
                        typeC_total_number--;
                    }
                    list_of_chocolate_printing.push(list_of_chocolate.front());
                    list_of_chocolate.pop();
                }
                pthread_mutex_unlock(&total_queue);
                flag = false;
                sleep(generate_waiting_time(printing_time_min, printing_time_max));
            }
        }
    }
    if (c.worker == 1) {
        while (1) {
            if (!flag) {
                pthread_mutex_lock(&total_queue);
                while (list_of_chocolate.size() < 11) {
                    pthread_cond_wait(&line8_cond, &total_queue);
                }
                for (int i = 0; i < 10; ++i) {
                    if (list_of_chocolate.front().type == 'A') {
                        printing_expiration_date_typeA++;
                        typeA_total_number--;
                    } else if (list_of_chocolate.front().type == 'B') {
                        printing_expiration_date_typeB++;
                        typeB_total_number--;
                    } else if (list_of_chocolate.front().type == 'C') {
                        printing_expiration_date_typeC++;
                        typeC_total_number--;
                    }
                    list_of_chocolate_printing.push(list_of_chocolate.front());
                    list_of_chocolate.pop();
                }
                pthread_mutex_unlock(&total_queue);
                flag = true;
                sleep(generate_waiting_time(printing_time_min, printing_time_max));
            }
        }
    }
    free(arg);
    return NULL;
}

void *containers(void *arg) {

    employees c = *(employees *) arg;

    if (c.worker == 0) {
        while (1) {
            if (!list_of_chocolate_printing.empty()) {
                if (list_of_chocolate_printing.front().type == 'A') {
                    pthread_mutex_lock(&total_queue_printing);
                    list_of_chocolate_printing_typeA.push(list_of_chocolate_printing.front());
                    list_of_chocolate_printing.pop();
                    containers_typeA++;
                    usleep(50000);
                    pthread_mutex_unlock(&total_queue_printing);
                } else {
                    sleep(2);
                }
            }
        }
    }
    if (c.worker == 1) {
        while (1) {
            if (!list_of_chocolate_printing.empty()) {
                if (list_of_chocolate_printing.front().type == 'B') {
                    pthread_mutex_lock(&total_queue_printing);
                    list_of_chocolate_printing_typeB.push(list_of_chocolate_printing.front());
                    list_of_chocolate_printing.pop();
                    containers_typeB++;
                    usleep(50000);
                    pthread_mutex_unlock(&total_queue_printing);

                } else {
                    sleep(2);
                }
            }
        }
    }

    if (c.worker == 2) {
        while (1) {
            if (!list_of_chocolate_printing.empty()) {
                if (list_of_chocolate_printing.front().type == 'C') {
                    pthread_mutex_lock(&total_queue_printing);
                    list_of_chocolate_printing_typeC.push(list_of_chocolate_printing.front());
                    list_of_chocolate_printing.pop();
                    containers_typeC++;
                    usleep(50000);

                    pthread_mutex_unlock(&total_queue_printing);

                } else {
                    sleep(2);
                }
            }

        }
    }


    return NULL;
}

void *carton_boxes(void *arg) {
    employees c = *(employees *) arg;
    if (c.worker == 0) {
        while (1) {
            if (!list_of_chocolate_printing_typeA.empty()) {
                pthread_mutex_lock(&total_queue_printing);

//                pthread_mutex_lock(&carton_mutex);
                list_of_chocolate_packed_typeA.push(list_of_chocolate_printing_typeA.front());
                list_of_chocolate_printing_typeA.pop();
//                pthread_mutex_unlock(&carton_mutex);

                pthread_mutex_unlock(&total_queue_printing);

                if ((list_of_chocolate_packed_typeA.size() % 20) == 0) {
                    carton_typeA++;
                    number_of_typeA_in_storage++;
                    pthread_cond_signal(&storage_area_cond);
                }
                usleep(50000);

            }
        }

    }
    if (c.worker == 1) {
        while (1) {
            if (!list_of_chocolate_printing_typeB.empty()) {
                pthread_mutex_lock(&total_queue_printing);

//                pthread_mutex_lock(&carton_mutex);
                list_of_chocolate_packed_typeB.push(list_of_chocolate_printing_typeB.front());
                list_of_chocolate_printing_typeB.pop();
//                pthread_mutex_unlock(&carton_mutex);

                pthread_mutex_unlock(&total_queue_printing);

                if ((list_of_chocolate_packed_typeB.size() % 20) == 0) {
                    carton_typeB++;
                    number_of_typeB_in_storage++;
                    pthread_cond_signal(&storage_area_cond);
                }
                usleep(50000);
            }
        }
    }
    if (c.worker == 2) {
        while (1) {
            if (!list_of_chocolate_printing_typeC.empty()) {
                pthread_mutex_lock(&total_queue_printing);

//                pthread_mutex_lock(&carton_mutex);
                list_of_chocolate_packed_typeC.push(list_of_chocolate_printing_typeC.front());
                list_of_chocolate_printing_typeC.pop();
//                pthread_mutex_unlock(&carton_mutex);

                pthread_mutex_unlock(&total_queue_printing);

                if ((list_of_chocolate_packed_typeC.size() % 20) == 0) {
                    carton_typeC++;
                    number_of_typeC_in_storage++;
                    pthread_cond_signal(&storage_area_cond);
                }
                usleep(50000);

            }
        }
    }
    free(arg);
    return NULL;
}

void *storage_boxes(void *arg) {
    employees c = *(employees *) arg;
    bool ff = true;
    while (1) {
        pthread_mutex_lock(&total_queue_printing);
        while (ff) {
            pthread_cond_wait(&storage_area_cond, &total_queue_printing);
            ff = false;
        }
        storage_area_counter++;
        pthread_mutex_unlock(&total_queue_printing);
        sleep(generate_waiting_time(time_to_place_the_carton_in_the_storage_area_min,
                                    time_to_place_the_carton_in_the_storage_area_max));
        ff = true;
        cout << "storage_area_counter " << storage_area_counter << endl;
    }

    free(arg);
    return NULL;
}

void *trucks(void *arg){
    employees c = *(employees *) arg;


    free(arg);
    return NULL;
}

// opengl
void startOpenGl() {

    init();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1400, 700);
    glutInitWindowPosition(150, 250);
    glutCreateWindow("Chocolate Factory simulator");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    border();
    TypesManuRooms();
    ExpirationDManuline();
    ContainersSection();
    Boxes();
    Storage();
    LoadingIntoTrucks();
    glutPostRedisplay();
    glutSwapBuffers();
}

void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1400, 0, 700);
    glMatrixMode(GL_MODELVIEW);
}

void renderBitMap(char *string, void *font, float x, float y) {
    char *c;
    glRasterPos2i(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void border() {

    int offset = 40;
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0 + offset, 0 + offset);
    glVertex2f(0 + offset, 700 - offset);

    glBegin(GL_LINES);
    glVertex2f(1400 - offset, 700 - offset);
    glVertex2f(1400 - offset, 0 + offset);

    glBegin(GL_LINES);
    glVertex2f(0 + offset, 0 + offset);
    glVertex2f(1400 - offset, 0 + offset);

    glBegin(GL_LINES);
    glVertex2f(0 + offset, 700 - offset);
    glVertex2f(1400 - offset, 700 - offset);

    glFlush();
    glEnd();
}

void Arrow(int x, int y) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x - 130, y);
    glEnd();
    glFlush();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x - 120, y + 10);
    glVertex2f(x - 130, y);
    glEnd();
    glFlush();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x - 120, y - 10);
    glVertex2f(x - 130, y);
    glEnd();
    glFlush();
}

void Arrow2(int x, int y) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 130, y);
    glEnd();
    glFlush();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x + 120, y + 10);
    glVertex2f(x + 130, y);
    glEnd();
    glFlush();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x + 120, y - 10);
    glVertex2f(x + 130, y);
    glEnd();
    glFlush();
}

void TypesManuRooms() {

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(40, 400);
    glVertex2f(1360, 400);
    glFlush();
    glEnd();

    for (int i = 40; i <= 1360; i += 440) {

        glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex2f(i, 660);
        glVertex2f(i, 400);
        glEnd();
        glFlush();
    }
    ///typeA manu lines
    sprintf(TypeAcountsSting, "TypeA #: %d", typeA_total_number);
    renderBitMap(TypeAcountsSting, GLUT_BITMAP_HELVETICA_18, 200, 410);

    for (int i = 0; i <= 2; i++) {
        glColor3f(0, 0, 1);

        glBegin(GL_POLYGON);
        glVertex2f((140 + 100 * i), 640);
        glVertex2f((140 + 100 * i) + 20, 640);
        glVertex2f((140 + 100 * i) + 20, 440);
        glVertex2f((140 + 100 * i), 440);
        glEnd();
        glFlush();

        ///typeA employees
        for (int j = 7; j >= 0; j--) {

            glColor3f(0, 1, 0);

//            if (typeA_employee_working[i][j]) {
//                glColor3f(1, 0, 0);
//            }
            glBegin(GL_POLYGON);
            glVertex2f((140 + 100 * i) - 10, (640 - 28 * j) + 10);
            glVertex2f((140 + 100 * i) - 10 - 10, (640 - 28 * j) + 10);
            glVertex2f((140 + 100 * i) - 10 - 10, (640 - 28 * j));
            glVertex2f((140 + 100 * i) - 10, (640 - 28 * j));
            glEnd();
            glFlush();
        }
    }

    ///typeB manu lines

    glColor3f(0, 0, 0);
    sprintf(TypeBcountsSting, "TypeB #: %d", typeB_total_number);
    renderBitMap(TypeBcountsSting, GLUT_BITMAP_HELVETICA_18, 650, 410);

    for (int i = 0; i <= 1; i++) {
        glColor3f(1, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2f((600 + 200 * i), 640);
        glVertex2f((600 + 200 * i) + 20, 640);
        glVertex2f((600 + 200 * i) + 20, 440);
        glVertex2f((600 + 200 * i), 440);
        glEnd();
        glFlush();

        ///typeB employees
        for (int j = 5; j >= 0; j--) {

            glColor3f(0, 1, 0);

            if (typeB_employee_working[i][j]) {
                glColor3f(1, 0, 0);

            }

            glBegin(GL_POLYGON);
            glVertex2f((600 + 200 * i) - 10, (640 - 40 * j) + 10);
            glVertex2f((600 + 200 * i) - 10 - 10, (640 - 40 * j) + 10);
            glVertex2f((600 + 200 * i) - 10 - 10, (640 - 40 * j));
            glVertex2f((600 + 200 * i) - 10, (640 - 40 * j));
            glEnd();
            glFlush();
        }
    }

    ///typeC manu lines

    glColor3f(0, 0, 0);
    sprintf(TypeCcountsSting, "TypeC #: %d", typeC_total_number);
    renderBitMap(TypeCcountsSting, GLUT_BITMAP_HELVETICA_18, 1100, 410);

    for (int i = 0; i <= 1; i++) {
        glColor3f(1, 0, 1);

        glBegin(GL_POLYGON);
        glVertex2f((1050 + 200 * i), 640);
        glVertex2f((1050 + 200 * i) + 20, 640);
        glVertex2f((1050 + 200 * i) + 20, 440);
        glVertex2f((1050 + 200 * i), 440);
        glEnd();
        glFlush();

        ///typeC employees
        for (int j = 4; j >= 0; j--) {
            glColor3f(0, 1, 0.0);

            if (typeC_employee_working[i][j]) {

                glColor3f(1.0, 0.0, 0.0);
            }


            glBegin(GL_POLYGON);
            glVertex2f((1050 + 200 * i) - 10, (640 - 50 * j) + 10);
            glVertex2f((1050 + 200 * i) - 10 - 10, (640 - 50 * j) + 10);
            glVertex2f((1050 + 200 * i) - 10 - 10, (640 - 50 * j));
            glVertex2f((1050 + 200 * i) - 10, (640 - 50 * j));
            glEnd();
            glFlush();
        }

    }
}

void ExpirationDManuline() {

    Arrow(1360, 310);

    sprintf(title, "exp date process");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_12, 1250, 315);

    glColor3f(0, 0, 0);
    sprintf(PatchNumSting, "Batch #: %d", PatchNum);
    renderBitMap(PatchNumSting, GLUT_BITMAP_HELVETICA_18, 1100, 310);

    ///expiring date employees
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(1050, 340);
    glVertex2f(1060, 340);
    glVertex2f(1060, 340 + 10);
    glVertex2f(1050, 340 + 10);
    glEnd();
    glFlush();
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(1050, 280);
    glVertex2f(1060, 280);
    glVertex2f(1060, 280 + 10);
    glVertex2f(1050, 280 + 10);
    glEnd();
    glFlush();


    glColor3f(1, 0, 0);

    glBegin(GL_POLYGON);
    glVertex2f(800, 330);
    glVertex2f(1000, 330);
    glVertex2f(1000, 310);
    glVertex2f(800, 310);
    glEnd();
    glFlush();

    glColor3f(0, 0, 0);
    sprintf(ExpNumASting, "exp products A#: %d", printing_expiration_date_typeA);
    renderBitMap(ExpNumASting, GLUT_BITMAP_HELVETICA_18, 600, 350);

    sprintf(ExpNumBSting, "exp products B#: %d", printing_expiration_date_typeB);
    renderBitMap(ExpNumBSting, GLUT_BITMAP_HELVETICA_18, 600, 320);

    sprintf(ExpNumCSting, "exp products C#: %d", printing_expiration_date_typeC);
    renderBitMap(ExpNumCSting, GLUT_BITMAP_HELVETICA_18, 600, 290);

}

void ContainersSection() {

    sprintf(title, "containers process");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_12, 450, 315);

    Arrow(550, 310);

    for (int i = 60; i <= 340; i += 120) {
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(i, 350);
        glVertex2f(i + 100, 350);
        glVertex2f(i + 100, 290);
        glVertex2f(i, 290);
        glEnd();
        glFlush();

        ///CONTAINERS EMPLOYEES
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2f(i + 50, 370);
        glVertex2f(i + 10 + 50, 370);
        glVertex2f(i + 10 + 50, 380);
        glVertex2f(i + 50, 380);
        glEnd();
        glFlush();
    }
    glColor3f(0, 0, 0);
    sprintf(title, "Container A");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 61, 320);
    sprintf(title, "Container B");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 181, 320);
    sprintf(title, "Container C");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 301, 320);

    sprintf(ContACapString, "Cont A cap #: %d", containers_typeA);
    renderBitMap(ContACapString, GLUT_BITMAP_HELVETICA_12, 60, 270);

    sprintf(ContBCapString, "Cont B cap #: %d", containers_typeB);
    renderBitMap(ContBCapString, GLUT_BITMAP_HELVETICA_12, 180, 270);

    sprintf(ContCCapString, "Cont C cap #: %d", containers_typeC);
    renderBitMap(ContCCapString, GLUT_BITMAP_HELVETICA_12, 300, 270);


}

void Boxes() {

    glColor3f(0, 0, 0);
    sprintf(title, "Boxing process");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_12, 50, 215);
    Arrow2(40, 200);

    ///BOXING EMPLOYEES
    for (int i = 250; i <= 350; i += 50) {
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2f(i, 220);
        glVertex2f(i + 10, 220);
        glVertex2f(i + 10, 210);
        glVertex2f(i, 210);
        glEnd();
        glFlush();
    }

    glColor3f(0, 0, 0);
    sprintf(FullCartonANumSting, "cartons A #: %d", carton_typeA);
    renderBitMap(FullCartonANumSting, GLUT_BITMAP_HELVETICA_18, 400, 240);

    sprintf(FullCartonBNumSting, "cartons B #: %d", carton_typeB);
    renderBitMap(FullCartonBNumSting, GLUT_BITMAP_HELVETICA_18, 400, 210);

    sprintf(FullCartonCNumSting, "cartons C #: %d", carton_typeC);
    renderBitMap(FullCartonCNumSting, GLUT_BITMAP_HELVETICA_18, 400, 180);
}

void Storage() {

    glColor3f(0, 0, 0);
    sprintf(title, "storage process");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_12, 610, 215);

    Arrow2(600, 200);
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(800, 230);
    glVertex2f(1000, 230);
    glVertex2f(1000, 180);
    glVertex2f(800, 180);
    glEnd();
    glFlush();

    glColor3f(0, 0, 0);
    sprintf(title, "storage Area");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 850, 200);

    ///STORING EMPLOYEES
    for (int j = 180; j <= 230; j += 30) {
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2f(760, j);
        glVertex2f(770, j);
        glVertex2f(770, j + 10);
        glVertex2f(760, j + 10);
        glEnd();
        glFlush();
    }
    glColor3f(0, 0, 0);
    sprintf(CartonNumSting, "stored cartons #: %d", CartonNum);
    renderBitMap(CartonNumSting, GLUT_BITMAP_HELVETICA_18, 1020, 200);

}

void LoadingIntoTrucks() {

    glColor3f(0, 0, 0);
    sprintf(title, "Loading in trucks process");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_12, 1200, 215);
    renderBitMap(title, GLUT_BITMAP_HELVETICA_12, 1200, 115);

    Arrow2(1200, 200);
    Arrow(1340, 100);

    ///Loading EMPLOYEES
    for (int j = 80; j <= 130; j += 30) {

        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2f(1150, j);
        glVertex2f(1160, j);
        glVertex2f(1160, j + 10);
        glVertex2f(1150, j + 10);
        glEnd();
        glFlush();
    }

    for (int i = 800; i <= 1100; i += 120) {
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(i, 130);
        glVertex2f(i + 60, 130);
        glVertex2f(i + 60, 70);
        glVertex2f(i, 70);
        glEnd();
        glFlush();
    }

    glColor3f(0, 0, 0);
    sprintf(title, "Truck1");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 800, 100);
    sprintf(title, "Truck2");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 920, 100);
    sprintf(title, "Truck3");
    renderBitMap(title, GLUT_BITMAP_HELVETICA_18, 1040, 100);


    sprintf(T1CapacitySting, "T1 capacity: %d", T1Capacity);
    renderBitMap(T1CapacitySting, GLUT_BITMAP_HELVETICA_18, 600, 126);

    sprintf(T2CapacitySting, "T2 capacity: %d", T2Capacity);
    renderBitMap(T2CapacitySting, GLUT_BITMAP_HELVETICA_18, 600, 96);

    sprintf(T3CapacitySting, "T3 capacity: %d", T3Capacity);
    renderBitMap(T3CapacitySting, GLUT_BITMAP_HELVETICA_18, 600, 66);
}