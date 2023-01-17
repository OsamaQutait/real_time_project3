#include "local.h"

void read_file();

int generate_waiting_time(int lower, int upper);

void *typeA(void *arg);

void *typeB(void *arg);

void *typeC(void *arg);

void *line_8(void *arg);

int main(int argc, char *argv[]) {

    pthread_cond_init(&list_of_chocolate_available, NULL);
    read_file();

    memset(order, 0, sizeof(order));
    memset(order1, 0, sizeof(order1));

    total_queue = PTHREAD_MUTEX_INITIALIZER;
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

//    while (1){
//        cout << printing_expiration_date_typeA << " " << printing_expiration_date_typeB << " " << printing_expiration_date_typeC << endl;
//        sleep(2);
//    }

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
    pthread_cond_destroy(&list_of_chocolate_available);
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
    fscanf(arguments, "%s %d %d\n", tmp, &printing_time_min, &printing_time_max);
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
//    sleep(1);

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
//            cout << GREEN << "employee " << c.worker << " produce item with step "
//                 << queue1[c.line][c.worker].back().finished_steps << " id " << z << endl;
//            fflush(stdout);
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
//                cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
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
//                cout << BLUE << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
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
//                cout << YELLOW << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
                queue1[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 4 || c.worker == 5 || c.worker == 6 || c.worker == 7) {
        pthread_mutex_lock(&typeA_l1_mutex[c.line]);
        order[c.line]++;
        pthread_mutex_unlock(&typeA_l1_mutex[c.line]);

        if (order[c.line] == 1) {
            while (1) {
                if (!queue1[c.line][3].empty()) {
                    chocolate coco = queue1[c.line][3].front();
                    queue1[c.line][3].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
//                    cout << GREEN << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                         << coco.chocolate_id << endl;
//                    fflush(stdout);
                    queue1[c.line][4].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 2) {
            while (1) {
                if (!queue1[c.line][4].empty()) {
                    chocolate coco = queue1[c.line][4].front();
                    queue1[c.line][4].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
//                    cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                         << coco.chocolate_id << endl;
//                    fflush(stdout);
                    queue1[c.line][5].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 3) {
            while (1) {
                if (!queue1[c.line][5].empty()) {
                    chocolate coco = queue1[c.line][5].front();
                    queue1[c.line][5].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
//                    cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                         << coco.chocolate_id << endl;
//                    fflush(stdout);
                    queue1[c.line][6].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order[c.line] == 4) {
            while (1) {
                if (!queue1[c.line][6].empty()) {
                    chocolate coco = queue1[c.line][6].front();
                    queue1[c.line][6].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minA, maxA));
                    coco.finished_steps++;
                    coco.type = 'A';
//                    cout << BLUE << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                         << coco.chocolate_id << endl;
//                    fflush(stdout);
//                    queue1[c.line][7].push(coco);

                    pthread_mutex_lock(&total_queue);
                    list_of_chocolate.push(coco);
//                    cout << c.line << " " <<list_of_chocolate.size() << endl;

                    pthread_mutex_unlock(&total_queue);

                    typeA_total_number++;

//                    cout << "number of produced element is " << queue1[c.line][7].size() << " number of line is  "<< c.line << endl;
                    pthread_mutex_unlock(&coco.chocolate_mutex);
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
//            cout << GREEN << "employee " << c.worker << " produce item with step "
//                 << coco.finished_steps << " id " << coco.chocolate_id << endl;
//            fflush(stdout);
            z += 1;
            pthread_mutex_unlock(&coco.chocolate_mutex);
        }
    }

    if (c.worker == 1) {
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
//                cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                cout << "emp " << c.worker << " line " << c.line << " coco is" << coco.chocolate_id << endl;
//                fflush(stdout);
                queue2[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 2) {
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
//                cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
                queue2[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 3) {
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
//                cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
                queue2[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    if (c.worker == 4) {
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
//               cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
                queue2[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    if (c.worker == 5) {
        while (1) {
            if (!queue2[c.line][c.worker - 1].empty()) {
                chocolate coco = queue2[c.line][c.worker - 1].front();
                queue2[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minB, maxB));
                coco.finished_steps++;
//               cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
//                queue2[c.line][c.worker].push(coco);
                pthread_mutex_lock(&total_queue);
                list_of_chocolate.push(coco);
//                cout << c.line << " " <<list_of_chocolate.size() << endl;
                pthread_mutex_unlock(&total_queue);

                typeB_total_number++;
//                cout << RED << "number of chocolate generated by the the line " << c.line << " is " << queue2[c.line][c.worker].size() << endl;
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    free(arg);
    return NULL;
}

void *typeC(void *arg) {
    employees c = *(employees *) arg;
    if (c.worker == 0) {
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
//            cout << GREEN << "employee " << c.worker << " produce item with step "
//                 << coco.finished_steps << " id " << coco.chocolate_id << endl;
//            fflush(stdout);
            z += 1;
            pthread_mutex_unlock(&coco.chocolate_mutex);
        }
    }
    if (c.worker == 1) {
        while (1) {
            if (!queue3[c.line][c.worker - 1].empty()) {
                chocolate coco = queue3[c.line][c.worker - 1].front();
                queue3[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minC, maxC));
                coco.finished_steps++;
//                cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
                queue3[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }
    if (c.worker == 2) {
        while (1) {
            if (!queue3[c.line][c.worker - 1].empty()) {
                chocolate coco = queue3[c.line][c.worker - 1].front();
                queue3[c.line][c.worker - 1].pop();
                coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_lock(&coco.chocolate_mutex);
                sleep(generate_waiting_time(minC, maxC));
                coco.finished_steps++;
//                cout << BLUE << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                fflush(stdout);
                queue3[c.line][c.worker].push(coco);
                pthread_mutex_unlock(&coco.chocolate_mutex);
            }
        }
    }

    if (c.worker == 3 || c.worker == 4) {
        pthread_mutex_lock(&typeC_mutex[2 - c.line]);
        order1[c.line]++;
        pthread_mutex_unlock(&typeC_mutex[2 - c.line]);
        if (order1[c.line] == 1) {
            while (1) {
                if (!queue3[c.line][2].empty()) {
                    chocolate coco = queue3[c.line][2].front();
                    queue3[c.line][2].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minC, maxC));
                    coco.finished_steps++;
//                    cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                    fflush(stdout);
                    queue3[c.line][3].push(coco);
                    pthread_mutex_unlock(&coco.chocolate_mutex);
                }
            }
        }
        if (order1[c.line] == 2) {
            while (1) {
                if (!queue3[c.line][3].empty()) {
                    chocolate coco = queue3[c.line][3].front();
                    queue3[c.line][3].pop();
                    coco.chocolate_mutex = PTHREAD_MUTEX_INITIALIZER;
                    pthread_mutex_lock(&coco.chocolate_mutex);
                    sleep(generate_waiting_time(minC, maxC));
                    coco.finished_steps++;
//                    cout << RED << "employee " << c.worker << " produce item step" << coco.finished_steps << " id is "
//                     << coco.chocolate_id << endl;
//                    fflush(stdout);
//                    queue3[c.line][4].push(coco);

                    pthread_mutex_lock(&total_queue);
                    list_of_chocolate.push(coco);
//                    cout << c.line << " " <<list_of_chocolate.size() << endl;

                    pthread_mutex_unlock(&total_queue);
                    typeC_total_number++;
//                    cout << "line " << c.line << " produce item " << queue3[c.line][4].size() << endl;
                    pthread_mutex_unlock(&coco.chocolate_mutex);
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
                if (list_of_chocolate.size() > 15) {
                    for (int i = 0; i < 10; ++i) {
//                        cout << GREEN << list_of_chocolate.front().chocolate_id << " " << list_of_chocolate.front().type
//                             << endl;
                        if (list_of_chocolate.front().type == 'A'){
                            printing_expiration_date_typeA++;
                        } else if (list_of_chocolate.front().type == 'B'){
                            printing_expiration_date_typeB++;
                        } else if (list_of_chocolate.front().type == 'C'){
                            printing_expiration_date_typeC++;
                        }
                        list_of_chocolate.pop();
                    }
                    cout << endl;
                    flag = false;
                    sleep(generate_waiting_time(printing_time_min, printing_time_max));
                }
            }
        }
    }
    if (c.worker == 1) {
        while (1) {
            if (!flag) {
                if (list_of_chocolate.size() > 15) {
                    for (int i = 0; i < 10; ++i) {
//                        cout << RED << list_of_chocolate.front().chocolate_id << " " << list_of_chocolate.front().type
//                             << endl;
                        if (list_of_chocolate.front().type == 'A'){
                            printing_expiration_date_typeA++;
                        } else if (list_of_chocolate.front().type == 'B'){
                            printing_expiration_date_typeB++;
                        } else if (list_of_chocolate.front().type == 'C'){
                            printing_expiration_date_typeC++;
                        }
                        list_of_chocolate.pop();
                    }
                    cout << endl;
                    flag = true;
                    sleep(generate_waiting_time(printing_time_min, printing_time_max));
                }
            }
        }
    }
    free(arg);
    return NULL;
}