#ifndef USERMODEL_H
#define USERMODEL_H
#include "Sysdefine.h"

void User()
{
	printf("********************Personal information**********************\n");
	printf("username£º%s, Id£º%s, permissions£º%d\n", head_number->name, head_number->Id, head_number->level);
	
	LoanBook* work = head_loanbook;
	printf("your borrowing information as follows£º\n");
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->borrowerId, head_number->Id) == 0)
		{
			printf("¡¶%s¡·£¬Id£º%s\n", work->bookname, work->bookId);
		}
	}
	printf("********************finish**********************\n");
	return;
}
//Êé¼®²éÑ¯
void FindBook()
{
	printf("********************Enquire book**********************\n");
	char buf[BOOKNAME + NAME + BOOKID] = { 0 };
	Book* work = head_book;
	int all = 0;
	printf("Please input the book ID or name£¬author£¬ input #all to enquire all information\n");
	scanf("%s", buf);
	rewind(stdin);

	if (strcmp(buf, "#all") == 0)
	{
		all = 1;
	}

	if (all == 1)
	{
		while (work->next != NULL)
		{
			work = work->next;
			printf("Outcome£º¡¶%s¡·, Id£º%s, author£º%s\n, left number£º%d\n, borrowed number£º%d\n",
				work->name, work->bookId, work->author_name, work->book_num, work->loan_num);
		}
		printf("********************Finish**********************\n");
		return;
	}
	else if (all == 0)
	{
		while (work->next != NULL)
		{
			work = work->next;
			if (strcmp(work->name, buf) == 0 || strcmp(work->bookId, buf) == 0 || strcmp(work->author_name, buf) == 0)
			{
				printf("outcome£º¡¶%s¡·, Id£º%s, author£º%s\n, left number£º%d\n, borrowed number£º%d\n",
					work->name, work->bookId, work->author_name, work->book_num, work->loan_num);
			}
		}
		printf("********************finish**********************\n");
		return;
	}
}

//½èÔÄ
static int brrowbook(const char* bookname, const char* bookId, const char* Id)
{
	LoanBook* loanbook = (LoanBook*)malloc(sizeof(LoanBook));
	memset(loanbook, 0, sizeof(LoanBook));


	LoanBook* work = head_loanbook;
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(Id, work->borrowerId) == 0 && strcmp(bookId, work->bookId) == 0)
		{
			printf("you already borrowed this book£¡\n");
			return 0;
		}
	}
	strcpy(loanbook->bookname, bookname);
	strcpy(loanbook->bookId, bookId);
	strcpy(loanbook->borrowerId, Id);
	work->next = loanbook;
	return 1;
}

//¹é»¹
static void returnbook(const char* bookId)
{
	Book* work = head_book;
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->bookId, bookId) == 0)
		{
			work->book_num += 1;
			work->loan_num -= 1;
			break;
		}
	}
	return;
}
//½èÔÄÊé¼®
void BorrowBook()
{
	printf("********************borrowing**********************\n");
	char buf[BOOKNAME] = { 0 };
	Book*		work = head_book;
	//LoanBook*	lbwork = head_loanbook;
	int choose = 0;
	printf("please input the book ID or name to borrow\n");
	scanf("%s", buf);
	rewind(stdin);
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->name, buf) == 0 || strcmp(work->bookId, buf) == 0)
		{
			printf("Outcome£º¡¶%s¡·, Id£º%s, author£º%s\n, left number£º%d\n, left number£º%d\n",
				work->name, work->bookId, work->author_name, work->book_num, work->loan_num);
			if (work->book_num <= 0)
			{
				printf("¡¾notice¡¿sorry this book is not enough!\n.");
			}
			else
			{
				printf("¡¾input 1 to borrow£¬input other things to skip ¡¿");
				scanf("%d", &choose);
				rewind(stdin);
				switch (choose)
				{
				case 1:
					if (brrowbook(work->name, work->bookId, head_number->Id))
					{	work->book_num -= 1;
						work->loan_num += 1;
						printf("succeed to borrow,please return early£¡\n");
					}
					break;
				default:
					printf("\n");
					break;
				}
			}
		}
		if (strcmp(work->bookId, buf) == 0)
		{
			break;
		}
	}
	printf("********************finish**********************\n");
}

//¹é»¹Êé¼®
void ReturnBook()
{
	printf("********************returning**********************\n");
	char buf[BOOKNAME + BOOKID] = { 0 };
	LoanBook*	lbwork = head_loanbook;
	LoanBook*	temp = head_loanbook;
	
	int choose = 0;
	printf("Please input the book name or book ID you want to return\n");
	scanf("%s", buf);
	rewind(stdin);

	while (lbwork->next != NULL)
	{
		lbwork = lbwork->next;
		if (strcmp(lbwork->bookname, buf) == 0 || strcmp(lbwork->bookId, buf) == 0)
		{
			if (strcmp(lbwork->borrowerId, head_number->Id) == 0)
			{
				printf("Outcome£º¡¶%s¡·, Id£º%s\n",lbwork->bookname, lbwork->bookId);
				printf("input 1 to return,input the other to skip");
				scanf("%d", &choose);
				rewind(stdin);
				switch (choose)
				{
				case 1:
					returnbook(lbwork->bookId);
					temp->next = lbwork->next;
					free(lbwork);
					printf("succeed to return\n");
					printf("********************finish**********************\n");
					return;
				default:
					break;
				}
			}
		}
		temp = temp->next;
	}
	printf("********************finish**********************\n");
}
#endif // !USERMODEL_H

