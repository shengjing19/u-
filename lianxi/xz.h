/*该头文件主要功能为
   须知 关于
最后改动v1.2 2024-8-17
by shengjing19
*/

#include<stdio.h>

//函数引用
void main2();
void red();
void blue();
void green();

 void aboutu()
 {
	 A:
	 std::cout << "关于我们\n";
	 std::cout << "                 -------\n";
	 std::cout << "                 |about|\n";
	 red();
	 std::cout << "                 --------------------------------------------------------------------------------------------\n";
	 std::cout << "                / 版权所有(C)2024笙箫旧景                                                                   /\n";
	 std::cout << "               /  使用许可                                                                                 / \n";
	 std::cout << "              /   允许个人或组织在以下条件下使用:                                                         /  \n";
	 std::cout << "             /    1.非商业用途:                                                                          /   \n";
	 std::cout << "            /       本程序免费开源至Github(GPL-3.0)仅限于非商业用途,禁止售卖此软件。                    /    \n";
	 std::cout << "           /      2.不得修改版权声明                                                                   /     \n";
	 std::cout << "          /         转载或使用本软件的任何内容时，不得修改或删除原始的版权声明和注明出处的信息。      /      \n";
	 std::cout << "         /        3.开源协议 GPL-3.0                                                                 /       \n";
	 std::cout << "        /         使用开源代码修改时必须标注原作者GitHub且必须开源                                  /        \n";
	 std::cout << "        --------------------------------------------------------------------------------------------         \n\n";
	 green();
	 std::cout << "                 --------------------------------------------------------------------------------------------\n";
	 std::cout << "                / U校园自助时长                                                                             /\n";
	 std::cout << "               / (C)2020-2024 笙箫旧景 All rights reserved.                                                / \n";
	 std::cout << "              /   U校园自助时长是根据 GPLv3 许可协议开放许可的。                                          /  \n";
	 std::cout << "             /    链接                                                                                   /   \n";
	 std::cout << "            /       1.官方网站：http://hisx.host3v.club                                                 /    \n";
	 std::cout << "           /        2.作者GitHub：https://github.com/shengjing19                                       /     \n";
	 std::cout << "           --------------------------------------------------------------------------------------------      \n";
	 blue();
	 std::cout << "\n\n\n";
	 std::cout << "输入0以返回主菜单:";
	 int i;
	 scanf("%d", &i);
	 if (i == 0)
	 {
		 system("cls");
		 main2();
	 }
	 else
		 goto A;
}
