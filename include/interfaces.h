#ifndef INTERFACES_H
#define INTERFACES_H

#include "date_structures.h"

// 后端API接口结构体
typedef struct {
    // 学生管理接口
    Result (*add_student)(Student student);
    Result (*find_student)(const char *id, Student *result);
    Result (*modify_student)(Student student);
    Result (*delete_student)(const char *id);
    Result (*get_all_students)(Student *array, int *count);
    int (*is_student_exist)(const char *id);

    // 消费管理接口
    Result (*add_consumption)(Consumption consumption);
    Result (*find_consumptions)(const char *id, Consumption *array, int *count);
    Result (*modify_consumption)(const char *id, int index, Consumption consumption);
    Result (*delete_consumption)(const char *id, int index);
    Result (*get_all_consumptions)(Consumption *array, int *count);
    float (*get_total_consumption)(const char *id);

    // 课程管理接口
    Result (*add_course)(Course course);
    Result (*find_courses)(const char *id, Course *array, int *count);
    Result (*modify_course)(const char *id, int index, Course course);
    Result (*delete_course)(const char *id, int index);
    Result (*get_all_courses)(Course *array, int *count);
    void (*get_course_stats)(const char *id, float *total, float *avg, int *count);
} BackendAPI;

// 初始化后端API
BackendAPI* init_backend_api();

// 清理后端API
void cleanup_backend_api(BackendAPI *api);

#endif
