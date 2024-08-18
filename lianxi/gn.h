/*��ͷ�ļ���Ҫ����Ϊ
   ������
���Ķ�v1.9 2024-8-18
by shengjing19
*/

#include <iostream>
#include <curl/curl.h>
//#include <sstream>  //�ַ�����-��ʽת��
//#include <fstream> //�ļ��������
#include "SimpleIni.h"
#include "color.h"
#include "download.h"

//��������
void main2();

//�������
#define IP "192.168.1.1:12"
std::string lver = "1.3.6"; //���ذ汾

//ȫ�ֱ���
int B232 = 0; //ȫ�ֱ���B232�����Ƿ�ִ�и��²���ָ��
int B233 = 0; //��ȡ�������汾���󷵻��� 
/*
  B233ָ��      B232ָ��   
  0 = Ĭ��ֵ    0 = �������°汾     
  1 = ����      1 = ��Ҫ����
                4 = ����
*/
const char* date2;
const char* sver;
const char* upsize;

void setDate(const char* date) //��̬�����ڴ�
{
    date2 = strdup(date);// Ϊdate2�����ڴ� ����date�����ݸ��Ƶ� date2��
    if (date2 == NULL) 
    {
        perror("strdup failed"); //�ڴ����ʧ��
        exit(1);
    }
}

void setsver(const char* ver) //��̬�����ڴ�
{
    sver = strdup(ver);
    if (sver == NULL) {
        perror("strdup failed");
        exit(1);
    }
}

void setupsize(const char* size) //��̬�����ڴ�
{
    upsize = strdup(size);
    if (upsize == NULL) {
        perror("strdup failed");
        exit(1);
    }
}

// �ص����������ڴ���д������� 
// - contents: ָ����յ������ݵ�ָ��
// - size: �������ݿ�Ĵ�С���ֽ�����
// - nmemb: ���ݿ������
// - s: ָ�� std::string �����ָ�룬���ڴ洢���յ�������
size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* s) 
{
    // �����½������ݵ����ֽ���
    size_t newLength = size * nmemb;
    // ��ȡ��ǰ�ַ����ĳ���
    size_t oldLength = s->size();
    try 
    {
        s->resize(oldLength + newLength); // ���� std::string �Ĵ�С�������½��յ�������
    }
    catch (std::bad_alloc& e) // �ڴ����ʧ��ʱ������ 0 ��ʾ����
    {
        return 0;
    }
    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength); // �����յ������ݸ��Ƶ� std::string ��
    return size * nmemb; // ���سɹ�����������ֽ���
}

//----------------------------------------------------------------------------------------------------------//
void Serverlver() //��ȡ�������汾
{
    CURL* curl; //����curlָ��
    CURLcode res; //����res�������ڴ洢 libcurl �����ķ��ش���
    std::string url = "http://" IP "/sver.ini";
    std::string response; //������ն���
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L); //���ӳ�ʱʱ��
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //���ӵ�ַ
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); //���� libcurl �Ļص����� ������յ������� ͨ���ص�����
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //���� libcurl ������ָ�룬���ڻص������н��յ����û����� ��������Ľ��ն���
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) //���ӷ�����
        {
            CSimpleIniA ini;
            SI_Error rc = ini.LoadData(response.c_str(), response.size()); //����Ӧ�ַ����м������ݵ� ini ���� �������С
            if (rc < 0)
            {
                B233 = 1;
            }
            std::string ver = ini.GetValue("config", "ver", "");//��ȡԶ�˰汾
            std::string date = ini.GetValue("day", "date", "");//��ȡ���·�������
            std::string size = ini.GetValue("size", "mb", "");//��ȡ�������ݰ���С
            setsver(ver.c_str());
            setDate(date.c_str()); //д��ȫ�ֱ���date2
            setupsize(size.c_str());
        }
        else
        {
            B233 = 1;
        }
        curl_easy_cleanup(curl);//�ر�����
    }
}

void status()  //״̬
{
    if (B233 == 0)
    {
        if (sver == lver)
        {
            green();
            std::cout << "   �������\n";
            B232 = 0;
            blue();
        }
        else if (sver != lver)
        {
            red();
            std::cout << "   ��Ҫ����\n";
            B232 = 1;
            blue();
        }
    }
    else if (B233 == 1)
    {
        red();
        std::cout << "   ����\n";
        blue();
    }
}

void localver()                                            //���ذ汾
{
    printf("    %s\n", lver.c_str());
}


void MB1() //��С
{
    if (B233 == 0)
    {
        if (sver == lver)
        {
            green();
            std::cout << "   0MB\n";
            blue();
        }
        else if (sver != lver)
        {
            std::cout << "   " << upsize << "\n";
        }
    }
    else if (B233 == 1)
    {
        red();
        std::cout << "   ����\n";
        blue();
    }
}

