#include "file.h"

//�������뺯��
void Insert_password(char password[]) {
	char c;
	while ((c = _getch()) != '\r') {
		if ('\b' == c) {
			printf("\b \b");
			password = password - 1;
			*password = '\0';
		}
		else {
			putchar('*');
			*password = c;
			password = password + 1;
		}
	}
}

//��¼���棬�ж��˺��Ƿ���ȷ
int sign_in(User* user_table) {
	//��¼��ֱ�������Ϊֹ
	while (true) {
		system("cls"); //����
		puts("Sign in Student Information Management System");
		User* p = user_table;
		char username[MaxSize_name] = { 0 };
		char password[MaxSize_name] = { 0 };
		//�����û������˺�
		printf("\nUsername: ");
		gets(username);
again_password:
		printf("Password: ");
		Insert_password(password);
		//�ж��Ƿ�������ţ��оͷ���Ȩ�ޣ�û�оͷ���-1
		while (p != NULL) {
			if (!strcmp(p->username, username)) {
				//�ҵ��ˣ���ʼ��������
				if (!strcmp(p->password, password)) {
					print_end_info("Log in succeed.");
					return p->isAdmin;
				}
				//�������
				else {
					print_end_info("Error: password is wrong.");
					goto again_password;
				}
			}
			p = p->next;
		}
		print_end_info("The account could not be found.");
	}
}

//ע����棬��������ͬ�˺ţ�Ĭ��Ϊ�û�
void sign_out(User* user_table) {
	char username[MaxSize_name] = { 0 }, password[MaxSize_name] = { 0 }, secondword[MaxSize_name] = { 0 };
	//ѭ�������û���
again_name:
	system("cls"); //����
	puts("Sign out of Student Information Management System");
	printf("\nUsername: ");
	gets(username);
	//�ж��Ƿ����ظ�
	User* p = user_table;
	while (p != NULL) {
		if (!strcmp(p->username, username)) {
			puts("\nDuplicate name, please enter again.");
			system("pause");
			goto again_name;
		}
		p = p->next;
	}
	//������������
again_word:
	printf("Password: ");
	Insert_password(password);
	printf("\nPassword again: ");
	Insert_password(secondword);
	if (strcmp(password, secondword)) {
		puts("\nThe two entered passwords do not match, enter again.");
		goto again_word;
	}
	//���ӵ��û�����
	User* newNode = (User*)malloc(sizeof(User));
	if (newNode == NULL) {
		perror("calloc failed in add_studnetInfo: ");
		return;
	}
	strcpy(newNode->username, username);
	strcpy(newNode->password, password);
	newNode->next = user_table->next;
	user_table->next = newNode;
	//�˳�
	puts("\nCreat user succesed.press any to continue.");
	system("pause");
}

//У������������ļ������ص��ڴ�
void Start_system(int argc, char* argv[], User* user_table, Student* student_table) {
	if (argc != 3) {
		puts("Error: Invalid Address Entered.\n");
		exit(1);
	}
	//����ֻ��ģʽ�ļ���
	FILE* user_film_p = fopen(argv[1], "ab+");
	if (user_film_p == NULL) {
		perror("userinfo.txt");
		exit(1);
	}
	FILE* student_film_p = fopen(argv[2], "ab+");
	if (student_film_p == NULL) {
		perror("database.txt");
		fclose("Student_film_p");
		exit(1);
	}
	//�����û���Ϣ��
	User* p = user_table;
	do {
		User* newNode = (User*)calloc(1, sizeof(User));
		if (newNode == NULL) {
			perror("calloc failed in start_system: ");
			return;
		}
		p->next = newNode;
		p = p->next;
	} while (fread(p, sizeof(User), 1, user_film_p) != 0);
	//����ѧ����Ϣ��
	Student* s = student_table;
	do {
		Student* newNode = (Student*)calloc(1, sizeof(Student));
		if (newNode == NULL) {
			perror("calloc failed in start_system: ");
			return;
		}
		s->next = newNode;
		s = s->next;
	} while (fread(s, sizeof(Student), 1, student_film_p) != 0);
	//�ر��ļ�
	fclose(user_film_p);
	fclose(student_film_p);
}

//��¼���棬�����Ƿ�Ϊ����Ա
bool initial_interface(User* user_table) {
	//��ӡ����
	print_title();
	puts("1.sign in");
	puts("2.sign out");
	puts("3.exit");
	//�ж�����
	while (true) {
		char ch = getchar();
		clear_input();
		switch (ch) {
		case '1':
			return sign_in(user_table);
		case '2':
			sign_out(user_table);
			return false;
		case '3':
			print_thank();
			exit(0);
		default:
			print_illegal_input();
			break;
		}
	}
}

//չʾϵͳ����
void show_system(bool isAdmin, User* user_table, Student* student_table) {
	system("cls"); 
	print_title();
	if (isAdmin) {
		show_Admin_system(user_table,student_table);
	}
	else {
		show_user_system(student_table);
	}
}

//�ر�ϵͳ�����ѻ����ڵ���Ϣд������ļ����ر��ļ�
void close_system(int argc, char* argv[], User* user_table, Student* student_table) {
	//���Ը���дģʽ���ļ�,����ȫ������
	FILE* user_film_p = fopen(argv[1], "wb+");
	if (user_film_p == NULL) {
		perror("userinfo.txt");
		exit(1);
	}
	FILE* student_film_p = fopen(argv[2], "wb+");
	if (student_film_p == NULL) {
		perror("database.txt");
		fclose("Student_film_p");
		exit(1);
	}
	//���ڴ�������д���ļ�
	User* u = user_table;
	Student* s = student_table->next;
	while (u != NULL && strlen(u->username) > 0) {
		fwrite(u, sizeof(User), 1, user_film_p);
		u = u->next;
	}
	while (s != NULL && strlen(s->name) > 0) {
		fwrite(s, sizeof(Student), 1, student_film_p);
		s = s->next;
	}
	fclose(user_film_p);
	fclose(student_film_p);
}

//��ӡ̧ͷ��Ϣ
void print_title(void) {
	system("cls");
	puts("*******************************************************");
	puts("******** Student Information Management Syetem ********");
	puts("****************** Build by dsy ***********************");
	puts("*******************************************************\n");
}

//��ն��������
void clear_input(void) {
	char temp;
	while ((temp = getchar()) != '\n');
}

//��ӡ�Ƿ�����
void print_illegal_input(void) {
	system("cls");
	puts("Illigal argument. Press any to continue.");
	system("pause");
}

//���������Ϣ������ͣ��Ļ
void print_end_info(char* c) {
	printf("\n%s . press any to continue.\n", c);
	system("pause");
}

//�������ʱ��ӡ��л
void print_thank(void) {
	system("cls");
	print_title();
	puts("Thanks for using. See you next time.\n");
}