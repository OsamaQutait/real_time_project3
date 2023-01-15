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
int minA, maxA, minB, maxB, minC, maxC, number_of_line ,
number_of_employee_of_typeA, number_of_employee_of_typeB, number_of_employee_of_typeC;
int order[4];
unordered_set<int> unordered_set1 = {1, 2, 3, 4};
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
vector<chocolate> list_of_chocolate;
queue<chocolate> queue1[9][9];
/*
 * mutex look
 */
pthread_mutex_t typeA_l1_mutex[4], typeA_l2_mutex, typeA_l3_mutex;
pthread_cond_t typeA_l1_cond[9], typeA_l2_cond, typeA_l3_cond;
#endif //PROJECT3_LOCAL_H
