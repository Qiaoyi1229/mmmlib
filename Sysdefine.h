#ifndef SYSDEFINE_H
#define SYSDEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME		35		//人名最大长度
#define BOOKNAME	100		//书名最大长度
#define ID			10		//ID最大长度
#define BOOKID		30		//书籍Id最大长度
#define PASSWORD	30		//密码最大长度

#define MIN_LEVEL	0		//用户最低权限（当低于这个权限，将清除信息）

#define BOOK_FILE_NAME		"book"		//书籍信息文件
#define NUMBER_FILE_NAME	"number"	//成员信息文件
#define LOAN_FILE_NAME		"loan"		//借阅信息文件


//成员信息
typedef struct number
{
	char name[NAME];
	char Id[ID];
	char password[PASSWORD];
	int level;				//成员等级Manager = 1，student = 0；
	struct number* next;
} Number;

//书籍信息
typedef struct book
{
	char name[BOOKNAME];
	char author_name[NAME];
	char bookId[BOOKID];		//书籍编号
	int	 book_num;			//书籍数量
	int  loan_num;			//借出数量
	struct book* next;
} Book;

//借阅信息
typedef struct loanbook
{
	char bookname[BOOKNAME];		//借出书名
	char bookId[BOOKID];			//书籍Id
	char borrowerId[ID];			//借书者Id
	struct loanbook* next;
} LoanBook;

extern Number*		head_number;
extern Book*		head_book;
extern LoanBook*	head_loanbook;

extern int number_Id;	//成员Id分配记录


#endif // !SYSDEFINE_H


