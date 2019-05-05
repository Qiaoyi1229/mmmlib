#include "Sysdefine.h"
#include "BaseModel.h"
#include "ManagerModel.h"
#include "UserModel.h"
#include "SysModel.h"


Number*		head_number;
Book*		head_book;
LoanBook*	head_loanbook;
int			number_Id = 0;


static void initData()
{
	//初始化链表头节点
	head_book = (Book*)malloc(sizeof(Book));
	memset(head_book, 0, sizeof(Book));
	head_number = (Number*)malloc(sizeof(Number));
	memset(head_number, 0, sizeof(Number));
	head_loanbook = (LoanBook*)malloc(sizeof(LoanBook));
	memset(head_loanbook, 0, sizeof(LoanBook));

	//////系统模块载入资源
	ReadBookData();
	ReadLoanData();
	ReadNumberData();

}

//菜单
static void Menu(Number* nber)
{
	printf("Welcome，%s。your permission is%d。\n",head_number->name, head_number->level);
	printf("********************菜单界面**********************\n");
	int choose = 0;
	while (1)
	{
		printf("1.enquire book\n2.borrow book\n3.return book\n4.clear screen\n5.personal information\n6.quit \n");
		if(nber->level > MIN_LEVEL)
			printf("7.add books\n8.delete books\n9.delete members\n10.enquire borrowing information\n11.enquire member information\n");
		scanf("%d", &choose);
		rewind(stdin);
		switch (choose)
		{
		case 1:
			FindBook();
			break;
		case 2:
			BorrowBook();
			break;
		case 3:
			ReturnBook();
			break;
		case 4:
#ifdef WIN32 
			system("cls");
#else
			system("clear");
#endif
			break;
		case 5:
			User();
			break;
		case 6:
			WriteBookData();
			WriteLoanData();
			return;
		case 7:
			if (nber->level <= MIN_LEVEL)
				break;
			AddBook();
			break;
		case 8:
			if (nber->level <= MIN_LEVEL)
				break;
			RemoveBook();
			break;
		case 9:
			if (nber->level <= MIN_LEVEL)
				break;
			RemoveNumber();
			break;
		case 10:
			if (nber->level <= MIN_LEVEL)
				break;
			CheckLoanBook();
			break;
		case 11:
			if (nber->level <= MIN_LEVEL)
				break;
			CheckNumber();
			break;
		}
	}
	return;
}
int main()
{
	initData();
	printf("**************************************************\n");
	printf("             WELCOME             \n");
	printf("**************************************************\n");
	printf("Input number to choose\n");
	int choose = 0;
	while (1)
	{
		printf("1.login\n2.student register \n3.manager register\n4.clear screen\n5.quit\n");
		scanf("%d", &choose);
		rewind(stdin);
		switch (choose)
		{
		case 1:
		{
			Number* number = Login();
			if (number == NULL)
				continue;
			Menu(number);
			break;
		}
		case 2:
		{
			Register(0);
			break;
		}
		case 3:
		{
			Register(1);
			break;
		}
		case 4:
		{
#ifdef WIN32 
			system("cls");
#else
			system("clear");
#endif
			break;
		}
		case 5:
		{
			WriteNumberData();
			FreeResource();
			exit(1);
			break;
		}
		default:
			break;
		}
	}
	
	getchar();
    return 0;
}


