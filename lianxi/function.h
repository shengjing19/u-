/*��ͷ�ļ���Ҫ����Ϊ
   ������
���Ķ�v1.4 2024-8-17
by shengjing19
*/

#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>

//��������
void green();
void red();
void blue();
void main2();

void sjhs(float rr) //��ʱ��-part1
{
    float hours = rr;
    int whole_hours = (int)hours;
    int minutes = (int)((hours - whole_hours) * 60);
    green();
    printf("\n�ѽ��� %d Сʱ %d  ����      \n", whole_hours, minutes);
    blue();
    printf("\033[1A");
    printf("\033[1A");
    printf("\033[2k");
}
void sj(int k) //��ʱ��-part2
{
    float hours = k / 60.0;
    sjhs(hours);
}

void mousexy()
{
    POINT cursorPos;
    green();
    std::cout << "                 -----------------------------------------------------------------------------\n";
    std::cout << "                / ע��                                                                       /\n";
    std::cout << "               / ��һ�ν��е��ǡ����ԡ�                                                     / \n";
    std::cout << "              /  ��ҳ���һ�α�ˢ�º󣬽����ָ���ƶ������ֵĶԻ���ġ�ȷ������ť��        /  \n";
    std::cout << "             /   �ȴ�10s��������ɹ���������ó���ɹ�                                    /   \n";
    std::cout << "            /    �����������Ĺ�ʱ��֮��                                                  /    \n";
    std::cout << "           ------------------------------------------------------------------------------     \n";
    blue();
    std::cout << "ʹ����ʾ:\n";
    std::cout << "1.��UУ԰��ҳ���ڶ�д˼���������һ�����޽�ȥ����\n";
    red();
    std::cout << "2.�����ÿ����Ԫ�ĵ�һ����Text��A��B��Reading in detail(���ȥ�Ǹ��α�������)\n";
    std::cout << "3.����T���뽫�������л��������������󻯼���\n\n";
    blue();
    green();
    std::cout << "����T��5s�Ӻ�ʼ����UУ԰��ҳˢ�£��ڸ�ʱ�������л�����������ȴ�ˢ��\n�������10s�Ӻ�����ƶ�����ȷ������ť��λ�ý��л�ȡ����\n";
    blue();
    std::cout << "\n����Tִ�� F����(��Сдͨ��)\n������: ";
    char c1[2];
    scanf("%s", c1);
    if (!(strcmp(c1, "T")) || !strcmp(c1, "t"))
    {
        printf("\n\n\n����5s��ʼ,��׼��\n");
        for (int i = 5; i > 0; --i)
        {
            std::cout << i << "��(s)\r";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        keybd_event(VK_F5, 0, 0, 0);
        keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
        Sleep(10000);//F5������ ������F5ʱӦͣ���������Թ����練Ӧ 1000=1s
        if (GetCursorPos(&cursorPos))
        {
            green();
            std::cout << "�ѻ�ȡ������:";
            std::cout << "(" << cursorPos.x << ", " << cursorPos.y << ")\n\n";
            blue();
            SetCursorPos(cursorPos.x, cursorPos.y); //���ָ���ƶ�������λ��
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            //------------- ��ʽ��ʼ-------------------------------------
            std::cout << "��ʽ��ʼ\n\n\n";
            int u = 0, sum = 1;
            for (1;; 1)
            {
                for (int j = 600; j > 0; --j)
                {
                    std::cout << j << "s�������һ��ˢ��  \r";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                keybd_event(VK_F5, 0, 0, 0);
                keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
                Sleep(8000);  //F5������ ������F5ʱӦͣ���������Թ����練Ӧ 1000=1s
                SetCursorPos(cursorPos.x, cursorPos.y); // ����Ϊ��ť��λ��
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                u++;  //ѭ������ ��ʼ0 �Թ���ʱ
                sum = u * 10;  // ��ʱ������ һ��10����
                sj(sum);
            }
        }//�����if
        else {
            const char* dr1 = "��ȡ����ʧ��";
            const char* dr2 = "����";
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
    }//�����if
    else if (!(strcmp(c1, "f")) || !strcmp(c1, "F"))
    {
        system("cls");
        main2();
    }
}

/*
void autoF5()
{
    printf("ʹ����ʾ:\n");
    printf("1.��UУ԰��ҳ���ڶ�д˼���������һ�����޽�ȥ����\n");
    printf("2.����T���뽫�������л��������������󻯼���\n");
    red();
    printf("3.�����ÿ����Ԫ�ĵ�һ����Text��A��B��Reading in detail(���ȥ�Ǹ��α�������).\n");
    printf("4.ֻ������1920*1080�ֱ��ʵ���Ļ");
    blue();
    printf("\n\n׼���ú�����T(��Сдͨ��)��ʼ��F����������\n");
    printf("�����룺");
    char c[2];
    scanf("%s", c);
    if (!(strcmp(c, "T")) || !strcmp(c, "t"))
    {
        printf("\n����5s��ʼ,��׼��\n");
        for (int i = 5; i > 0; --i)
        {
            std::cout << i << "��(s)\r";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        //--------------���Ի���--------------------------------
        keybd_event(VK_F5, 0, 0, 0);//����F5
        keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);//�ͷ�F5
        // �������λ�ò����
        Sleep(1000);//F5������ ������F5ʱӦͣ���������Թ����練Ӧ 1000=1s
        SetCursorPos(934, 597); // ����Ϊ��ť��λ��
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        //----------------------------------------------------------
        system("cls");
        int u = 0, sum = 1;
        //------------- ��ʽ��ʼ1920*1080-------------------------------------
        for (1;;1)
        {
            for (int j = 5; j > 0; --j)
            {
                std::cout << j << "s�������һ��ˢ��  \r";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            keybd_event(VK_F5, 0, 0, 0);//����F5
            keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);//�ͷ�F5
            Sleep(1000);  //F5������ ������F5ʱӦͣ���������Թ����練Ӧ 1000=1s
            // �������λ�ò����
            SetCursorPos(934, 597); // ����Ϊ��ť��λ��
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            u++;  //ѭ������ ��ʼ0 �Թ���ʱ
            sum = u * 10;  // ��ʱ������ һ��10����
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
// ģ�������ֹ���
void ScrollMouse(int delta)
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;   //�������ͣ����
    input.mi.mouseData = delta; // ��ֵ���Ϲ�������ֵ���¹���
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    SendInput(1, &input, sizeof(INPUT));
}

// ģ�������
void click() 
{
    INPUT Input = { 0 };

    // ��ȡ��ǰ���λ��
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    // �ƶ���ָ��λ��
    SetCursorPos(cursorPos.x, cursorPos.y);

    // ģ������������
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));

    ZeroMemory(&Input, sizeof(INPUT));

    // ģ��������̧��
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));
}

void ks()
{
    const int scrollInterval = 1000; // 1��1��
    const int scrollAmount = 120; // �����������������κ�ֵ����120ͨ����ʾһ�Ρ�����������

    // ����ѭ����ֱ�������ⲿ��ֹ ����ֱ�ӹرճ���
    while (TRUE) {
        // ���Ϲ���
        ScrollMouse(scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        // ģ������Ļ���ĵ��
        click();
        // �ȴ�5�루5000���룩
        Sleep(3000);
        // ���¹���
        ScrollMouse(-scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        click();
    }

}

void zd()
{
    int SI, SA, SP;
    printf("\n\n\n\n\n\n");
    printf("������\n\n\n");
    printf("\t\t\tÿ��������¹����Ĵ���:");
    scanf("%d", &SI);
    printf("\t\t\tÿ������ķ���(Խ�����·���Խ��,Ĭ�����õ�Ϊ120):");
    scanf("%d", &SA);
    printf("\t\t\tÿ��ȫ�������ֻ���Ҫ�ȴ���ʱ��(��λ/s):");
    scanf("%d", &SP);
    const int scrollInterval = SI*1000; // 1��1��
    const int scrollAmount = SA; // �����������������κ�ֵ����120ͨ����ʾһ�Ρ�����������
    printf("\n\n\n�������\n����5s�����������л�����Ҫ�����Ĵ���\n�ر��������ֹͣ����\n");
    Sleep(5000);
    // ����ѭ����ֱ�������ⲿ��ֹ ����ֱ�ӹرճ���
    while (TRUE) {
        // ���Ϲ���
        ScrollMouse(scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        // ģ������Ļ���ĵ��
        click();
        // �ȴ�5�루5000���룩
        Sleep(SP*1000);
        // ���¹���
        ScrollMouse(-scrollAmount);
        std::this_thread::sleep_for(std::chrono::milliseconds(scrollInterval));
        click();
    }

}
*/
