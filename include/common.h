#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 100
#define MAX_CONSUMPTION 500
#define MAX_COURSES 200
#define MAX_STRING_LEN 100

#define DATA_DIR "data/"
#define STUDENTS_FILE DATA_DIR "students.dat"
#define CONSUMPTION_FILE DATA_DIR "consumptions.dat"
#define COURSES_FILE DATA_DIR "courses.dat"

typedef enum {
    SUCCESS = 0,
    FAIL = -1,
    NOT_FOUND = -2,
    DUPLICATE = -3,
    INVALID_INPUT = -4
} Result;

void clear_screen();
void pause_screen();
void get_current_date(char *date_str);

#endif
