#include "file.h"

int main(int argc, char* argv[]) {
	//����ͷ�ڵ�
	User user_table = { "admin","123456",true };//��ʼ��һ������Ա�˻�
	Student student_table = { 0 };
	 
	Start_system(argc, argv,&user_table,&student_table);//�򿪱�
	bool isAdmin = initial_interface(&user_table);//��¼�����ж�Ȩ��
	show_system(isAdmin, &user_table, &student_table);//�򿪽���
	close_system(argc, argv, &user_table, &student_table);//�ر�ϵͳ�������ļ��ٴ�д��

	return 0;
}