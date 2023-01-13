//
// Created by osama on 1/13/23.
//

#ifndef PROJECT3_LOCAL_H
#define PROJECT3_LOCAL_H
#include <iostream>
using namespace std;
#include <unistd.h>
#include <pthread.h>
#include <vector>

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLACK   "\033[30m"      /* Black */
#define MAGENTA "\033[35m"      /* Magenta */
typedef struct employees
{
    int line;
    int worker; // number of step
} employees;
/*
 * mutex look
 */
pthread_mutex_t typeA_l1_mutex, typeA_l2_mutex, typeA_l3_mutex;
pthread_cond_t typeA_l1_cond, typeA_l2_cond, typeA_l3_cond;
#endif //PROJECT3_LOCAL_H
