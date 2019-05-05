#ifndef SYSDEFINE_H
#define SYSDEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME		35		//������󳤶�
#define BOOKNAME	100		//������󳤶�
#define ID			10		//ID��󳤶�
#define BOOKID		30		//�鼮Id��󳤶�
#define PASSWORD	30		//������󳤶�

#define MIN_LEVEL	0		//�û����Ȩ�ޣ����������Ȩ�ޣ��������Ϣ��

#define BOOK_FILE_NAME		"book"		//�鼮��Ϣ�ļ�
#define NUMBER_FILE_NAME	"number"	//��Ա��Ϣ�ļ�
#define LOAN_FILE_NAME		"loan"		//������Ϣ�ļ�


//��Ա��Ϣ
typedef struct number
{
	char name[NAME];
	char Id[ID];
	char password[PASSWORD];
	int level;				//��Ա�ȼ�Manager = 1��student = 0��
	struct number* next;
} Number;

//�鼮��Ϣ
typedef struct book
{
	char name[BOOKNAME];
	char author_name[NAME];
	char bookId[BOOKID];		//�鼮���
	int	 book_num;			//�鼮����
	int  loan_num;			//�������
	struct book* next;
} Book;

//������Ϣ
typedef struct loanbook
{
	char bookname[BOOKNAME];		//�������
	char bookId[BOOKID];			//�鼮Id
	char borrowerId[ID];			//������Id
	struct loanbook* next;
} LoanBook;

extern Number*		head_number;
extern Book*		head_book;
extern LoanBook*	head_loanbook;

extern int number_Id;	//��ԱId�����¼


#endif // !SYSDEFINE_H


