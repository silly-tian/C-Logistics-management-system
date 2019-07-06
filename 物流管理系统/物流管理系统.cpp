#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"

struct TagThing                  //结构体
{
	int num;                     //货物编号
	char send_place[20];         //发货地
	char send_name[20];			 //发货人
	char send_num[20];           //发货人电话
	char send_time[20];          //发货时间
	char get_place[20];          //收获地
	char get_name[20];           //收货人
	char get_num[20];            //收货人电话
	char get_time[20];           //收货时间
	char thing_name[20];         //货物名称
	int thing_num;               //货物数量
	float thing_tiji;            //货物体积
	float thing_zhongliang;      //货物重量
	float thing_yunfei;          //货物运费
	char thing_yun_way[20];         //货物交付方式
	char thing_yunfei_way[20];      //运费支付方式
	struct TagThing *next;  
};

void fflush();
int Login();
void ChangePassword();
int Menu();
int MenuGuest();
void gotoxy(int x, int y);
int GetMenuNum(int i, struct TagThing *list);
int GetMenuNumGuest(int i, struct TagThing *list);
struct TagThing *CreateNode(struct TagThing *list);
void AddThingByLast(struct TagThing *list, struct TagThing *node);
void ShowAll(struct TagThing *list);
void DeleteByNum(struct TagThing *list);
void LoadingData(struct TagThing *list);
void SaveData(struct TagThing *list);
void ChangeDataByNum(struct TagThing *list);
void FindData(struct TagThing *list);
void QRCode();
void StatisticsData(struct TagThing *list);
void SortData(struct TagThing *list);

void fflush()  //清空缓冲区
{
	int ch;
	while ((ch = getchar()) != EOF && ch != '\n')
	{
		;
	}
}

int Login()  //登录界面
{
	FILE *fp;
	fp = fopen("password.txt", "r");
	if (fp == NULL)
	{
		fp = fopen("password.txt", "w+");
		fprintf(fp, "%s", "2:447=7?");
		fclose(fp);
		fp = fopen("password.txt", "r");
	}
	char password[20];
	char password_right[20];
	int i = -1;
	printf("\n\n\n\n\n\n");
	printf("                                                    ┌────────────────────┬─────────────────────┬────────────────────┐\n");
	printf("                                                    │                    │ 雷森货运物流管理系统│                    │\n");
	printf("                                                    │                    └─────────────────────┘                    │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │                 请输入密码(八位数):                           │\n");
	printf("                                                    │             如果不输入密码，直接回车将进入游客模式            │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    └───────────────────────────────────────────────────────────────┘\n");
	gotoxy(89, 13);
	/*for (int i = 0; i < 8; i++)
	{
		password[i] = _getch();
		printf("*");
	}*/
	do
	{
		i++;
		password[i] = _getch();
		if (password[i] == '\b')
		{
			printf("\b \b");
			i -= 2;
		}
		else if(password[i] == '\r')
		{
			;
		}
		else
		{
			printf("*");
		}
	} while (password[i] != '\r');
	if (password[0] == '\r')
	{
		printf("\n                                                    │                                                            ");
		printf("\n                                                    │                进入游客模式，将在3秒后进入系统\n");
		Sleep(3000);

		return 2;
	}
	password[i] = '\0';
	//scanf("%d", &password);
	//fscanf(fp, "%d", &password_right);
	fscanf(fp, "%s", password_right);
	fclose(fp);
	for (i = 0; i < 8; i++)
	{
		password_right[i] -= i;
	}
	if (strcmp(password, password_right) == 0)
	{
		printf("\n                                                    │                                                            ");
		printf("\n                                                    │                  密码正确，将在3秒后进入系统                  ");
		Sleep(3000);
		return 1;
	}
	else
	{
		printf("\n                                                    │                                                           ");
		printf("\n                                                    │                 密码错误，程序将在3秒后关闭                  \n");
		return 0;
	}
}

void ChangePassword()  //修改密码
{
	char password1[10];
	char password2[10];
	printf("\n\n");
	printf("     请输入新密码(八位数):");
	scanf("%s", password1);
	printf("     请再次输入新密码(八位数):");
	scanf("%s", password2);
	if (strcmp(password1, password2) == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			password1[i] += i;
		}
		FILE *fp;
		fp = fopen("password.txt", "w");
		fprintf(fp, "%s", password1);
		printf("     密码修改成功!\n");
		fclose(fp);
	}
	else
	{
		printf("     两次密码输入不一致。\n");
	}
	printf("     ");
	system("pause");
}

