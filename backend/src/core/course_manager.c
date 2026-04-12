#include "../../../include/common.h"
#include "../../../include/date_structures.h"

// 静态数据存储
static Course courses[MAX_COURSES];
static int course_count = 0;

// 外部函数声明
extern Result save_courses_to_file(Course courses[], int count);
extern Result load_courses_from_file(Course courses[], int *count);
extern int is_student_exist(const char *id);

// 初始化课程管理器
Result init_course_manager() {
    return load_courses_from_file(courses, &course_count);
}

// 添加课程成绩
Result add_course(Course course) {
    if (course_count >= MAX_COURSES) return FAIL;
    if (!is_student_exist(course.studentId)) return NOT_FOUND;

    courses[course_count++] = course;
    return save_courses_to_file(courses, course_count);
}

// 查找课程成绩
Result find_courses(const char *id, Course *array, int *count) {
    *count = 0;

    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].studentId, id) == 0) {
            array[(*count)++] = courses[i];
        }
    }

    return (*count > 0) ? SUCCESS : NOT_FOUND;
}

// 修改课程成绩
Result modify_course(const char *id, int index, Course course) {
    int real_index = -1;
    int found_count = 0;

    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].studentId, id) == 0) {
            if (found_count == index) {
                real_index = i;
                break;
            }
            found_count++;
        }
    }

    if (real_index == -1) return NOT_FOUND;

    courses[real_index] = course;
    return save_courses_to_file(courses, course_count);
}

// 删除课程成绩
Result delete_course(const char *id, int index) {
    int real_index = -1;
    int found_count = 0;

    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].studentId, id) == 0) {
            if (found_count == index) {
                real_index = i;
                break;
            }
            found_count++;
        }
    }

    if (real_index == -1) return NOT_FOUND;

    // 移动数组元素
    for (int i = real_index; i < course_count - 1; i++) {
        courses[i] = courses[i + 1];
    }
    course_count--;

    return save_courses_to_file(courses, course_count);
}

// 获取所有课程成绩
Result get_all_courses(Course *array, int *count) {
    if (course_count == 0) return NOT_FOUND;

    memcpy(array, courses, sizeof(Course) * course_count);
    *count = course_count;
    return SUCCESS;
}

// 获取课程统计
void get_course_stats(const char *id, float *total, float *avg, int *count) {
    *total = 0.0f;
    *count = 0;

    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].studentId, id) == 0) {
            *total += courses[i].score;
            (*count)++;
        }
    }

    *avg = (*count > 0) ? (*total / *count) : 0.0f;
}
