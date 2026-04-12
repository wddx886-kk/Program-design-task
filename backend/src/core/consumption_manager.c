#include "../../../include/common.h"
#include "../../../include/date_structures.h"

// 静态数据存储
static Consumption consumptions[MAX_CONSUMPTION];
static int consumption_count = 0;

// 外部函数声明
extern Result save_consumptions_to_file(Consumption consumptions[], int count);
extern Result load_consumptions_from_file(Consumption consumptions[], int *count);
extern int is_student_exist(const char *id);

// 初始化消费管理器
Result init_consumption_manager() {
    return load_consumptions_from_file(consumptions, &consumption_count);
}

// 添加消费记录
Result add_consumption(Consumption consumption) {
    if (consumption_count >= MAX_CONSUMPTION) return FAIL;
    if (!is_student_exist(consumption.studentId)) return NOT_FOUND;

    consumptions[consumption_count++] = consumption;
    return save_consumptions_to_file(consumptions, consumption_count);
}

// 查找消费记录
Result find_consumptions(const char *id, Consumption *array, int *count) {
    *count = 0;

    for (int i = 0; i < consumption_count; i++) {
        if (strcmp(consumptions[i].studentId, id) == 0) {
            array[(*count)++] = consumptions[i];
        }
    }

    return (*count > 0) ? SUCCESS : NOT_FOUND;
}

// 修改消费记录
Result modify_consumption(const char *id, int index, Consumption consumption) {
    int real_index = -1;
    int found_count = 0;

    for (int i = 0; i < consumption_count; i++) {
        if (strcmp(consumptions[i].studentId, id) == 0) {
            if (found_count == index) {
                real_index = i;
                break;
            }
            found_count++;
        }
    }

    if (real_index == -1) return NOT_FOUND;

    consumptions[real_index] = consumption;
    return save_consumptions_to_file(consumptions, consumption_count);
}

// 删除消费记录
Result delete_consumption(const char *id, int index) {
    int real_index = -1;
    int found_count = 0;

    for (int i = 0; i < consumption_count; i++) {
        if (strcmp(consumptions[i].studentId, id) == 0) {
            if (found_count == index) {
                real_index = i;
                break;
            }
            found_count++;
        }
    }

    if (real_index == -1) return NOT_FOUND;

    // 移动数组元素
    for (int i = real_index; i < consumption_count - 1; i++) {
        consumptions[i] = consumptions[i + 1];
    }
    consumption_count--;

    return save_consumptions_to_file(consumptions, consumption_count);
}

// 获取所有消费记录
Result get_all_consumptions(Consumption *array, int *count) {
    if (consumption_count == 0) return NOT_FOUND;

    memcpy(array, consumptions, sizeof(Consumption) * consumption_count);
    *count = consumption_count;
    return SUCCESS;
}

// 获取消费总额
float get_total_consumption(const char *id) {
    float total = 0.0f;

    for (int i = 0; i < consumption_count; i++) {
        if (strcmp(consumptions[i].studentId, id) == 0) {
            total += consumptions[i].amount;
        }
    }

    return total;
}
