#include "../../../include/common.h"
#include "../../../include/date_structures.h"

// 私有函数声明
static int ensure_data_dir();

// 创建数据目录
static int ensure_data_dir() {

    return SUCCESS;
}

// 保存学生数据
Result save_students_to_file(Student students[], int count) {
    ensure_data_dir();

    FILE *fp = fopen(STUDENTS_FILE, "wb");
    if (fp == NULL) return FAIL;

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), count, fp);

    fclose(fp);
    return SUCCESS;
}

// 加载学生数据
Result load_students_from_file(Student students[], int *count) {
    FILE *fp = fopen(STUDENTS_FILE, "rb");
    if (fp == NULL) {
        *count = 0;
        return SUCCESS;
    }

    fread(count, sizeof(int), 1, fp);
    if (*count > MAX_STUDENTS) *count = MAX_STUDENTS;

    fread(students, sizeof(Student), *count, fp);

    fclose(fp);
    return SUCCESS;
}

// 保存消费数据
Result save_consumptions_to_file(Consumption consumptions[], int count) {
    ensure_data_dir();

    FILE *fp = fopen(CONSUMPTION_FILE, "wb");
    if (fp == NULL) return FAIL;

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(consumptions, sizeof(Consumption), count, fp);

    fclose(fp);
    return SUCCESS;
}

// 加载消费数据
Result load_consumptions_from_file(Consumption consumptions[], int *count) {
    FILE *fp = fopen(CONSUMPTION_FILE, "rb");
    if (fp == NULL) {
        *count = 0;
        return SUCCESS;
    }

    fread(count, sizeof(int), 1, fp);
    if (*count > MAX_CONSUMPTION) *count = MAX_CONSUMPTION;

    fread(consumptions, sizeof(Consumption), *count, fp);

    fclose(fp);
    return SUCCESS;
}

// 保存课程数据
Result save_courses_to_file(Course courses[], int count) {
    ensure_data_dir();

    FILE *fp = fopen(COURSES_FILE, "wb");
    if (fp == NULL) return FAIL;

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(courses, sizeof(Course), count, fp);

    fclose(fp);
    return SUCCESS;
}

// 加载课程数据
Result load_courses_from_file(Course courses[], int *count) {
    FILE *fp = fopen(COURSES_FILE, "rb");
    if (fp == NULL) {
        *count = 0;
        return SUCCESS;
    }

    fread(count, sizeof(int), 1, fp);
    if (*count > MAX_COURSES) *count = MAX_COURSES;

    fread(courses, sizeof(Course), *count, fp);

    fclose(fp);
    return SUCCESS;
}
