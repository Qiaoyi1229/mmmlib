#ifndef SYSMODEL_H
#define SYSMODEL_H
#include "Sysdefine.h"
//写入与加载借阅资源
void WriteLoanData()
{
	FILE* fd_loanbook = fopen(LOAN_FILE_NAME, "wb");
	if (fd_loanbook == NULL)
	{
		return;
	}
	LoanBook* work = head_loanbook;
	while (work->next != NULL)
	{
		work = work->next;
		fwrite(work, sizeof(LoanBook), 1, fd_loanbook);
	}
	return;
}

void ReadLoanData()
{
	FILE* fd_loanbook = fopen(LOAN_FILE_NAME, "rb");
	if (fd_loanbook == NULL)
	{
		return;
	}
	LoanBook* work = head_loanbook;
	LoanBook* temp = NULL;
	while (!feof(fd_loanbook))
	{
		temp = (LoanBook*)malloc(sizeof(LoanBook));
		memset(temp, 0, sizeof(LoanBook));
		fread(temp, sizeof(LoanBook), 1, fd_loanbook);
		if (*temp->bookname == '\0' || *temp->borrowerId == '\0' || *temp->bookId == '\0')
		{
			free(temp);
			continue;
		}
		temp->next = NULL;
		work->next = temp;
		work = work->next;
	}
}

//写入加载用户资源
void ReadNumberData()
{
	FILE* fd_number;
	fd_number = fopen(NUMBER_FILE_NAME, "rb");
	if (fd_number == NULL)
	{
		return;
	}
	Number* work = head_number;
	Number* temp = NULL;
	fread(&number_Id, sizeof(number_Id), 1, fd_number);
	while (!feof(fd_number))
	{
		temp = (Number*)malloc(sizeof(Number));
		memset(temp, 0, sizeof(Number));
		fread(temp, sizeof(Number), 1, fd_number);
		if (*temp->name == '\0' || *temp->password == '\0')
		{
			free(temp);
			continue;
		}
		temp->next = NULL;
		work->next = temp;
		work = work->next;
	}
}
void WriteNumberData()
{
	FILE* fd_number = fopen(NUMBER_FILE_NAME, "wb");
	if (fd_number == NULL)
	{
		return;
	}
	Number* work = head_number;
	fwrite(&number_Id, sizeof(number_Id), 1, fd_number);
	while (work->next != NULL)
	{
		work = work->next;
		fwrite(work, sizeof(Number), 1, fd_number);
	}
	return;
}
//写入与加载书籍资源
void WriteBookData()
{
	FILE* fd_book;
	fd_book = fopen(BOOK_FILE_NAME, "wb");
	if (fd_book == NULL)
	{
		return;
	}
	Book* work = head_book;

	while (work->next != NULL)
	{
		work = work->next;
		fwrite(work, sizeof(Book), 1, fd_book);
	}
	return;
}
void ReadBookData()
{
	FILE* fd_book;
	fd_book = fopen(BOOK_FILE_NAME, "rb");
	if (fd_book == NULL)
	{
		return;
	}
	Book* work = head_book;
	Book* temp = NULL;
	while (!feof(fd_book))
	{
		temp = (Book*)malloc(sizeof(Book));
		memset(temp, 0, sizeof(Book));
		fread(temp, sizeof(Book), 1, fd_book);
		if (*temp->author_name == '\0' || *temp->name == '\0' || *temp->bookId == '\0')
		{
			free(temp);
			continue;
		}
		temp->next = NULL;
		work->next = temp;
		work = work->next;
	}
	return;
}
//释放资源
void FreeResource()
{
	//成员资源
	Number* work_number = head_number;
	Number* temp_number = head_number;
	while (work_number->next != NULL)
	{
		work_number = work_number->next;
		free(temp_number);
		temp_number = work_number;
	}
	free(work_number);

	//书籍资源
	Book* work_book = head_book;
	Book* temp_book = head_book;
	while (work_book->next != NULL)
	{
		work_book = work_book->next;
		free(temp_book);
		temp_book = work_book;
	}
	free(work_book);

	//借阅资源
	LoanBook* work_loan = head_loanbook;
	LoanBook* temp_loan = head_loanbook;
	while (work_loan->next != NULL)
	{
		work_loan = work_loan->next;
		free(temp_loan);
		temp_loan = work_loan;
	}
	free(work_loan);

}
#endif // !SYSMODEL_H


