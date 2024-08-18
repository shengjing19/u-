/*该头文件主要功能为
   主要UI
最后改动v1.6 2024-8-18
by shengjing19
*/

#include <stdio.h>
#include "function.h"
#include "gn.h"

//颜色
void yellow();
void blue();
void green();
void gx();
//主要功能函数
void autodelup();
void aboutu();
void main2();
int main();

//引用全局变量
extern const char* date2;
extern const char* sver;
extern const char* upsize;

void menu()//菜单
{
	int g;
	printf("\n\t\t\t\t\t\t 选择需要的配置");
	printf("\n\t\t\t\t\t======================================");
	printf("\n\t\t\t\t\t1.适用于U校园的自动配置\n");
	printf("\n\t\t\t\t\t2.关于我们\n");
	printf("\n\n\n\n\n\n");
	printf("输入0以退出程序\n");
	printf("请选择所需操作的序号：");
	std::cout << "\n\n\n\n\n\n";
	std::cout << "\t\t\t\t ---------------------------------------------------\n";
	std::cout << "\t\t\t\t 当前版本:"; green(); std::cout << lver; blue();
	std::cout << "     官方网站:http://hisx.host3v.club";
	printf("\033[7A");
	printf("\033[62D");
	scanf("%d", &g);
	
	switch (g)
	{
	case 1: system("cls"); mousexy(); break;
	case 2: system("cls"); aboutu();
	case 0: break;
	}
}

void update() //检查更新及其UI
{
	autodelup(); //更新包清理函数 gn.h
	system("cls");
	printf("\033[1A");
	printf("\033[2K");
	std::cout << "                                                                                          \n";
	std::cout << "                                                                                          \n";
	//std::cout << "                                                                                        \n";
	std::cout << "                  --------------------------         | 当前版本 ："; localver();
	std::cout << "                 |                          |        |                                    \n";
	std::cout << "                 |   -----           -----  |        | 服务器版本："; printf("   %s\n", sver);
	std::cout << "                 |  | 0 0 |  -----  | 1 1 | |        |                                    \n";
	std::cout << "                 |  | 0 0 |  -----  | 1 1 | |        | 状态："; status();
	std::cout << "                 |   -----           -----  |        |                                    \n";
	std::cout << "                 |                          |        | 大小："; MB1();
	std::cout << "                 ----------------------------        |                                    \n";
	std::cout << "                /   Q W E R T Y U I O P     /        | 程序更新准许码： TYNY3233          \n";
	std::cout << "               /    A S D F G H J K L      /         |                                    \n";
	std::cout << "              /     Z X C V B N M         /          | 更新发布时间："; printf("   %s\n", date2);
	std::cout << "             /      1 2 3 4 5 6 7 8 9 0  /           |                                    \n";
	std::cout << "            -----------------------------            |                                    \n";
	std::cout << "                                                                                          \n";
	std::cout << "         ——————————————————————————————————————\n";
	// 输出字符数组
	yellow();
	printf("\t   更新内容：\n");
	blue();
	uplog(); // 更新日志 gn.h
	gx();   // 更新判断函数 gn.h
	free((void*)sver);
	free((void*)date2);
	free((void*)upsize);
}

void load1() //启动UI 命令动画
{
	Serverlver();
	std::cout << "正在加载必要组件...\n\n";
	std::cout << "Loading function....";
	Sleep(200);
	green();
	std::cout << "     ----ok\n";
	blue();
	std::cout << "Loading libcurl.....";
	Sleep(500);
	green();
	std::cout << "     ----ok\n";
	blue();
	std::cout << "Loading update.....";
	Sleep(1400);
	green();
	std::cout << "      ----ok\n";
	blue();
	std::cout << "Loading download....";
	Sleep(200);
	green();
	std::cout << "     ----ok\n";
	std::cout << "Load Done\n\n\n\n\n";
	blue();
	printf("欢迎使用U校园自助20时长\n");
	Sleep(1200);
	printf("\033[1A");
	printf("\033[2K");
	printf("正在搜索更新....\n");
	Sleep(800);
	update(); //检查更新
}