#ifndef BASEMODEL_H
#define BASEMODEL_H
#include "Sysdefine.h"


//Register
void Register(int level)
{
	printf("********************Register ID**********************\n");
	char Idbuf[ID] = { 0 };
	char namebuf[NAME] = { 0 };
	int	Id = 100000;
	Number* work = head_number;

onName: 
	printf("Please input your username.【less than 30 chars】：\n");
	scanf("%s", namebuf);
	rewind(stdin);				//刷新输入缓冲区

	if (namebuf[0] == '#' || namebuf[0] == ' ')
	{
		printf("【notice】The first digit of the user name cannot be # or a space!\n");
		goto onName;
	}
	if (namebuf[0] == '\0')
	{
		printf("【notice】Username can not be empty!\n");
		goto onName;
	}

	namebuf[NAME - 1] = '\0';
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->name, namebuf) == 0)
		{
			printf("【notice】Duplicated username!\n");
			printf("********************Register Failure**********************\n");	
			return;
		}
	}

	Number* number = (Number*)malloc(sizeof(Number));
	memset(number, 0, sizeof(Number));  // 内存空间初始化 
	strcpy(number->name, namebuf);

//密码
onPassword:
	printf("Please input your password:");
	scanf("%s", number->password);
	rewind(stdin);			//刷新输入缓冲区
	if (namebuf[0] == '\0')
	{
		printf("【notice】Password can not be empty!\n");
		goto onPassword;
	}
	number->password[PASSWORD - 1] = '\0';//末位结束
	

	Id = Id + number_Id;
	sprintf(number->Id, "%d", Id);

	number->level = level;
	number->next = NULL;

	work->next = number;
	printf("********************Registration successful**********************\n");
	printf("Your information is as follows:\n");
	printf("username：%s\nId：%s\n password：%s\n", number->name, number->Id, number->password);
	printf("**************************************************\n");
	number_Id++;
	return;
}


//登陆
Number* Login()
{
	printf("********************WELCOME To login**********************\n");
	char buf[NAME + ID] = { 0 };
	char passbuf[PASSWORD] = { 0 };

	printf("please input the name or ID：");
	scanf("%s", buf);
	rewind(stdin);
	printf("please input the password：");
	scanf("%s", passbuf);

	Number* work = head_number;
	while (work->next != NULL)
	{
		work = work->next;
		if (strcmp(work->name, buf) == 0 || strcmp(work->Id, buf) == 0)//找到对应的用户
		{
			if (strcmp(work->password, passbuf) == 0)
			{
				strcpy(head_number->Id, work->Id);
				strcpy(head_number->name, work->name);
				strcpy(head_number->password, work->password);
				head_number->level = work->level;
				printf("********************Succeed to login**********************\n");

				return head_number;
			}
			break;
		}
	}
	printf("【NOtice】username(or Id)，password wrong！\n");
	printf("********************Fail to login**********************\n");
	return NULL;
}

#endif // !BASEMODEL_H

