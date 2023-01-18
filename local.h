#ifndef PROJECT3_LOCAL_H
#define PROJECT3_LOCAL_H
#include <iostream>
using namespace std;
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <string.h>
#include <queue>
#include <unordered_set>
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLACK   "\033[30m"      /* Black */
#define MAGENTA "\033[35m"      /* Magenta */


pthread_t thread[3][8];
pthread_t thread1[2][6];
pthread_t thread2[2][5];
pthread_t thread3[2];
pthread_t thread4[3];
bool flag = true;
int containers_typeA, containers_typeB, containers_typeC;
int printing_expiration_date_typeA = 0, printing_expiration_date_typeB = 0, printing_expiration_date_typeC = 0;
int printing_time_min, printing_time_max;
int typeB_total_number = 0, typeC_total_number = 0, typeA_total_number = 0;
int minA, maxA, minB, maxB, minC, maxC, number_of_line ,
number_of_employee_of_typeA, number_of_employee_of_typeB, number_of_employee_of_typeC;
int order[4], order1[3];
typedef struct employees
{
    int line;
    int worker; // number of step
} employees;
typedef struct chocolate
{
    unsigned int chocolate_id;
    char type;
    int finished_steps;
    pthread_mutex_t chocolate_mutex;
} chocolate;
queue<chocolate> list_of_chocolate;
queue<chocolate> list_of_chocolate_printing;
queue<chocolate> list_of_chocolate_printing_typeA, list_of_chocolate_printing_typeB, list_of_chocolate_printing_typeC;
queue<chocolate> queue1[9][9];
queue<chocolate> queue2[9][9];
queue<chocolate> queue3[9][9];

/*
 * mutex look
 */
pthread_mutex_t typeA_l1_mutex[4], typeC_mutex[2], total_queue, total_queue_printing;
#endif //PROJECT3_LOCAL_H
