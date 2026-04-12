#include "../../../include/common.h"
#include "../../../include/date_structures.h"

// 静态数据存储
static Student students[MAX_STUDENTS];
static int student_count = 0;

// 外部函数声明
extern Result save_students_to_file(Student students[], int count);
extern Result load_students_from_file(Student students[], int *count);

// 初始化学生管理器
Result init_student_manager() {
    return load_students_from_file(students, &student_count);
}

// 查找学生索引
static int find_student_index(const char *id) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// 添加学生
Result add_student(Student student) {
    if (student_count >= MAX_STUDENTS) return FAIL;
    if (find_student_index(student.id) != -1) return DUPLICATE;

    students[student_count++] = student;
    return save_students_to_file(students, student_count);
}

// 查找学生
Result find_student(const char *id, Student *result) {
    int index = find_student_index(id);
    if (index == -1) return NOT_FOUND;

    *result = students[index];
    return SUCCESS;
}

// 修改学生
Result modify_student(Student student) {
    int index = find_student_index(student.id);
    if (index == -1) return NOT_FOUND;

    students[index] = student;
    return save_students_to_file(students, student_count);
}

// 删除学生
Result delete_student(const char *id) {
    int index = find_student_index(id);
    if (index == -1) return NOT_FOUND;

    // 移动数组元素
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;

    return save_students_to_file(students, student_count);
}

// 获取所有学生
Result get_all_students(Student *array, int *count) {
    if (student_count == 0) return NOT_FOUND;

    memcpy(array, students, sizeof(Student) * student_count);
    *count = student_count;
    return SUCCESS;
}

// 检查学生是否存在
int is_student_exist(const char *id) {
    return find_student_index(id) != -1;
}

// 获取学生数量
int get_student_count() {
    return student_count;
}
