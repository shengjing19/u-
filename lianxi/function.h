/*该头文件主要功能为
   程序功能
最后改动v1.4 2024-8-17
by shengjing19
*/

#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>

//函数引用
void green();
void red();
void blue();
void main2();

void sjhs(float rr) //计时器-part1
{
    float hours = rr;
    int whole_hours = (int)hours;
    int minutes = (int)((hours - whole_hours) * 60);
    green();
    printf("\n已进行 %d 小时 %d  分钟      \n", whole_hours, minutes);
    blue();
    printf("\033[1A");
    printf("\033[1A");
    printf("\033[2k");
}
void sj(int k) //计时器-part2
{
    float hours = k / 60.0;
    sjhs(hours);
}

void mousexy()
{
    POINT cursorPos;
    green();
    std::cout << "                 -----------------------------------------------------------------------------\n";
    std::cout << "                / 注意                                                                       /\n";
    std::cout << "               / 第一次进行的是“测试”                                                     / \n";
    std::cout << "              /  当页面第一次被刷新后，将鼠标指针移动到出现的对话框的“确定”按钮上        /  \n";
    std::cout << "             /   等待10s后如果被成功点击则启用程序成功                                    /   \n";
    std::cout << "            /    即可享受您的挂时长之旅                                                  /    \n";
    std::cout << "           ------------------------------------------------------------------------------     \n";
    blue();
    std::cout << "使用提示:\n";
    std::cout << "1.打开U校园网页版在读写思政中随便找一个必修进去即可\n";
    red();
    std::cout << "2.最好找每个单元的第一个带Text的A或B的Reading in detail(点进去是个课本的文章)\n";
    std::cout << "3.输入T后请将主窗口切换到浏览器，并最大化即可\n\n";
    blue();
    green();
    std::cout << "输入T后5s钟后开始进行U校园网页刷新，在该时间内请切换到浏览器并等待刷新\n你可以在10s钟后将鼠标移动到“确定”按钮的位置进行获取坐标\n";
    blue();
    std::cout << "\n输入T执行 F返回(大小写通用)\n请输入: ";
    char c1[2];
    scanf("%s", c1);
    if (!(strcmp(c1, "T")) || !strcmp(c1, "t"))
    {
        printf("\n\n\n程序5s后开始,请准备\n");
        for (int i = 5; i > 0; --i)
        {
            std::cout << i << "秒(s)\r";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        keybd_event(VK_F5, 0, 0, 0);
        keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
        Sleep(10000);//F5缓冲区 当按下F5时应停留几秒钟以供网络反应 1000=1s
        if (GetCursorPos(&cursorPos))
        {
            green();
            std::cout << "已获取到坐标:";
            std::cout << "(" << cursorPos.x << ", " << cursorPos.y << ")\n\n";
            blue();
            SetCursorPos(cursorPos.x, cursorPos.y); //鼠标指针移动到坐标位置
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            //------------- 正式开始-------------------------------------
            std::cout << "正式开始\n\n\n";
            int u = 0, sum = 1;
            for (1;; 1)
            {
                for (int j = 600; j > 0; --j)
                {
                    std::cout << j << "s后进行下一次刷新  \r";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                keybd_event(VK_F5, 0, 0, 0);
                keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
                Sleep(8000);  //F5缓冲区 当按下F5时应停留几秒钟以供网络反应 1000=1s
                SetCursorPos(cursorPos.x, cursorPos.y); // 更改为按钮的位置
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                u++;  //循环次数 初始0 以供计时
                sum = u * 10;  // 计时分钟数 一次10分钟
                sj(sum);
            }
        }//最里层if
        else {
            const char* dr1 = "获取坐标失败";
            const char* dr2 = "错误！";
            wchar_t wdr1[20];
            wchar_t wdr2[20];
            MultiByteToWideChar(CP_ACP, 0, dr1, -1, wdr1, 20);
            MultiByteToWideChar(CP_ACP, 0, dr2, -1, wdr2, 20);
            MessageBox(NULL,
                wdr1,
                wdr2,
                MB_ICONERROR | MB_OK);
            system("cls");
            main2();
        }
    }//最外层if
    else if (!(strcmp(c1, "f")) || !strcmp(c1, "F"))
    {
        system("cls");
        main2();
    }
}

/*
void autoF5()
{
    printf("使用提示:\n");
    printf("1.打开U校园网页版在读写思政中随便找一个必修进去即可\n");
    printf("2.输入T后请将主窗口切换到浏览器，并最大化即可\n");
    red();
    printf("3.最好找每个单元的第一个带Text的A或B的Reading in detail(点进去是个课本的文章).\n");
    printf("4.只适用于1920*1080分辨率的屏幕");
    blue();
    printf("\n\n准备好后输入T(大小写通用)后开始，F返回主界面\n");
    printf("请输入：");
    char c[2];
    scanf("%s", c);
    if (!(strcmp(c, "T")) || !strcmp(c, "t"))
    {
        printf("\n程序5s后开始,请准备\n");
        for (int i = 5; i > 0; --i)
        {
            std::cout << i << "秒(s)\r";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        //--------------测试环节--------------------------------
        keybd_event(VK_F5, 0, 0, 0);//按下F5
        keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);//释放F5
        // 设置鼠标位置并点击
        Sleep(1000);//F5缓冲区 当按下F5时应停留几秒钟以供网络反应 1000=1s
        SetCursorPos(934, 597); // 更改为按钮的位置
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        //----------------------------------------------------------
        system("cls");
        int u = 0, sum = 1;
        //------------- 正式开始1920*1080-------------------------------------
        for (1;;1)
        {
            for (int j = 5; j > 0; --j)
            {
                std::cout << j << "s后进行下一次刷新  \r";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            keybd_event(VK_F5, 0, 0, 0);//按下F5
            keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);//释放F5
            Sleep(1000);  //F5缓冲区 当按下F5时应停留几秒钟以供网络反应 1000=1s
            // 设置鼠标位置并点击
            SetCursorPos(934, 597); // 更改为按钮的位置
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            u++;  //循环次数 初始0 以供计时
            sum = u * 10;  // 计时分钟数 一次10分钟
            sj(sum);  
        }
    }
    else if (!(strcmp(c, "f")) || !strcmp(c, "F"))
    {
        system("cls");
        main2();
    }
}
*/

/*
// 模拟鼠标滚轮滚动
void ScrollMouse(int delta)
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;   //输入类型：鼠标
    input.mi.mouseData = delta; // 正值向上滚动，负值向下滚动
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    SendInput(1, &input, sizeof(INPUT));
}

// 模拟鼠标点击
void click() 
{
    INPUT Input = { 0 };

    // 获取当前鼠标位置
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    // 移动到指定位置
    SetCursorPos(cursorPos.x, cursorPos.y);

    // 模拟鼠标左键按下
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));

    ZeroMemory(&Input, sizeof(INPUT));

    // 模拟鼠标左键抬起
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));
}

void ks()
{
    const int scrollInterval = 1000; // 1秒1次
    const int scrollAmount = 120; // 滚动的量，可以是任何值，但120通常表示一次“单击”滚动

    // 无限循环，直到程序被外部终止 例如直接关闭程序
    while (TRUE) {
        // 向上滚动
        ScrollMouse(scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        // 模拟在屏幕中心点击
        click();
        // 等待5秒（5000毫秒）
        Sleep(3000);
        // 向下滚动
        ScrollMouse(-scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        click();
    }

}

void zd()
{
    int SI, SA, SP;
    printf("\n\n\n\n\n\n");
    printf("请输入\n\n\n");
    printf("\t\t\t每秒滚轮上下滚动的次数:");
    scanf("%d", &SI);
    printf("\t\t\t每秒滚动的幅度(越大上下幅度越大,默认设置的为120):");
    scanf("%d", &SA);
    printf("\t\t\t每个全部操作轮回需要等待的时间(单位/s):");
    scanf("%d", &SP);
    const int scrollInterval = SI*1000; // 1秒1次
    const int scrollAmount = SA; // 滚动的量，可以是任何值，但120通常表示一次“单击”滚动
    printf("\n\n\n设置完成\n配置5s后启动，请切换到需要滚动的窗口\n关闭软件即可停止运行\n");
    Sleep(5000);
    // 无限循环，直到程序被外部终止 例如直接关闭程序
    while (TRUE) {
        // 向上滚动
        ScrollMouse(scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        // 模拟在屏幕中心点击
        click();
        // 等待5秒（5000毫秒）
        Sleep(SP*1000);
        // 向下滚动
        ScrollMouse(-scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        click();
    }

}
*/
