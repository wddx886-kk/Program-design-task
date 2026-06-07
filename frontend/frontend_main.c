#include "../include/common.h"
#include "../include/interfaces.h"

// 获取后端API
extern BackendAPI* get_backend_api();

// 前端输入验证函数
void validate_input(const char *prompt, char *input, int max_len) {
	while (1) {
		printf("%s", prompt);
		fgets(input, max_len, stdin);
		input[strcspn(input, "\n")] = '\0';

		if (strlen(input) > 0) break;
		printf("输入不能为空，请重新输入!\n");
	}
}

float validate_float_input(const char *prompt) {
	float value;
	char buffer[50];

	while (1) {
		printf("%s", prompt);
		fgets(buffer, sizeof(buffer), stdin);

		if (sscanf(buffer, "%f", &value) == 1) {
			return value;
		}
		printf("输入无效，请输入数字!\n");
	}
}

// 菜单显示函数
void display_main_menu() {
	printf("\n=== 个人信息管理系统 ===\n");
	printf("1. 学生信息管理\n");
	printf("2. 消费记录管理\n");
	printf("3. 成绩管理\n");
	printf("0. 退出系统\n");
	printf("========================\n");
}

void display_student_menu() {
	printf("\n=== 学生信息管理 ===\n");
	printf("1. 添加学生信息\n");
	printf("2. 查找学生信息\n");
	printf("3. 修改学生信息\n");
	printf("4. 删除学生信息\n");
	printf("5. 显示所有学生\n");
	printf("0. 返回主菜单\n");
	printf("========================\n");
}

void display_consumption_menu() {
	printf("\n=== 消费记录管理 ===\n");
	printf("1. 添加消费记录\n");
	printf("2. 查找消费记录\n");
	printf("3. 修改消费记录\n");
	printf("4. 删除消费记录\n");
	printf("5. 显示所有记录\n");
	printf("6. 消费总额统计\n");
	printf("0. 返回主菜单\n");
	printf("========================\n");
}

void display_course_menu() {
	printf("\n=== 成绩管理 ===\n");
	printf("1. 添加课程成绩\n");
	printf("2. 查找课程成绩\n");
	printf("3. 修改课程成绩\n");
	printf("4. 删除课程成绩\n");
	printf("5. 显示所有成绩\n");
	printf("6. 成绩统计\n");
	printf("0. 返回主菜单\n");
	printf("========================\n");
}

