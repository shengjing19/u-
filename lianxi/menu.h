/*��ͷ�ļ���Ҫ����Ϊ
   ��ҪUI
���Ķ�v1.6 2024-8-18
by shengjing19
*/

#include <stdio.h>
#include "function.h"
#include "gn.h"

//��ɫ
void yellow();
void blue();
void green();
void gx();
//��Ҫ���ܺ���
void autodelup();
void aboutu();
void main2();
int main();

//����ȫ�ֱ���
extern const char* date2;
extern const char* sver;
extern const char* upsize;

void menu()//�˵�
{
	int g;
	printf("\n\t\t\t\t\t\t ѡ����Ҫ������");
	printf("\n\t\t\t\t\t======================================");
	printf("\n\t\t\t\t\t1.������UУ԰���Զ�����\n");
	printf("\n\t\t\t\t\t2.��������\n");
	printf("\n\n\n\n\n\n");
	printf("����0���˳�����\n");
	printf("��ѡ�������������ţ�");
	std::cout << "\n\n\n\n\n\n";
	std::cout << "\t\t\t\t ---------------------------------------------------\n";
	std::cout << "\t\t\t\t ��ǰ�汾:"; green(); std::cout << lver; blue();
	std::cout << "     �ٷ���վ:http://hisx.host3v.club";
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

void update() //�����¼���UI
{
	autodelup(); //���°������� gn.h
	system("cls");
	printf("\033[1A");
	printf("\033[2K");
	std::cout << "                                                                                          \n";
	std::cout << "                                                                                          \n";
	//std::cout << "                                                                                        \n";
	std::cout << "                  --------------------------         | ��ǰ�汾 ��"; localver();
	std::cout << "                 |                          |        |                                    \n";
	std::cout << "                 |   -----           -----  |        | �������汾��"; printf("   %s\n", sver);
	std::cout << "                 |  | 0 0 |  -----  | 1 1 | |        |                                    \n";
	std::cout << "                 |  | 0 0 |  -----  | 1 1 | |        | ״̬��"; status();
	std::cout << "                 |   -----           -----  |        |                                    \n";
	std::cout << "                 |                          |        | ��С��"; MB1();
	std::cout << "                 ----------------------------        |                                    \n";
	std::cout << "                /   Q W E R T Y U I O P     /        | �������׼���룺 TYNY3233          \n";
	std::cout << "               /    A S D F G H J K L      /         |                                    \n";
	std::cout << "              /     Z X C V B N M         /          | ���·���ʱ�䣺"; printf("   %s\n", date2);
	std::cout << "             /      1 2 3 4 5 6 7 8 9 0  /           |                                    \n";
	std::cout << "            -----------------------------            |                                    \n";
	std::cout << "                                                                                          \n";
	std::cout << "         ����������������������������������������������������������������������������\n";
	// ����ַ�����
	yellow();
	printf("\t   �������ݣ�\n");
	blue();
	uplog(); // ������־ gn.h
	gx();   // �����жϺ��� gn.h
	free((void*)sver);
	free((void*)date2);
	free((void*)upsize);
}

void load1() //����UI �����
{
	Serverlver();
	std::cout << "���ڼ��ر�Ҫ���...\n\n";
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
	printf("��ӭʹ��UУ԰����20ʱ��\n");
	Sleep(1200);
	printf("\033[1A");
	printf("\033[2K");
	printf("������������....\n");
	Sleep(800);
	update(); //������
}