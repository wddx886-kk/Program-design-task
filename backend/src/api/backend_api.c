#include "../../../include/interfaces.h"

// 声明管理器函数
extern Result init_student_manager();
extern Result add_student(Student student);
extern Result find_student(const char *id, Student *result);
extern Result modify_student(Student student);
extern Result delete_student(const char *id);
extern Result get_all_students(Student *array, int *count);
extern int is_student_exist(const char *id);
extern int get_student_count();

extern Result init_consumption_manager();
extern Result add_consumption(Consumption consumption);
extern Result find_consumptions(const char *id, Consumption *array, int *count);
extern Result modify_consumption(const char *id, int index, Consumption consumption);
extern Result delete_consumption(const char *id, int index);
extern Result get_all_consumptions(Consumption *array, int *count);
extern float get_total_consumption(const char *id);

extern Result init_course_manager();
extern Result add_course(Course course);
extern Result find_courses(const char *id, Course *array, int *count);
extern Result modify_course(const char *id, int index, Course course);
extern Result delete_course(const char *id, int index);
extern Result get_all_courses(Course *array, int *count);
extern void get_course_stats(const char *id, float *total, float *avg, int *count);

// 后端API实例
static BackendAPI api_instance;

// 初始化后端API
BackendAPI* init_backend_api() {
    // 初始化各个管理器
    init_student_manager();
    init_consumption_manager();
    init_course_manager();

    // 绑定函数指针
    api_instance.add_student = add_student;
    api_instance.find_student = find_student;
    api_instance.modify_student = modify_student;
    api_instance.delete_student = delete_student;
    api_instance.get_all_students = get_all_students;
    api_instance.is_student_exist = is_student_exist;

    api_instance.add_consumption = add_consumption;
    api_instance.find_consumptions = find_consumptions;
    api_instance.modify_consumption = modify_consumption;
    api_instance.delete_consumption = delete_consumption;
    api_instance.get_all_consumptions = get_all_consumptions;
    api_instance.get_total_consumption = get_total_consumption;

    api_instance.add_course = add_course;
    api_instance.find_courses = find_courses;
    api_instance.modify_course = modify_course;
    api_instance.delete_course = delete_course;
    api_instance.get_all_courses = get_all_courses;
    api_instance.get_course_stats = get_course_stats;

    return &api_instance;
}

// 清理后端API
void cleanup_backend_api(BackendAPI *api) {
    (void)api;
}

// 获取后端API接口
BackendAPI* get_backend_api() {
    static BackendAPI *api = NULL;
    if (api == NULL) {
        api = init_backend_api();
    }
    return api;
}