// 学生信息管理功能
void student_management(BackendAPI *api) {
	int choice;
	do {
		clear_screen();
		display_student_menu();
		printf("请输入选择: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
			case 1: {
				Student student;
				printf("\n=== 添加学生信息 ===\n");
				validate_input("输入学号: ", student.id, sizeof(student.id));
				if (api->is_student_exist(student.id)) {
					printf("该学号已存在!\n");
					pause_screen();
					break;
				}
				validate_input("输入姓名: ", student.name, sizeof(student.name));
				validate_input("输入性别: ", student.gender, sizeof(student.gender));
				validate_input("输入出生年月: ", student.birth, sizeof(student.birth));
				validate_input("输入专业: ", student.major, sizeof(student.major));
				validate_input("输入爱好: ", student.hobby, sizeof(student.hobby));

				Result result = api->add_student(student);
				if (result == SUCCESS) {
					printf("学生信息添加成功!\n");
				} else {
					printf("添加失败!\n");
				}
				pause_screen();
				break;
			}
			case 2: {
				char id[20];
				printf("\n=== 查找学生信息 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Student student;
				Result result = api->find_student(id, &student);
				if (result == SUCCESS) {
					printf("\n找到学生信息:\n");
					printf("学号: %s\n", student.id);
					printf("姓名: %s\n", student.name);
					printf("性别: %s\n", student.gender);
					printf("出生年月: %s\n", student.birth);
					printf("专业: %s\n", student.major);
					printf("爱好: %s\n", student.hobby);
				} else {
					printf("未找到该学生!\n");
				}
				pause_screen();
				break;
			}
			case 3: {
				char id[20];
				printf("\n=== 修改学生信息 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Student student;
				if (api->find_student(id, &student) == SUCCESS) {
					printf("当前信息:\n");
					printf("1. 姓名: %s\n", student.name);
					printf("2. 性别: %s\n", student.gender);
					printf("3. 出生年月: %s\n", student.birth);
					printf("4. 专业: %s\n", student.major);
					printf("5. 爱好: %s\n", student.hobby);

					printf("选择要修改的字段(1-5): ");
					int field;
					scanf("%d", &field);
					getchar();

					switch (field) {
						case 1:
							validate_input("输入新姓名: ", student.name, sizeof(student.name));
							break;
						case 2:
							validate_input("输入新性别: ", student.gender, sizeof(student.gender));
							break;
						case 3:
							validate_input("输入新出生年月: ", student.birth, sizeof(student.birth));
							break;
						case 4:
							validate_input("输入新专业: ", student.major, sizeof(student.major));
							break;
						case 5:
							validate_input("输入新爱好: ", student.hobby, sizeof(student.hobby));
							break;
						default:
							printf("无效选择!\n");
							pause_screen();
							continue;
					}

					Result result = api->modify_student(student);
					if (result == SUCCESS) {
						printf("修改成功!\n");
					} else {
						printf("修改失败!\n");
					}
				} else {
					printf("未找到该学生!\n");
				}
				pause_screen();
				break;
			}
			case 4: {
				char id[20];
				printf("\n=== 删除学生信息 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Student student;
				if (api->find_student(id, &student) == SUCCESS) {
					printf("确认删除学生 %s (y/n)? ", student.name);
					char confirm;
					scanf("%c", &confirm);
					getchar();

					if (confirm == 'y' || confirm == 'Y') {
						Result result = api->delete_student(id);
						if (result == SUCCESS) {
							printf("删除成功!\n");
						} else {
							printf("删除失败!\n");
						}
					} else {
						printf("删除操作已取消!\n");
					}
				} else {
					printf("未找到该学生!\n");
				}
				pause_screen();
				break;
			}
			case 5: {
				printf("\n=== 所有学生信息 ===\n");
				Student students[MAX_STUDENTS];
				int count;

				Result result = api->get_all_students(students, &count);
				if (result == SUCCESS) {
					printf("=================================================================================================\n");
					printf("| %-15s | %-10s | %-5s | %-10s | %-15s | %-30s |\n",
					       "学号", "姓名", "性别", "出生年月", "专业", "爱好");
					printf("=================================================================================================\n");

					for (int i = 0; i < count; i++) {
						printf("| %-15s | %-10s | %-5s | %-10s | %-15s | %-30s |\n",
						       students[i].id, students[i].name, students[i].gender,
						       students[i].birth, students[i].major, students[i].hobby);
					}
					printf("=================================================================================================\n");
				} else {
					printf("没有学生记录!\n");
				}
				pause_screen();
				break;
			}
			case 0:
				break;
			default:
				printf("无效选择!\n");
				pause_screen();
		}
	} while (choice != 0);
}

// 消费记录管理功能
void consumption_management(BackendAPI *api) {
	int choice;
	do {
		clear_screen();
		display_consumption_menu();
		printf("请输入选择: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
			case 1: {
				Consumption consumption;
				printf("\n=== 添加消费记录 ===\n");
				validate_input("输入学生学号: ", consumption.studentId, sizeof(consumption.studentId));

				if (!api->is_student_exist(consumption.studentId)) {
					printf("该学号不存在!\n");
					pause_screen();
					break;
				}

				consumption.amount = validate_float_input("输入消费金额: ");
				validate_input("输入消费描述: ", consumption.description, sizeof(consumption.description));
				get_current_date(consumption.date);

				Result result = api->add_consumption(consumption);
				if (result == SUCCESS) {
					printf("消费记录添加成功!\n");
				} else {
					printf("添加失败!\n");
				}
				pause_screen();
				break;
			}
			case 2: {
				char id[20];
				printf("\n=== 查找消费记录 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Consumption consumptions[MAX_CONSUMPTION];
				int count;
				Result result = api->find_consumptions(id, consumptions, &count);

				if (result == SUCCESS) {
					printf("\n该学生的消费记录:\n");
					printf("=================================================================================\n");
					printf("| %-10s | %-20s | %-12s |\n", "金额", "描述", "日期");
					printf("=================================================================================\n");

					for (int i = 0; i < count; i++) {
						printf("| %-10.2f | %-20s | %-12s |\n",
						       consumptions[i].amount, consumptions[i].description, consumptions[i].date);
					}
					printf("=================================================================================\n");
				} else {
					printf("未找到该学生的消费记录!\n");
				}
				pause_screen();
				break;
			}
			case 3: {
				char id[20];
				printf("\n=== 修改消费记录 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Consumption consumptions[MAX_CONSUMPTION];
				int count;
				Result result = api->find_consumptions(id, consumptions, &count);

				if (result != SUCCESS) {
					printf("未找到该学生的消费记录!\n");
					pause_screen();
					break;
				}

				printf("\n该学生的消费记录:\n");
				printf("===========================================================================================\n");
				printf("| %-5s | %-10s | %-20s | %-12s |\n", "序号", "金额", "描述", "日期");
				printf("===========================================================================================\n");
				for (int i = 0; i < count; i++) {
					printf("| %-5d | %-10.2f | %-20s | %-12s |\n",
					       i + 1, consumptions[i].amount, consumptions[i].description, consumptions[i].date);
				}
				printf("===========================================================================================\n");

				printf("选择要修改的记录序号(1-%d): ", count);
				int index;
				scanf("%d", &index);
				getchar();

				if (index < 1 || index > count) {
					printf("无效序号!\n");
					pause_screen();
					break;
				}

				Consumption consumption = consumptions[index - 1];
				printf("选择要修改的字段:\n");
				printf("1. 金额: %.2f\n", consumption.amount);
				printf("2. 描述: %s\n", consumption.description);
				printf("3. 日期: %s\n", consumption.date);
				printf("请输入选择(1-3): ");

				int field;
				scanf("%d", &field);
				getchar();

				switch (field) {
					case 1:
						consumption.amount = validate_float_input("输入新消费金额: ");
						break;
					case 2:
						validate_input("输入新消费描述: ", consumption.description, sizeof(consumption.description));
						break;
					case 3:
						validate_input("输入新消费日期: ", consumption.date, sizeof(consumption.date));
						break;
					default:
						printf("无效选择!\n");
						pause_screen();
						break;
				}

				if (field < 1 || field > 3) {
					break;
				}

				result = api->modify_consumption(id, index - 1, consumption);
				if (result == SUCCESS) {
					printf("消费记录修改成功!\n");
				} else {
					printf("修改失败!\n");
				}
				pause_screen();
				break;
			}
			case 4: {
				char id[20];
				printf("\n=== 删除消费记录 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Consumption consumptions[MAX_CONSUMPTION];
				int count;
				Result result = api->find_consumptions(id, consumptions, &count);

				if (result != SUCCESS) {
					printf("未找到该学生的消费记录!\n");
					pause_screen();
					break;
				}

				printf("\n该学生的消费记录:\n");
				printf("===========================================================================================\n");
				printf("| %-5s | %-10s | %-20s | %-12s |\n", "序号", "金额", "描述", "日期");
				printf("===========================================================================================\n");
				for (int i = 0; i < count; i++) {
					printf("| %-5d | %-10.2f | %-20s | %-12s |\n",
					       i + 1, consumptions[i].amount, consumptions[i].description, consumptions[i].date);
				}
				printf("===========================================================================================\n");

				printf("选择要删除的记录序号(1-%d): ", count);
				int index;
				scanf("%d", &index);
				getchar();

				if (index < 1 || index > count) {
					printf("无效序号!\n");
					pause_screen();
					break;
				}

				printf("确认删除该消费记录 (y/n)? ");
				char confirm;
				scanf("%c", &confirm);
				getchar();

				if (confirm == 'y' || confirm == 'Y') {
					result = api->delete_consumption(id, index - 1);
					if (result == SUCCESS) {
						printf("消费记录删除成功!\n");
					} else {
						printf("删除失败!\n");
					}
				} else {
					printf("删除操作已取消!\n");
				}
				pause_screen();
				break;
			}
			case 5: {
				printf("\n=== 所有消费记录 ===\n");
				Consumption consumptions[MAX_CONSUMPTION];
				int count;

				Result result = api->get_all_consumptions(consumptions, &count);
				if (result == SUCCESS) {
					printf("========================================================================================================\n");
					printf("| %-15s | %-10s | %-20s | %-12s |\n", "学号", "金额", "描述", "日期");
					printf("========================================================================================================\n");
					for (int i = 0; i < count; i++) {
						printf("| %-15s | %-10.2f | %-20s | %-12s |\n",
						       consumptions[i].studentId, consumptions[i].amount,
						       consumptions[i].description, consumptions[i].date);
					}
					printf("========================================================================================================\n");
				} else {
					printf("没有消费记录!\n");
				}
				pause_screen();
				break;
			}
			case 6: {
				char id[20];
				printf("\n=== 消费总额统计 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				float total = api->get_total_consumption(id);
				if (total > 0) {
					printf("学生 %s 的消费总额为: %.2f\n", id, total);
				} else {
					printf("未找到该学生的消费记录!\n");
				}
				pause_screen();
				break;
			}
			case 0:
				break;
			default:
				printf("无效选择!\n");
				pause_screen();
		}
	} while (choice != 0);
}

// 成绩管理功能
void course_management(BackendAPI *api) {
	int choice;
	do {
		clear_screen();
		display_course_menu();
		printf("请输入选择: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
			case 1: {
				Course course;
				printf("\n=== 添加课程成绩 ===\n");
				validate_input("输入学生学号: ", course.studentId, sizeof(course.studentId));

				if (!api->is_student_exist(course.studentId)) {
					printf("该学号不存在!\n");
					pause_screen();
					break;
				}

				validate_input("输入课程名称: ", course.courseName, sizeof(course.courseName));
				course.score = validate_float_input("输入成绩(0-100): ");

				if (course.score < 0 || course.score > 100) {
					printf("成绩必须在0-100之间!\n");
					pause_screen();
					break;
				}

				validate_input("输入学期: ", course.semester, sizeof(course.semester));

				Result result = api->add_course(course);
				if (result == SUCCESS) {
					printf("课程成绩添加成功!\n");
				} else {
					printf("添加失败!\n");
				}
				pause_screen();
				break;
			}
			case 2: {
				char id[20];
				printf("\n=== 查找课程成绩 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Course courses[MAX_COURSES];
				int count;
				Result result = api->find_courses(id, courses, &count);

				if (result == SUCCESS) {
					printf("\n该学生的课程成绩:\n");
					printf("=================================================================================\n");
					printf("| %-20s | %-8s | %-15s |\n", "课程名称", "成绩", "学期");
					printf("=================================================================================\n");

					for (int i = 0; i < count; i++) {
						printf("| %-20s | %-8.1f | %-15s |\n",
						       courses[i].courseName, courses[i].score, courses[i].semester);
					}
					printf("=================================================================================\n");
				} else {
					printf("未找到该学生的课程成绩!\n");
				}
				pause_screen();
				break;
			}
			case 3: {
				char id[20];
				printf("\n=== 修改课程成绩 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Course courses[MAX_COURSES];
				int count;
				Result result = api->find_courses(id, courses, &count);

				if (result != SUCCESS) {
					printf("未找到该学生的课程成绩!\n");
					pause_screen();
					break;
				}

				printf("\n该学生的课程成绩:\n");
				printf("===========================================================================================\n");
				printf("| %-5s | %-20s | %-8s | %-15s |\n", "序号", "课程名称", "成绩", "学期");
				printf("===========================================================================================\n");
				for (int i = 0; i < count; i++) {
					printf("| %-5d | %-20s | %-8.1f | %-15s |\n",
					       i + 1, courses[i].courseName, courses[i].score, courses[i].semester);
				}
				printf("===========================================================================================\n");

				printf("选择要修改的记录序号(1-%d): ", count);
				int index;
				scanf("%d", &index);
				getchar();

				if (index < 1 || index > count) {
					printf("无效序号!\n");
					pause_screen();
					break;
				}

				Course course = courses[index - 1];
				printf("选择要修改的字段:\n");
				printf("1. 课程名称: %s\n", course.courseName);
				printf("2. 成绩: %.1f\n", course.score);
				printf("3. 学期: %s\n", course.semester);
				printf("请输入选择(1-3): ");

				int field;
				scanf("%d", &field);
				getchar();

				switch (field) {
					case 1:
						validate_input("输入新课程名称: ", course.courseName, sizeof(course.courseName));
						break;
					case 2:
						course.score = validate_float_input("输入新成绩(0-100): ");
						if (course.score < 0 || course.score > 100) {
							printf("成绩必须在0-100之间!\n");
							pause_screen();
							break;
						}
						break;
					case 3:
						validate_input("输入新学期: ", course.semester, sizeof(course.semester));
						break;
					default:
						printf("无效选择!\n");
						pause_screen();
						break;
				}

				if (field < 1 || field > 3 || course.score < 0 || course.score > 100) {
					break;
				}

				result = api->modify_course(id, index - 1, course);
				if (result == SUCCESS) {
					printf("课程成绩修改成功!\n");
				} else {
					printf("修改失败!\n");
				}
				pause_screen();
				break;
			}
			case 4: {
				char id[20];
				printf("\n=== 删除课程成绩 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				Course courses[MAX_COURSES];
				int count;
				Result result = api->find_courses(id, courses, &count);

				if (result != SUCCESS) {
					printf("未找到该学生的课程成绩!\n");
					pause_screen();
					break;
				}

				printf("\n该学生的课程成绩:\n");
				printf("===========================================================================================\n");
				printf("| %-5s | %-20s | %-8s | %-15s |\n", "序号", "课程名称", "成绩", "学期");
				printf("===========================================================================================\n");
				for (int i = 0; i < count; i++) {
					printf("| %-5d | %-20s | %-8.1f | %-15s |\n",
					       i + 1, courses[i].courseName, courses[i].score, courses[i].semester);
				}
				printf("===========================================================================================\n");

				printf("选择要删除的记录序号(1-%d): ", count);
				int index;
				scanf("%d", &index);
				getchar();

				if (index < 1 || index > count) {
					printf("无效序号!\n");
					pause_screen();
					break;
				}

				printf("确认删除该课程成绩 (y/n)? ");
				char confirm;
				scanf("%c", &confirm);
				getchar();

				if (confirm == 'y' || confirm == 'Y') {
					result = api->delete_course(id, index - 1);
					if (result == SUCCESS) {
						printf("课程成绩删除成功!\n");
					} else {
						printf("删除失败!\n");
					}
				} else {
					printf("删除操作已取消!\n");
				}
				pause_screen();
				break;
			}
			case 5: {
				printf("\n=== 所有课程成绩 ===\n");
				Course courses[MAX_COURSES];
				int count;

				Result result = api->get_all_courses(courses, &count);
				if (result == SUCCESS) {
					printf("========================================================================================================\n");
					printf("| %-15s | %-20s | %-8s | %-15s |\n", "学号", "课程名称", "成绩", "学期");
					printf("========================================================================================================\n");
					for (int i = 0; i < count; i++) {
						printf("| %-15s | %-20s | %-8.1f | %-15s |\n",
						       courses[i].studentId, courses[i].courseName,
						       courses[i].score, courses[i].semester);
					}
					printf("========================================================================================================\n");
				} else {
					printf("没有课程成绩记录!\n");
				}
				pause_screen();
				break;
			}
			case 6: {
				char id[20];
				printf("\n=== 成绩统计 ===\n");
				validate_input("输入学号: ", id, sizeof(id));

				float total, avg;
				int count;
				api->get_course_stats(id, &total, &avg, &count);

				if (count > 0) {
					printf("统计结果:\n");
					printf("课程总数: %d\n", count);
					printf("成绩总额: %.1f\n", total);
					printf("平均分: %.2f\n", avg);
				} else {
					printf("未找到该学生的课程成绩!\n");
				}
				pause_screen();
				break;
			}
			case 0:
				break;
			default:
				printf("无效选择!\n");
				pause_screen();
		}
	} while (choice != 0);
}

// 前端主程序
int main() {
	printf("Frontend starting...\n");

	// 获取后端API接口
	BackendAPI *api = get_backend_api();
	if (api == NULL) {
		printf("Failed to connect to backend!\n");
		return 1;
	}

	printf("Frontend initialized successfully!\n");
	pause_screen();

	int choice;
	do {
		clear_screen();
		display_main_menu();
		printf("请输入选择: ");
		scanf("%d", &choice);
		getchar();

		switch (choice) {
			case 1:
				student_management(api);
				break;
			case 2:
				consumption_management(api);
				break;
			case 3:
				course_management(api);
				break;
			case 0:
				printf("感谢使用个人信息管理系统，再见!\n");
				break;
			default:
				printf("无效选择，请重新输入!\n");
				pause_screen();
		}
	} while (choice != 0);

	return 0;
}
