#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <conio.h>
#include <string.h>

#define MaxSize_name 20
#define MaxScore 100

typedef struct User_s {
	char username[MaxSize_name];
	char password[MaxSize_name];
	bool isAdmin;
	struct User_s* next;
} User;

typedef struct Student_s{
	int id;
	char name[MaxSize_name];
	int chinese;
	int math;
	int english;
	struct Student_s* next;
} Student;

//file.c
void Start_system(int argc, char* argv[],User* user_table, Student* student_table);//��ʼ�������ر�
bool initial_interface(User* user_table);	//��¼����
void show_system(bool isAdmin, User* user_table, Student* student_table);//����Ȩ��չʾ����
void close_system(int argc, char* argv[], User* user_table, Student* student_table);//�ر�ϵͳ
void print_title(void);	//��ӡ����
void Insert_password(char password[]); //��������
void clear_input(void);	//������������
void print_illegal_input(void);//��ӡ�Ƿ�����
void print_end_info(char* c);//��ӡ����������Ϣ��ͬʱ��ͣ
void print_thank(void);	//��ӡ������

//user.c
void show_user_system(const Student* student_table);//�û��˺�ֻ�ô���ѧ����Ϣ����
void find_name(const Student* student_table);
void find_id(const Student* student_table);
void print_studentInfo(const Student *s); //���ѧ����Ϣ

//admin.c
void show_Admin_system(User* user_table, Student* student_table);//����Ա�˻�����ɾ���˺ţ����Դ������ָ��
void find_all(const Student *student_table);
void add_studentInfo(Student* student_table);
void update_studentInfo(Student* student_table);
void delete_student(Student* student_table);
void add_user(User* user_table);
void update_user(User* user_table);
void search_user(const User* user_table);
void delete_user(User* user_table);