#ifndef MANAGERMODEL_H
#define MANAGERMODEL_H
#include "Sysdefine.h"

//清除该成员Id对应的书籍借阅信息，以及增加对应书籍的内容
void clean(char* RemoveId)
{
	LoanBook* work = head_loanbook;
	LoanBook* temp = head_loanbook;
	LoanBook* temp2 = NULL;
	Book* work_book = head_book;
	while (work->next != NULL)
	{
		work = work->next;
		if (temp2 != NULL)
		{
			free(temp2);
		}
		if (strcmp(RemoveId, work->borrowerId) == 0)
		{
			temp->next = work->next;
			temp2 = work;
			while (work_book->next != NULL)
			{
				work_book = work_book->next;
				if (strcmp(work->bookId, work_book->bookId) == 0)
				{
					work_book->book_num += 1;
					work_book->loan_num -= 1;
					work_book = head_book;
					break;
				}
			}
		}
		else
		{
			temp = temp->next;
		}
	}
	return;
}
//注销成员
int RemoveNumber()
{
	printf("********************delete the member**********************\n");
	printf("please input the ID you want to delete\n");
	char Idbuf[ID];
	scanf("%s", Idbuf);
	rewind(stdin);

	Number* work = head_number;
	Number* temp = head_number;
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->Id, Idbuf) == 0)
		{
			if (*head_number->Id != '\0' && strcmp(work->Id, head_number->Id) == 0)
			{
				printf("【notice】fail to delete\n");
				printf("********************fail to delete**********************\n");
				return 0;
			}
			temp->next = work->next;
			clean(work->Id);
			free(work);
			printf("********************succeed to delete**********************\n");
			return 1;
		}
		temp = temp->next;
	}
	printf("【notice】cannot find！\n");
	printf("********************fail to delete**********************\n");
	return -1;
}

//删除书籍
void RemoveBook()
{
	printf("********************delete the book**********************\n");
	Book* work = head_book;
	Book* temp = head_book;
	char buf[BOOKNAME] = { 0 };
	int del_num = 0;
delBookname:
	printf("please input the ID or name you want to delete：");
	scanf("%s", buf);
	rewind(stdin);
	if (buf[0] == '\0')
	{
		printf("【notice】title cannot be empty \n");
		goto delBookname;
	}
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->name, buf) == 0 || strcmp(work->bookId, buf) == 0)
		{
			printf("Outcome：《%s》, Id：%s, author：%s\n, number left：%d\n,number borrowed ：%d\n",
				work->name, work->bookId, work->author_name, work->book_num, work->loan_num);

			printf("Please input the numebr you want to delete, 0 to skip，negative number to return\n");
			scanf("%d", &del_num);
			rewind(stdin);
			if (del_num < 0)
			{
				return;
			}
			else if (del_num == 0)
			{
				continue;
			}
			else
			{
				work->book_num = work->book_num - del_num;
				if (work->book_num <= 0 && work->loan_num > 0)
				{
					work->book_num = 0;
						printf("【notice】some of this books are not returned，cannot be deleted completely，left number0\n");
						printf("********************Finish**********************\n");
					return;
				}
				else if (work->book_num <= 0)
				{
					temp->next = work->next;
					free(work);
						printf("********************Succeed to fail**********************\n");
					return;
				}
			}
		}
		temp = temp->next;
	}
	printf("【notice】cannot find the book！\n");
	printf("********************Finish**********************\n");
}
//增加书籍
void AddBook()
{
	printf("********************add book**********************\n");
	char namebuf[BOOKNAME] = { 0 };
	char author_name[NAME] = { 0 };
	char bookId[BOOKID] = { 0 };
	int book_num = 0;
	Book* work = head_book;
	Book* book = (Book*)malloc(sizeof(Book));
	memset(book, 0, sizeof(Book));

BookNo:
	printf("Please input book ID\n");
	scanf("%s", bookId);
	rewind(stdin);
	if (bookId == NULL)
	{
		printf("【notice】book ID cannot be empty\n");
		goto BookNo;
	}

	printf("Please input the number of book\n");
	scanf("%d", &book_num);
	rewind(stdin);
	if (book_num <= 0)
	{
		printf("【notice】number cannot be 0 or the negative\n");
		printf("********************结束操作**********************\n");
		return;
	}
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->bookId, bookId) == 0)
		{
			printf("【notice】Duplicated ID\n");
			work->book_num += book_num;
			printf("********************finish**********************\n");
			return;
		}
	}
BookName:
	printf("Please input book name\n");
	scanf("%s", namebuf);
	rewind(stdin);
	printf("Please input author name\n");
	scanf("%s", author_name);
	rewind(stdin);
	if (namebuf == NULL || author_name == NULL || *namebuf == '#' || *author_name == '#')
	{
		printf("【notice】book name or author cannot be empty,the initial place cannot be #\n");
		goto BookName;
	}

	strcpy(book->name, namebuf);
	strcpy(book->author_name, author_name);
	strcpy(book->bookId, bookId);
	book->book_num = book_num;
	book->loan_num = 0;

	work->next = book;
	printf("********************succeed to add**********************\n");
	return;
}


//成员查询
void CheckNumber()
{
	printf("********************enquire members**********************\n");
	char buf[NAME] = { 0 };
	int is_all = 0;
	printf("Please input the ID or username you want to enquire, input #all to enquire all information\n");
	scanf("%s", buf);
	if (strcmp(buf, "#all") == 0)
	{
		is_all = 1;
	}

	Number* work = head_number;
	if (is_all == 1)
	{
		while (work->next != NULL)
		{
			work = work->next;
			printf("Outcome：username：%s, Id：%s, permissions：%d\n", work->name, work->Id, work->level);
		}
		return;
	}
	else
	{
		while (work->next != NULL)
		{
			work = work->next;
			if (strcmp(work->name, buf) == 0 || strcmp(work->Id, buf) == 0)
			{
				printf("Outcome：username：%s, Id：%s, permissions：%d\n", work->name, work->Id, work->level);
			}
		}
		return;
	}
	printf("********************Finish**********************\n");
	return;
}

//借阅信息查询
void CheckLoanBook()
{
	printf("********************borrowing information**********************\n");
	LoanBook* work = head_loanbook;
	char buf[BOOKNAME + BOOKID] = { 0 };
	int is_all = 0;

	printf("Please input the ID or book name you want to enquire, 输入 #all to enquire all information\n");
	scanf("%s", buf);
	rewind(stdin);
	if (strcmp(buf, "#all") == 0)
	{
		is_all = 1;
	}
	if (is_all == 1)
	{
		printf("all borrowing information as follows：\n");
		while (work->next != NULL)
		{
			work = work->next;
			printf("《%s》，Id：%s，borrowers：%s\n", work->bookname, work->bookId, work->borrowerId);
		}
	}
	else
	{
		printf("all borrowing information as follows：\n");
		while (work->next != NULL)
		{
			work = work->next;
			if (strcmp(work->bookname, buf) == 0 || strcmp(work->bookId, buf) == 0)
			{
				printf("《%s》，Id：%s，borrowers：%s\n", work->bookname, work->bookId, work->borrowerId);
			}
			else if(strcmp(buf, work->borrowerId) == 0)
			{
				printf("《%s》，Id：%s，borrowers：%s\n", work->bookname, work->bookId, work->borrowerId);
			}
		}
		printf("********************Finish**********************\n");
		return;
	}
	printf("********************Finish**********************\n");
	return;
}
#endif // !USERMODEL_ H