void gotoxy(int x, int y)  //移动光标
{
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

int Menu()  //打印主菜单
{
	system("cls");
	int i;
	printf("\n\n\n\n\n\n");
	printf("                                                    ┌────────────────────┬─────────────────────┬────────────────────┐\n");
	printf("                                                    │                    │ 雷森货运物流管理系统│                    │\n");
	printf("                                                    │                    └─────────────────────┘                    │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │   1. 添加货物信息                                             │\n");
	printf("                                                    │   2. 删除货物信息                                             │\n");
	printf("                                                    │   3. 修改货物信息                                             │\n");
	printf("                                                    │   4. 查找货物信息                                             │\n");
	printf("                                                    │   5. 统计货物信息                                             │\n");
	printf("                                                    │   6. 查看所有货物信息                                         │\n");
	printf("                                                    │   7. 修改登录密码                                             │\n");
	printf("                                                    │   8. 关于                                                     │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │   0. 退出系统                                                 │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │   请输入:                                                     │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    └───────────────────────────────────────────────────────────────┘\n");
	gotoxy(63, 21);
	while ((scanf("%d", &i) != 1) || i < 0 || i > 8)
	{
		gotoxy(67, 21);
		printf("您输入的信息有误，请重新输入:       \b\b\b\b\b\b\b");
		fflush();
	}

	return i;
}

int MenuGuest()  //打印主菜单(游客)
{
	system("cls");
	int i;
	printf("\n\n\n\n\n\n");
	printf("                                                    ┌────────────────────┬─────────────────────┬────────────────────┐\n");
	printf("                                                    │                    │ 雷森货运物流管理系统│                    │\n");
	printf("                                                    │                    └─────────────────────┘                    │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │   1. 查找货物信息                                             │\n");
	printf("                                                    │   2. 统计货物信息                                             │\n");
	printf("                                                    │   3. 查看所有货物信息                                         │\n");
	printf("                                                    │   4. 关于                                                     │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │   0. 退出系统                                                 │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    │   请输入:                                                     │\n");
	printf("                                                    │                                                               │\n");
	printf("                                                    └───────────────────────────────────────────────────────────────┘\n");
	gotoxy(63, 17);
	while ((scanf("%d", &i) != 1) || i < 0 || i > 4)
	{
		gotoxy(67, 17);
		printf("您输入的信息有误，请重新输入:       \b\b\b\b\b\b\b");
		fflush();
	}

	return i;
}

int GetMenuNum(int i, struct TagThing *list)   //获得在菜单输入的编号
{
	switch (i)
	{
	case 1:
		ShowAll(list);
		AddThingByLast(list, CreateNode(list));
		break;
	case 2:
		ShowAll(list);
		DeleteByNum(list);
		break;
	case 3:
		ShowAll(list);
		ChangeDataByNum(list);
		break;
	case 4:
		FindData(list);
		break;
	case 5:
		StatisticsData(list);
		break;
	case 6:
		ShowAll(list);
		break;
	case 7:
		ChangePassword();
		break;
	case 8:
		printf("\n\n\n");
		QRCode();
		system("color F1");
		break;
	default:
		break;
	}
	return i;
}

int GetMenuNumGuest(int i, struct TagThing *list)   //获得在菜单输入的编号(游客)
{
	switch (i)
	{
	case 1:
		FindData(list);
		break;
	case 2:
		StatisticsData(list);
		break;
	case 3:
		ShowAll(list);
		break;
	case 4:
		printf("\n\n\n");
		QRCode();
		system("color F1");
		break;
	default:
		break;
	}
	return i;
}

struct TagThing *CreateNode(struct TagThing *list)  //创建一个结点
{
	int i;
	struct TagThing *pos = list->next;
	struct TagThing *node = (struct TagThing*)malloc(sizeof(struct TagThing));
	node->next = NULL;
	if (!node)
	{
		printf("     申请内存失败");
		return NULL;
	}
	printf("\n\n\n     您将依次输入货物编号，发货地，发货人，发货人电话，发货时间，收货地，收货人，收货人电话，收货时间，货物名称，货物数量，货物体积，货物重量，货物运费，货物交付方式，运费交付方式。\n");
	printf("     请输入货物的编号:");
	while (scanf("%d", &node->num) != 1)
	{
		printf("     输入错误请重新输入:");
		int ch;
		while ((ch = getchar()) != EOF && ch != '\n')
		{
			;
		}
	}
	while (pos)
	{
		if (pos->num == node->num)
		{
			printf("     货物编号与之前的重复，请重新输入!\n");
			printf("     ");
			system("pause");
			fflush();
			return NULL;
		}
		pos = pos->next;
	}
	printf("     请输入货物的发货地:");
	while (scanf("%s", node->send_place) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的发货人:");
	while (scanf("%s", &node->send_name) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的发货人电话:");
	while (scanf("%s", node->send_num) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的发货时间:");
	while (scanf("%s", node->send_time) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的收货地:");
	while (scanf("%s", node->get_place) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的收货人:");
	while (scanf("%s", node->get_name) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的收货人电话:");
	while (scanf("%s", node->get_num) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的收货时间:");
	while (scanf("%s", node->get_time) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的名称:");
	while (scanf("%s", node->thing_name) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的数量:");
	while (scanf("%d", &node->thing_num) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的体积:");
	while (scanf("%f", &node->thing_tiji) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("     请输入货物的重量:");
	while (scanf("%f", &node->thing_zhongliang) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}    
	printf("     请输入货物的运费:");
	while (scanf("%f", &node->thing_yunfei) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	printf("\n");
	printf("     1. 自提\n");
	printf("     2. 送货\n");
	printf("     请选择货物的交付方式:");
	while ((scanf("%d", &i) != 1) || i < 1 || i > 2)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	switch (i)
	{
	case 1:
		node->thing_yun_way[0] = -41;
		node->thing_yun_way[1] = -44;
		node->thing_yun_way[2] = -52;
		node->thing_yun_way[3] = -31;
		node->thing_yun_way[4] = '\0';
		break;
	case 2:
		node->thing_yun_way[0] = -53;
		node->thing_yun_way[1] = -51;
		node->thing_yun_way[2] = -69;
		node->thing_yun_way[3] = -11;
		node->thing_yun_way[4] = '\0';
		break;
	}
	printf("\n");
	printf("     1. 已付\n");
	printf("     2. 回付\n");
	printf("     3. 到付\n");
	printf("     4. 回单\n");
	printf("     请选择货物的运费交付方式:");
	while ((scanf("%d", &i) != 1) || i < 1 || i > 4)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	switch (i)
	{
	case 1:
		node->thing_yunfei_way[0] = -46;
		node->thing_yunfei_way[1] = -47;
		node->thing_yunfei_way[2] = -72;
		node->thing_yunfei_way[3] = -74;
		node->thing_yunfei_way[4] = '\0';
		break;
	case 2:
		node->thing_yunfei_way[0] = -69;
		node->thing_yunfei_way[1] = -40;
		node->thing_yunfei_way[2] = -72;
		node->thing_yunfei_way[3] = -74;
		node->thing_yunfei_way[4] = '\0';
		break;
	case 3:
		node->thing_yunfei_way[0] = -75;
		node->thing_yunfei_way[1] = -67;
		node->thing_yunfei_way[2] = -72;
		node->thing_yunfei_way[3] = -74;
		node->thing_yunfei_way[4] = '\0';
		break;
	case 4:
		node->thing_yunfei_way[0] = -69;
		node->thing_yunfei_way[1] = -40;
		node->thing_yunfei_way[2] = -75;
		node->thing_yunfei_way[3] = -91;
		node->thing_yunfei_way[4] = '\0';
		break;
	default:
		break;
	}
	return node;
}

void AddThingByLast(struct TagThing *list, struct TagThing *node) //尾插法
{
	if (node == NULL)
	{
		return;
	}
	struct TagThing *pos = list;
	while (pos->next)
	{
		pos = pos->next;
	}
	pos->next = node;
	printf("     货物数据录入成功！\n");
	printf("     ");
	system("pause");
}

void ShowAll(struct TagThing *list)  //打印所有信息
{
	struct TagThing *pos = list->next;
	if (pos == NULL)
	{
		printf("\n\n");
		printf("     您的数据为空!\n");
		printf("     ");
		system("pause");
	}
	printf("\n\n");
	printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
	printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
	while (pos)
	{
		printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
		printf("│ %-8d", pos->num);
		printf("│ %-6s", pos->send_place);
		printf("│ %-6s", pos->send_name);
		printf("│ %-12s", pos->send_num);
		printf("│ %-8s", pos->send_time);
		printf("│ %-6s", pos->get_place);
		printf("│ %-6s", pos->get_name);
		printf("│ %-12s", pos->get_num);
		printf("│ %-8s", pos->get_time);
		printf("│ %-8s", pos->thing_name);
		printf("│ %-8d", pos->thing_num);
		printf("│ %-6.fm3", pos->thing_tiji);
		printf("│ %-6.fkg", pos->thing_zhongliang);
		printf("│ %-6.f￥", pos->thing_yunfei);
		printf("│ %-12s", pos->thing_yun_way);
		printf("│ %-12s│\n", pos->thing_yunfei_way);
		pos = pos->next;
	}
	printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");

	system("pause");
}

void DeleteByNum(struct TagThing *list)  //按照货物编号删除
{
	struct TagThing *pos = list->next;
	struct TagThing *posF = list;
	if (!pos)
	{
		printf("\n\n\n     数据已经为空!!!\n");
		printf("     ");
		system("pause");
		return;
	}
	int num;
	printf("\n\n\n     请输入您想要删除的货物的编号:");
	while (scanf("%d", &num) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	while (pos)
	{
		if (pos->num == num)
		{
			posF->next = pos->next;
			pos->next = NULL;
			free(pos);
			printf("     数据删除成功!!!\n");
			printf("     ");
			system("pause");
			return;
		}
		pos = pos->next;
		posF = posF->next;
		if (!pos)
		{
			printf("     未找到编号为%d的货物, 无法删除!!!\n", num);
			printf("     ");
			system("pause");
		}
	}

}

void LoadingData(struct TagThing *list)  //加载数据
{
	FILE *fp;
	struct TagThing *pos = (struct TagThing*)malloc(sizeof(struct TagThing));
	pos->next = NULL;
	if ((fp = fopen("data.txt", "r")) == NULL)
	{
		fp = fopen("data.txt", "w+");
		fp = fopen("data.txt", "r");
		/*printf("\n     文件打开失败\n");
		printf("     ");
		system("pause");
		return 0;*/
	}
	while ((fscanf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%f\t%f\t%f\t%s\t%s", &pos->num, pos->send_place, pos->send_name, pos->send_num, pos->send_time, pos->get_place, pos->get_name, pos->get_num, pos->get_time, pos->thing_name, &pos->thing_num, &pos->thing_tiji, &pos->thing_zhongliang, &pos->thing_yunfei, pos->thing_yun_way, pos->thing_yunfei_way)) == 16)
	{
		list->next = pos;
		list = list->next;
		pos = (struct TagThing*)malloc(sizeof(struct TagThing));
		pos->next = NULL;
	}
	return;
}

void SaveData(struct TagThing *list)  //保存数据
{
	FILE *fp;
	fp = fopen("data.txt", "w");
	struct TagThing* pos = list->next;
	while (pos)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%f\t%f\t%f\t%s\t%s\n", pos->num, pos->send_place, pos->send_name, pos->send_num, pos->send_time, pos->get_place, pos->get_name, pos->get_num, pos->get_time, pos->thing_name, pos->thing_num, pos->thing_tiji, pos->thing_zhongliang, pos->thing_yunfei, pos->thing_yun_way, pos->thing_yunfei_way);
		pos = pos->next;
	}
	fclose(fp);
	return;
}

void ChangeDataByNum(struct TagThing *list)  //根据货物编号修改数据
{
	struct TagThing *pos = list->next;
	struct TagThing *pos1 = list->next;
	int num1;
	if (!pos)
	{
		printf("\n\n\n     数据已经为空!!!\n");
		printf("     ");
		system("pause");
		return;
	}
	int num;
	printf("\n\n\n     请输入您想要修改的货物的编号:");
	while (scanf("%d", &num) != 1)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	while (pos)
	{
		if (pos->num == num)
		{
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
			printf("│ %-8d", pos->num);
			printf("│ %-6s", pos->send_place);
			printf("│ %-6s", pos->send_name);
			printf("│ %-12s", pos->send_num);
			printf("│ %-8s", pos->send_time);
			printf("│ %-6s", pos->get_place);
			printf("│ %-6s", pos->get_name);
			printf("│ %-12s", pos->get_num);
			printf("│ %-8s", pos->get_time);
			printf("│ %-8s", pos->thing_name);
			printf("│ %-8d", pos->thing_num);
			printf("│ %-6.fm3", pos->thing_tiji);
			printf("│ %-6.fkg", pos->thing_zhongliang);
			printf("│ %-6.f￥", pos->thing_yunfei);
			printf("│ %-12s", pos->thing_yun_way);
			printf("│ %-12s│\n", pos->thing_yunfei_way);
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			int i;
			printf("\n     1. 货物编号\n     2. 发货地\n     3. 发货人\n");
			printf("     4. 发货人电话\n     5. 发货时\n     6. 收货地\n");
			printf("     7. 收货人\n     8. 收货人电话\n     9. 收货时间\n");
			printf("     10. 货物名称\n     11. 货物数量\n     12. 货物体积\n");
			printf("     13. 货物重量\n     14. 货物运费\n     15. 货物交付方式\n");
			printf("     16. 运费交付方式\n\n     0. 修改全部数据\n\n");
			printf("     请输入您想要修改的信息为:");
			while (scanf("%d", &i) != 1 || i < 0 || i > 16)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			switch (i)
			{
			case 1:
				printf("\n     请输入修改之后的货物编号:");
				while (scanf("%d", &num1) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				while (pos1)
				{
					if (pos1->num == num1)
					{
						printf("     货物编号与之前的重复，请重新输入!\n");
						printf("     ");
						system("pause");
						fflush();
						return;
					}
					pos1 = pos1->next;
				}
				pos->num = num1;
				break;
			case 2:
				printf("     请输入修改后的货物的发货地:");
				while (scanf("%s", pos->send_place) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 3:
				printf("     请输入修改后的货物的发货人:");
				while (scanf("%s", pos->send_name) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 4:
				printf("     请输入修改后的货物的发货人电话:");
				while (scanf("%s", pos->send_num) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 5:
				printf("     请输入修改后的货物的发货时间:");
				while (scanf("%s", pos->send_time) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 6:
				printf("     请输入修改后的货物的收货地:");
				while (scanf("%s", pos->get_place) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 7:
				printf("     请输入修改后的货物的收货人:");
				while (scanf("%s", pos->get_name) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 8:
				printf("     请输入修改后的货物的收货人电话:");
				while (scanf("%s", pos->get_num) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 9:
				printf("     请输入修改后的货物的收货时间:");
				while (scanf("%s", pos->get_time) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 10:
				printf("     请输入修改后的货物名称:");
				while (scanf("%s", pos->thing_name) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 11:
				printf("     请输入修改后的货物数量:");
				while (scanf("%d", &pos->thing_num) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 12:
				printf("     请输入修改后的货物体积:");
				while (scanf("%f", &pos->thing_tiji) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 13:
				printf("     请输入修改后的货物重量:");
				while (scanf("%f", &pos->thing_zhongliang) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 14:
				printf("     请输入修改后的货物运费:");
				while (scanf("%f", &pos->thing_yunfei) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 15:
				printf("     请输入修改后的货物交付方式:");
				while (scanf("%s", pos->thing_yun_way) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 16:
				printf("     请输入修改后的货物运费支付方式:");
				while (scanf("%s", pos->thing_yunfei_way) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			case 0:
				printf("\n     请输入修改之后的货物编号:");
				while (scanf("%d", &num1) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				while (pos1)
				{
					if (pos1->num == num1)
					{
						printf("     货物编号与之前的重复，请重新输入!\n");
						printf("     ");
						system("pause");
						fflush();
						return;
					}
					pos1 = pos1->next;
				}
				pos->num = num1;
				printf("     请输入修改后的货物的发货地:");
				while (scanf("%s", pos->send_place) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的发货人:");
				while (scanf("%s", pos->send_name) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的发货人电话:");
				while (scanf("%s", pos->send_num) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的发货时间:");
				while (scanf("%s", pos->send_time) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的收货地:");
				while (scanf("%s", pos->get_place) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的收货人:");
				while (scanf("%s", pos->get_name) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的收货人电话:");
				while (scanf("%s", pos->get_num) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物的收货时间:");
				while (scanf("%s", pos->get_time) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物名称:");
				while (scanf("%s", pos->thing_name) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物数量:");
				while (scanf("%d", &pos->thing_num) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物体积:");
				while (scanf("%f", &pos->thing_tiji) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物重量:");
				while (scanf("%f", &pos->thing_zhongliang) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物运费:");
				while (scanf("%f", &pos->thing_yunfei) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物交付方式:");
				while (scanf("%s", pos->thing_yun_way) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				printf("     请输入修改后的货物运费支付方式:");
				while (scanf("%s", pos->thing_yunfei_way) != 1)
				{
					printf("     输入错误请重新输入:");
					fflush();
				}
				break;
			default:
				break;
			}
			printf("\n     修改成功!!!\n");
			printf("     ");
			system("pause");
			return;
		}
		pos = pos->next;
		if (!pos)
		{
			printf("     未找到编号为%d的货物, 无法修改!!!\n", num);
			printf("     ");
			system("pause");
		}
	}
}

void FindData(struct TagThing *list)  //查找数据
{
	int i;
	int i1;
	int i2;
	int j;
	char data[20];
	int flag = 1;
	int flag2 = 0;
	char data1[20];
	char data2[20];
	int count = 0;
	struct TagThing *pos = list->next;
	printf("     1. 模糊查找\n");
	printf("     2. 组合查找\n");
	printf("     3. 返回菜单\n\n");
	printf("     请输入您想要的查询方式:");
	while (scanf("%d", &i) != 1 || i < 1 || i > 3)
	{
		printf("     输入错误请重新输入:");
		fflush();
	}
	switch (i)
	{
	case 1:
		printf("\n\n     1. 按发货地查找\n");
		printf("     2. 按发货人查找\n");
		printf("     3. 按发货人电话查找\n");
		printf("     4. 按发货时间查找\n");
		printf("     5. 按货物名称查找\n\n");
		printf("     请输入查找的方式:");
		while (scanf("%d", &i) != 1 || i < 1 || i > 5)
		{
			printf("     输入错误请重新输入:");
			fflush();
		}
		switch (i)
		{
		case 1:
			printf("     请输入您想要查找的信息:");
			while (scanf("%s", data) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				flag = 1;
				i1 = 0;
				while (pos->send_place[i1])
				{
					if (pos->send_place[i1] == data[0])
					{
						i2 = i1;
						j = 0;
						while (pos->send_place[i2] == data[j])
						{
							i2++;
							j++;
							if (data[j] == '\0')
							{
								printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
								printf("│ %-8d", pos->num);
								printf("│ %-6s", pos->send_place);
								printf("│ %-6s", pos->send_name);
								printf("│ %-12s", pos->send_num);
								printf("│ %-8s", pos->send_time);
								printf("│ %-6s", pos->get_place);
								printf("│ %-6s", pos->get_name);
								printf("│ %-12s", pos->get_num);
								printf("│ %-8s", pos->get_time);
								printf("│ %-8s", pos->thing_name);
								printf("│ %-8d", pos->thing_num);
								printf("│ %-6.fm3", pos->thing_tiji);
								printf("│ %-6.fkg", pos->thing_zhongliang);
								printf("│ %-6.f￥", pos->thing_yunfei);
								printf("│ %-12s", pos->thing_yun_way);
								printf("│ %-12s│\n", pos->thing_yunfei_way);
								flag = 0;
								flag2 = 1;
								count++;
								break;
							}
						}
					}
					if (flag == 0)
					{
						break;
					}
					i1++;
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (flag2 == 1)
			{
				printf("     信息查找成功!!!\n");
				printf("     共找到%d条信息。\n", count);
			}
			else
			{
				printf("     没有找到相关信息!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		case 2:
			printf("     请输入您想要查找的信息:");
			while (scanf("%s", data) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				flag = 1;
				i1 = 0;
				while (pos->send_name[i1])
				{
					if (pos->send_name[i1] == data[0])
					{
						i2 = i1;
						j = 0;
						while (pos->send_name[i2] == data[j])
						{
							i2++;
							j++;
							if (data[j] == '\0')
							{
								printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
								printf("│ %-8d", pos->num);
								printf("│ %-6s", pos->send_place);
								printf("│ %-6s", pos->send_name);
								printf("│ %-12s", pos->send_num);
								printf("│ %-8s", pos->send_time);
								printf("│ %-6s", pos->get_place);
								printf("│ %-6s", pos->get_name);
								printf("│ %-12s", pos->get_num);
								printf("│ %-8s", pos->get_time);
								printf("│ %-8s", pos->thing_name);
								printf("│ %-8d", pos->thing_num);
								printf("│ %-6.fm3", pos->thing_tiji);
								printf("│ %-6.fkg", pos->thing_zhongliang);
								printf("│ %-6.f￥", pos->thing_yunfei);
								printf("│ %-12s", pos->thing_yun_way);
								printf("│ %-12s│\n", pos->thing_yunfei_way);
								flag = 0;
								break;
							}
						}
					}
					if (flag == 0)
					{
						break;
					}
					i1++;
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (flag2 == 1)
			{
				printf("     信息查找成功!!!\n");
			}
			else
			{
				printf("     没有找到相关信息!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		case 3:
			printf("     请输入您想要查找的信息:");
			while (scanf("%s", data) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				flag = 1;
				i1 = 0;
				while (pos->send_num[i1])
				{
					if (pos->send_num[i1] == data[0])
					{
						i2 = i1;
						j = 0;
						while (pos->send_num[i2] == data[j])
						{
							i2++;
							j++;
							if (data[j] == '\0')
							{
								printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
								printf("│ %-8d", pos->num);
								printf("│ %-6s", pos->send_place);
								printf("│ %-6s", pos->send_name);
								printf("│ %-12s", pos->send_num);
								printf("│ %-8s", pos->send_time);
								printf("│ %-6s", pos->get_place);
								printf("│ %-6s", pos->get_name);
								printf("│ %-12s", pos->get_num);
								printf("│ %-8s", pos->get_time);
								printf("│ %-8s", pos->thing_name);
								printf("│ %-8d", pos->thing_num);
								printf("│ %-6.fm3", pos->thing_tiji);
								printf("│ %-6.fkg", pos->thing_zhongliang);
								printf("│ %-6.f￥", pos->thing_yunfei);
								printf("│ %-12s", pos->thing_yun_way);
								printf("│ %-12s│\n", pos->thing_yunfei_way);
								flag = 0;
								break;
							}
						}
					}
					if (flag == 0)
					{
						break;
					}
					i1++;
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (flag2 == 1)
			{
				printf("     信息查找成功!!!\n");
			}
			else
			{
				printf("     没有找到相关信息!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		case 4:
			printf("     请输入您想要查找的信息:");
			while (scanf("%s", data) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				flag = 1;
				i1 = 0;
				while (pos->send_time[i1])
				{
					if (pos->send_time[i1] == data[0])
					{
						i2 = i1;
						j = 0;
						while (pos->send_time[i2] == data[j])
						{
							i2++;
							j++;
							if (data[j] == '\0')
							{
								printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
								printf("│ %-8d", pos->num);
								printf("│ %-6s", pos->send_place);
								printf("│ %-6s", pos->send_name);
								printf("│ %-12s", pos->send_num);
								printf("│ %-8s", pos->send_time);
								printf("│ %-6s", pos->get_place);
								printf("│ %-6s", pos->get_name);
								printf("│ %-12s", pos->get_num);
								printf("│ %-8s", pos->get_time);
								printf("│ %-8s", pos->thing_name);
								printf("│ %-8d", pos->thing_num);
								printf("│ %-6.fm3", pos->thing_tiji);
								printf("│ %-6.fkg", pos->thing_zhongliang);
								printf("│ %-6.f￥", pos->thing_yunfei);
								printf("│ %-12s", pos->thing_yun_way);
								printf("│ %-12s│\n", pos->thing_yunfei_way);
								flag = 0;
								break;
							}
						}
					}
					if (flag == 0)
					{
						break;
					}
					i1++;
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (flag2 == 1)
			{
				printf("     信息查找成功!!!\n");
			}
			else
			{
				printf("     没有找到相关信息!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		case 5:
			printf("     请输入您想要查找的信息:");
			while (scanf("%s", data) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				flag = 1;
				i1 = 0;
				while (pos->thing_name[i1])
				{
					if (pos->thing_name[i1] == data[0])
					{
						i2 = i1;
						j = 0;
						while (pos->thing_name[i2] == data[j])
						{
							i2++;
							j++;
							if (data[j] == '\0')
							{
								printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
								printf("│ %-8d", pos->num);
								printf("│ %-6s", pos->send_place);
								printf("│ %-6s", pos->send_name);
								printf("│ %-12s", pos->send_num);
								printf("│ %-8s", pos->send_time);
								printf("│ %-6s", pos->get_place);
								printf("│ %-6s", pos->get_name);
								printf("│ %-12s", pos->get_num);
								printf("│ %-8s", pos->get_time);
								printf("│ %-8s", pos->thing_name);
								printf("│ %-8d", pos->thing_num);
								printf("│ %-6.fm3", pos->thing_tiji);
								printf("│ %-6.fkg", pos->thing_zhongliang);
								printf("│ %-6.f￥", pos->thing_yunfei);
								printf("│ %-12s", pos->thing_yun_way);
								printf("│ %-12s│\n", pos->thing_yunfei_way);
								flag = 0;
								break;
							}
						}
					}
					if (flag == 0)
					{
						break;
					}
					i1++;
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (flag2 == 1)
			{
				printf("     信息查找成功!!!\n");
			}
			else
			{
				printf("     没有找到相关信息!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		default:
			break;
		}
		break;
	case 2:
		printf("\n\n     1. 发货人与收货人\n");
		printf("     2. 发货人电话与收货人电话\n");
		printf("     3. 发货地与收货地\n\n");
		printf("     请输入查找的方式:");
		while (scanf("%d", &i) != 1 || i < 1 || i > 3)
		{
			printf("     输入错误请重新输入:");
			fflush();
		}
		switch (i)
		{
		case 1:
			printf("\n     请输入发货人:");
			while (scanf("%s", &data1) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("     请输入收货人:");
			while (scanf("%s", &data2) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				if (strcmp(pos->send_name, data1) == 0)
				{
					if (strcmp(pos->get_name, data2) == 0)
					{
						printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
						printf("│ %-8d", pos->num);
						printf("│ %-6s", pos->send_place);
						printf("│ %-6s", pos->send_name);
						printf("│ %-12s", pos->send_num);
						printf("│ %-8s", pos->send_time);
						printf("│ %-6s", pos->get_place);
						printf("│ %-6s", pos->get_name);
						printf("│ %-12s", pos->get_num);
						printf("│ %-8s", pos->get_time);
						printf("│ %-8s", pos->thing_name);
						printf("│ %-8d", pos->thing_num);
						printf("│ %-6.fm3", pos->thing_tiji);
						printf("│ %-6.fkg", pos->thing_zhongliang);
						printf("│ %-6.f￥", pos->thing_yunfei);
						printf("│ %-12s", pos->thing_yun_way);
						printf("│ %-12s│\n", pos->thing_yunfei_way);
						flag2 = 1;
					}
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (!flag2)
			{
				printf("     未找到相关信息!!!\n");
			}
			else
			{
				printf("     信息查找成功!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		case 2:
			printf("\n     请输入发货人电话:");
			while (scanf("%s", &data1) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("     请输入收货人电话:");
			while (scanf("%s", &data2) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				if (strcmp(pos->send_num, data1) == 0)
				{
					if (strcmp(pos->get_num, data2) == 0)
					{
						printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
						printf("│ %-8d", pos->num);
						printf("│ %-6s", pos->send_place);
						printf("│ %-6s", pos->send_name);
						printf("│ %-12s", pos->send_num);
						printf("│ %-8s", pos->send_time);
						printf("│ %-6s", pos->get_place);
						printf("│ %-6s", pos->get_name);
						printf("│ %-12s", pos->get_num);
						printf("│ %-8s", pos->get_time);
						printf("│ %-8s", pos->thing_name);
						printf("│ %-8d", pos->thing_num);
						printf("│ %-6.fm3", pos->thing_tiji);
						printf("│ %-6.fkg", pos->thing_zhongliang);
						printf("│ %-6.f￥", pos->thing_yunfei);
						printf("│ %-12s", pos->thing_yun_way);
						printf("│ %-12s│\n", pos->thing_yunfei_way);
						flag2 = 1;
					}
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (!flag2)
			{
				printf("     未找到相关信息!!!\n");
			}
			else
			{
				printf("     信息查找成功!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		case 3:
			printf("\n     请输入发货地:");
			while (scanf("%s", &data1) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("     请输入收货地:");
			while (scanf("%s", &data2) != 1)
			{
				printf("     输入错误请重新输入:");
				fflush();
			}
			printf("┌─────────┬───────┬───────┬─────────────┬─────────┬───────┬───────┬─────────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────────┬─────────────┐\n");
			printf("│ 货物编号│ 发货地│ 发货人│  发货人电话 │ 发货时间│ 收货地│ 收货人│  收货人电话 │ 收货时间│ 货物名称│ 货物数量│ 货物体积│ 货物重量│ 货物运费│ 货物交付方式│ 运费交付方式│\n");
			while (pos)
			{
				if (strcmp(pos->send_place, data1) == 0)
				{
					if (strcmp(pos->get_place, data2) == 0)
					{
						printf("├─────────┼───────┼───────┼─────────────┼─────────┼───────┼───────┼─────────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────────┼─────────────┤\n");
						printf("│ %-8d", pos->num);
						printf("│ %-6s", pos->send_place);
						printf("│ %-6s", pos->send_name);
						printf("│ %-12s", pos->send_num);
						printf("│ %-8s", pos->send_time);
						printf("│ %-6s", pos->get_place);
						printf("│ %-6s", pos->get_name);
						printf("│ %-12s", pos->get_num);
						printf("│ %-8s", pos->get_time);
						printf("│ %-8s", pos->thing_name);
						printf("│ %-8d", pos->thing_num);
						printf("│ %-6.fm3", pos->thing_tiji);
						printf("│ %-6.fkg", pos->thing_zhongliang);
						printf("│ %-6.f￥", pos->thing_yunfei);
						printf("│ %-12s", pos->thing_yun_way);
						printf("│ %-12s│\n", pos->thing_yunfei_way);
						flag2 = 1;
					}
				}
				pos = pos->next;
			}
			printf("└─────────┴───────┴───────┴─────────────┴─────────┴───────┴───────┴─────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────────┴─────────────┘\n");
			if (!flag2)
			{
				printf("     未找到相关信息!!!\n");
			}
			else
			{
				printf("     信息查找成功!!!\n");
			}
			printf("     ");
			system("pause");
			break;
		default:
			break;
		}
		break;
	case 3:
		return;
		break;
	}
}

void QRCode()  //关于  和  二维码
{
	system("cls");
	MessageBox(NULL, TEXT("名称：物流管理系统\n学校：西安邮电大学\n作者：大数据1802 田霈森"), TEXT("关于"), MB_OK);
	system("color F0");
	printf("\n\n\n");
	printf("                ███████  ██    ███  ██  █  █████    █  ███████\n");
	printf("                █          █  ███    ███  ██  ███      ███  █          █\n");
	printf("                █  ███  █  ███    ████  █    █        █      █  ███  █\n");
	printf("                █  ███  █    ███  ███████      ██  ██    █  ███  █\n");
	printf("                █  ███  █      ██            █    █        █      █  ███  █\n");
	printf("                █          █  █    █  █        █    ██  █    ██  █          █\n");
	printf("                ███████  █  █  █  █  █  █  █  █  █  █  █  ███████\n");
	printf("                                █        ███  █            █  █  █                \n");
	printf("                    ███  █  ██  █  █  ██  ██        ███  ████    ███\n");
	printf("                █        █      █          █  █    █      ██  ██  ██        █\n");
	printf("                        ███  █    █  ███  █    █  ██  ████  █  █  ███\n");
	printf("                ██                    █      █    █  ████  ███  █        ██\n");
	printf("                █████  █  █  █    █    ██  ██        ██    ███      ██\n");
	printf("                      █  █    █      █    ███  █          ██  ██  █  ██    \n");
	printf("                █  ███  ███    █  █                  █  ████  █    █  ██\n");
	printf("                ██    █          █                        ██  █    ██        █  \n");
	printf("                        ███  █  █                        █████  ██  █  ███\n");
	printf("                ██████  ██      ██                  █        ██   █         \n");
	printf("                ███  █  █      █  █                    █  ███  █          ██\n");
	printf("                ██  █  █  █  █  █                        █      ██    █      █\n");
	printf("                ██      █████  █  █                  ██  █    ███████  \n");
	printf("                ███  ██  ███  █  █                    ██        ██    █  █\n");
	printf("                █      ████        █                    ██  ██    █    ████\n");
	printf("                    █  █      █  █      █    █    █████            █      ██\n");
	printf("                            ███  █    ██  ███  ███  ██        ███████\n");
	printf("                █    ███    ████  ███    ██  █    █  █  ██      █    █\n");
	printf("                █      █  █  █      █    █  █  █            ██    ███████\n");
	printf("                █  ██        █  █      ████  ██  ██    █    █  █  █  █  \n");
	printf("                █    █  █████        █    █  █  █  ███  ██████  ██  \n");
	printf("                                ████      █  ████    █  █    █      █    █  \n");
	printf("                ███████    █    ██    █    █  ██  █  █  █  █  ██  ██\n");
	printf("                █          █    ██    ███  ████          ███      █        \n");
	printf("                █  ███  █  ███████  ██  ███████  ██████  ██  \n");
	printf("                █  ███  █  █    ████          █    █            ██  █      \n");
	printf("                █  ███  █  █  ███  █  █      ███  ███    █  █    █  █\n");
	printf("                █          █          █  ██  ██  █      █  ██████        █\n");
	printf("                ███████      ██  █      █    █  ██████    █  █████\n");
	//printf("\n\n想加一下微信吗[]~(￣▽￣)~*\n\n");   前面有多个\n, 后面有一个\n 会打印错误
	printf("\n\n                                   想加一下微信吗[]~(￣▽￣)~*\n\n");
	system("pause");
}

void StatisticsData(struct TagThing *list)   //统计
{
	int count_thing = 0;
	int count_ziti = 0;
	int count_songhuo = 0;
	int count_yifu = 0;
	int count_huifu = 0;
	int count_daofu = 0;
	int count_huidan = 0;
	struct TagThing *pos = list->next;
	while (pos)
	{
		count_thing++;
		if (strcmp(pos->thing_yun_way, "自提") == 0)
		{
			count_ziti++;
		}
		if (strcmp(pos->thing_yun_way, "送货") == 0)
		{
			count_songhuo++;
		}
		if (strcmp(pos->thing_yunfei_way, "已付") == 0)
		{
			count_yifu++;
		}
		if (strcmp(pos->thing_yunfei_way, "回付") == 0)
		{
			count_huifu++;
		}
		if (strcmp(pos->thing_yunfei_way, "到付") == 0)
		{
			count_daofu++;
		}
		if (strcmp(pos->thing_yunfei_way, "回单") == 0)
		{
			count_huidan++;
		}
		pos = pos->next;
	}
	printf("\n\n\n\n                                                    经统计后\n\n");
	printf("                                                    共有货物%d件\n\n", count_thing);
	printf("                                                    货物交付方式为自提的有%d件\n", count_ziti);
	printf("                                                    货物交付方式为送货的有%d件\n", count_songhuo);
	printf("                                                    运费支付方式为已付的有%d件\n", count_yifu);
	printf("                                                    运费支付方式为回付的有%d件\n", count_huifu);
	printf("                                                    运费支付方式为到付的有%d件\n", count_daofu);
	printf("                                                    运费支付方式为回单的有%d件\n", count_huidan);
	printf("                                                    ");
	system("pause");
	return;
}

void SortData(struct TagThing *list)
{
	struct TagThing *pos;
	struct TagThing *posF = list;
	int z_num;                     //货物编号
	char z_send_place[20];         //发货地
	char z_send_name[20];			 //发货人
	char z_send_num[20];           //发货人电话
	char z_send_time[20];          //发货时间
	char z_get_place[20];          //收获地
	char z_get_name[20];           //收货人
	char z_get_num[20];            //收货人电话
	char z_get_time[20];           //收货时间
	char z_thing_name[20];         //货物名称
	int z_thing_num;               //货物数量
	float z_thing_tiji;            //货物体积
	float z_thing_zhongliang;      //货物重量
	float z_thing_yunfei;          //货物运费
	char z_thing_yun_way[20];         //货物交付方式
	char z_thing_yunfei_way[20];      //运费支付方式
	while (posF->next)
	{
		pos = posF->next;
		while (pos)
		{
			if (posF->num > pos->num)
			{
				z_num = pos->num;
				strcpy(z_send_place, pos->send_place);
				strcpy(z_send_name, pos->send_name);
				strcpy(z_send_num, pos->send_num);
				strcpy(z_send_time, pos->send_time);
				strcpy(z_get_place, pos->get_place);
				strcpy(z_get_name, pos->get_name);
				strcpy(z_get_num, pos->get_num);
				strcpy(z_get_time, pos->get_time);
				strcpy(z_thing_name, pos->thing_name);
				z_thing_num = pos->thing_num;
				z_thing_tiji = pos->thing_tiji;
				z_thing_zhongliang = pos->thing_zhongliang;
				z_thing_yunfei = pos->thing_yunfei;
				strcpy(z_thing_yun_way, pos->thing_yun_way);
				strcpy(z_thing_yunfei_way, pos->thing_yunfei_way);

				pos->num = posF->num;
				strcpy(pos->send_place, posF->send_place);
				strcpy(pos->send_name, posF->send_name);
				strcpy(pos->send_num, posF->send_num);
				strcpy(pos->send_time, posF->send_time);
				strcpy(pos->get_place, posF->get_place);
				strcpy(pos->get_name, posF->get_name);
				strcpy(pos->get_num, posF->get_num);
				strcpy(pos->get_time, posF->get_time);
				strcpy(pos->thing_name, posF->thing_name);
				pos->thing_num = posF->thing_num;
				pos->thing_tiji = posF->thing_tiji;
				pos->thing_zhongliang = posF->thing_zhongliang;
				pos->thing_yunfei = posF->thing_yunfei;
				strcpy(pos->thing_yun_way, posF->thing_yun_way);
				strcpy(pos->thing_yunfei_way, posF->thing_yunfei_way);

				posF->num = z_num;
				strcpy(posF->send_place, z_send_place);
				strcpy(posF->send_name, z_send_name);
				strcpy(posF->send_num, z_send_num);
				strcpy(posF->send_time, z_send_time);
				strcpy(posF->get_place, z_get_place);
				strcpy(posF->get_name, z_get_name);
				strcpy(posF->get_num, z_get_num);
				strcpy(posF->get_time, z_get_time);
				strcpy(posF->thing_name, z_thing_name);
				posF->thing_num = z_thing_num;
				posF->thing_tiji = z_thing_tiji;
				posF->thing_zhongliang = z_thing_zhongliang;
				posF->thing_yunfei = z_thing_yunfei;
				strcpy(posF->thing_yun_way, z_thing_yun_way);
				strcpy(posF->thing_yunfei_way, z_thing_yunfei_way);
			}
			pos = pos->next;
		}
		posF = posF->next;
	}
}

int main()  //主函数
{
	system("mode con cols=170 lines=45");
	system("color F1");
	int i;
	struct TagThing *list = (struct TagThing*)malloc(sizeof(struct TagThing));
	list->next = NULL;
	

	/*LoadingData(list);
	while (GetMenuNum(Menu(), list))
	{
		;
	}
	SaveData(list);*/


	LoadingData(list);
	i = Login();
	if (i == 1)
	{
		while (GetMenuNum(Menu(), list))
		{
			;
		}
	}
	else if (i == 2)
	{
		while (GetMenuNumGuest(MenuGuest(), list))
		{
			;
		}
	}
	else
	{
		Sleep(3000);
		return 0;
	}
	SortData(list);
	SaveData(list);

	
	return 0;
}