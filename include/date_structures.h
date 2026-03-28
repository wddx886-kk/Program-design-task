#ifndef DATE_STRUCTURES_H
#define DATE_STRUCTURES_H

#define MAX_STUDENTS 100
#define MAX_CONSUMPTION 500
#define MAX_COURSES 200

typedef struct {

    char name[50];      // 姓名
    char id[20];        // 学号
    char gender[10];    // 性别
    char birth[20];     // 出生年月
    char major[50];     // 专业
    char hobby[100];     // 爱好

}Student;

typedef struct {

    char studentId[20]; // 学生学号
    float amount;       // 消费金额
    char description[100]; // 消费描述
    char date[20];      // 消费日期

} Consumption;

typedef struct {

    char sudentId[20]; // 学生学号
    char courseName[50];  // 课程名称
    float score;
    char semester[20]; // 学期
   
} Course;

#endif