//
// Created by osama on 1/20/23.
//
#include "local.h"
int main (){
    char tmp[300];
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
    fscanf(arguments, "%s %d\n", tmp, &carton_capacity);
    fscanf(arguments, "%s %d %d\n", tmp, &time_to_place_the_carton_in_the_storage_area_min,
           &time_to_place_the_carton_in_the_storage_area_max);
    fscanf(arguments, "%s %d\n", tmp, &storage_area_capacity);
    fscanf(arguments, "%s %d\n", tmp, &number_of_trucks);
    fscanf(arguments, "%s %d\n", tmp, &truck_capacity);
    fscanf(arguments, "%s %d\n", tmp, &truck_travel_time);

    fclose(arguments);
    return 0;
}