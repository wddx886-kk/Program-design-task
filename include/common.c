#include "common.h"

// 清屏函数
void clear_screen() {
    system("cls || clear");
}

// 暂停函数
void pause_screen() {
    printf("\n按回车键继续...");
    getchar();
}

// 获取当前日期
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%04d-%02d-%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