//--------------------------------------------------------------------------------------------------------------//
size_t write_callback2(void* contents, size_t size, size_t nmemb, void* userp) 
{
    // �����½������ݵ����ֽ���
    size_t realsize = size * nmemb;
    // ���û��Զ����ָ��ת��Ϊ std::string ָ��
    std::string* data = (std::string*)userp;
    // �����յ�������׷�ӵ� std::string ������
    data->append((char*)contents, realsize);
    return realsize;
}

void uplog()  //������־
{
    CURL* curl; //����curlָ��
    CURLcode res;
    std::string url = "http://" IP "/data.txt";
    std::string response; //������ն���
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2); //���� libcurl �Ļص����� ������յ������� ͨ���ص�����
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //���� libcurl ������ָ�룬���ڻص������н��յ����û����� ��������Ľ��ն���
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) 
        {
            red();
            printf("\n\t          ���ӷ�����ʧ��\n\n\n\n\n");
            blue();
            B232 = 4;
        }
        else {
            std::cout << response << std::endl;// ����ɹ�����ʾ��Ӧ����
        }
        curl_easy_cleanup(curl);
    }
}

void gx() //������������
{
    if (B232 == 1)
    {
        printf("�Ƿ�ʼ����Y/N:");
        char yn[2];
        scanf("%s", yn);
        if (!(strcmp(yn, "Y")) || !(strcmp(yn, "y")))
        {
            setup();
            red();
            printf("�����˳�����");
            Sleep(800);
            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;

            /*STARTUPINFO �� PROCESS_INFORMATION �������ṹ��
            �ڵ��� CreateProcess ����ʱ�ǳ���Ҫ��
            ���Ƿֱ�����ָ���½��̵�������Ϣ�ͽ����½��̵���Ϣ*/

            const char* dr = "C:\\up.exe";//������ֽ�
            wchar_t wdr[30];//������ֽ�
            MultiByteToWideChar(CP_ACP, 0, dr, -1, wdr, 30); //�����ֽ��ַ�drת����ֽ�wdr �Լ���LPWSTR

            if (!CreateProcess(
                NULL,                   // û��ģ�����ƣ�ʹ�������У�
                wdr,                    // ������
                NULL,                   // ���̾�����ɼ̳�
                NULL,                   // �߳̾�����ɼ̳�
                FALSE,                  // ���þ���̳�Ϊ FALSE
                0,                      // û�д�����־
                NULL,                   // ʹ�ø����̵Ļ�������
                NULL,                   // ʹ�ø����̵���ʼĿ¼ 
                &si,                    // ָ�� STARTUPINFO �ṹ��ָ��
                &pi)                    // ָ�� STARTUPINFO �ṹ��ָ��
                )
            { 
               printf("��������ʧ�ܣ�������룺%d��.\n", GetLastError());
               return;
            }
            // �رս��̺��߳̾��
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            exit(0);
        }
        else if (!(strcmp(yn, "N")) || !(strcmp(yn, "n")))
        {
            printf("\033[1A");
            printf("\033[2K");
            red();
            printf("����ȡ����������������..");
            blue();
            Sleep(2000);
            printf("\033[2K");
            printf("\033[24D");
            printf("��ӭʹ�ã�");
            Sleep(1000);
            //printf("\033[1A");
            printf("\033[2K");
            system("cls");
            main2();//
        }
        Sleep(1000);
    }
    else if (B232 == 0)
    {
        green();
        printf("�������°汾��������������..");
        blue();
        Sleep(2000);
        printf("\033[2K");
        printf("\033[28D");
        printf("��ӭʹ�ã�");
        Sleep(1000);
        //printf("\033[1A");
        printf("\033[2K");
        system("cls");
        main2();//
    }
    else if (B232 == 4)
    {
        red();
        printf("����������ʧ�ܣ���������");
        blue();
        Sleep(2000);
        printf("\033[2K");
        printf("\033[26D");
        printf("���θ���ֹͣ,������������....\n");
        Sleep(1300);
        printf("\033[1A");
        printf("\033[2K");
        printf("��ӭʹ�ã�");
        Sleep(1000);
        //printf("\033[1A");
        printf("\033[2K");
        system("cls");
        main2();//
    }
}

/*void removegx() //�ֶ�ɾ�����°�
{
    char c[2];
    printf("����'c'��ɾ�����°�:");
    scanf("%s", c);
    if (!(strcmp(c, "C")) || !(strcmp(c, "c")))
    {
        if (!(remove("C:\\up.exe")))
        {
            green();
            printf("�ɹ�\n");
            blue();
        }
        else
        {
            red();
            printf("ʧ��\n");
            blue();
        }
    }
    else
    {
        red();
        printf("ɾ��������ȡ��\n");
        blue();
    }
    Sleep(1000);
}
*/

void autodelup()
{
    remove("C:\\up.exe");
}
