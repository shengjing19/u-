/*该头文件主要功能为
   检查更新
最后改动v1.9 2024-8-18
by shengjing19
*/

#include <iostream>
#include <curl/curl.h>
//#include <sstream>  //字符串流-格式转换
//#include <fstream> //文件输入输出
#include "SimpleIni.h"
#include "color.h"
#include "download.h"

//函数引用
void main2();

//软件参数
#define IP "192.168.1.1:12"
std::string lver = "1.3.6"; //本地版本

//全局变量
int B232 = 0; //全局变量B232控制是否执行更新部分指令
int B233 = 0; //获取服务器版本错误返回码 
/*
  B233指令      B232指令   
  0 = 默认值    0 = 已是最新版本     
  1 = 离线      1 = 需要更新
                4 = 离线
*/
const char* date2;
const char* sver;
const char* upsize;

void setDate(const char* date) //动态分配内存
{
    date2 = strdup(date);// 为date2分配内存 并将date的内容复制到 date2中
    if (date2 == NULL) 
    {
        perror("strdup failed"); //内存分配失败
        exit(1);
    }
}

void setsver(const char* ver) //动态分配内存
{
    sver = strdup(ver);
    if (sver == NULL) {
        perror("strdup failed");
        exit(1);
    }
}

void setupsize(const char* size) //动态分配内存
{
    upsize = strdup(size);
    if (upsize == NULL) {
        perror("strdup failed");
        exit(1);
    }
}

// 回调函数，用于处理写入的数据 
// - contents: 指向接收到的数据的指针
// - size: 单个数据块的大小（字节数）
// - nmemb: 数据块的数量
// - s: 指向 std::string 对象的指针，用于存储接收到的数据
size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* s) 
{
    // 计算新接收数据的总字节数
    size_t newLength = size * nmemb;
    // 获取当前字符串的长度
    size_t oldLength = s->size();
    try 
    {
        s->resize(oldLength + newLength); // 调整 std::string 的大小以容纳新接收到的数据
    }
    catch (std::bad_alloc& e) // 内存分配失败时，返回 0 表示错误
    {
        return 0;
    }
    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength); // 将接收到的数据复制到 std::string 中
    return size * nmemb; // 返回成功处理的数据字节数
}

//----------------------------------------------------------------------------------------------------------//
void Serverlver() //获取服务器版本
{
    CURL* curl; //定义curl指针
    CURLcode res; //定义res变量用于存储 libcurl 操作的返回代码
    std::string url = "http://" IP "/sver.ini";
    std::string response; //定义接收对象
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L); //连接超时时间
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //连接地址
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); //设置 libcurl 的回调函数 处理接收到的数据 通过回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //设置 libcurl 的数据指针，用于回调函数中接收到的用户数据 赋给定义的接收对象
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) //连接服务器
        {
            CSimpleIniA ini;
            SI_Error rc = ini.LoadData(response.c_str(), response.size()); //从响应字符串中加载数据到 ini 对象 数据与大小
            if (rc < 0)
            {
                B233 = 1;
            }
            std::string ver = ini.GetValue("config", "ver", "");//获取远端版本
            std::string date = ini.GetValue("day", "date", "");//获取更新发布日期
            std::string size = ini.GetValue("size", "mb", "");//获取更新数据包大小
            setsver(ver.c_str());
            setDate(date.c_str()); //写入全局变量date2
            setupsize(size.c_str());
        }
        else
        {
            B233 = 1;
        }
        curl_easy_cleanup(curl);//关闭连接
    }
}

void status()  //状态
{
    if (B233 == 0)
    {
        if (sver == lver)
        {
            green();
            std::cout << "   无需更新\n";
            B232 = 0;
            blue();
        }
        else if (sver != lver)
        {
            red();
            std::cout << "   需要更新\n";
            B232 = 1;
            blue();
        }
    }
    else if (B233 == 1)
    {
        red();
        std::cout << "   离线\n";
        blue();
    }
}

void localver()                                            //本地版本
{
    printf("    %s\n", lver.c_str());
}


void MB1() //大小
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
        std::cout << "   离线\n";
        blue();
    }
}

//--------------------------------------------------------------------------------------------------------------//
size_t write_callback2(void* contents, size_t size, size_t nmemb, void* userp) 
{
    // 计算新接收数据的总字节数
    size_t realsize = size * nmemb;
    // 将用户自定义的指针转换为 std::string 指针
    std::string* data = (std::string*)userp;
    // 将接收到的数据追加到 std::string 对象中
    data->append((char*)contents, realsize);
    return realsize;
}

void uplog()  //更新日志
{
    CURL* curl; //定义curl指针
    CURLcode res;
    std::string url = "http://" IP "/data.txt";
    std::string response; //定义接收对象
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2); //设置 libcurl 的回调函数 处理接收到的数据 通过回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //设置 libcurl 的数据指针，用于回调函数中接收到的用户数据 赋给定义的接收对象
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) 
        {
            red();
            printf("\n\t          连接服务器失败\n\n\n\n\n");
            blue();
            B232 = 4;
        }
        else {
            std::cout << response << std::endl;// 请求成功，显示响应内容
        }
        curl_easy_cleanup(curl);
    }
}

void gx() //启动更新下载
{
    if (B232 == 1)
    {
        printf("是否开始更新Y/N:");
        char yn[2];
        scanf("%s", yn);
        if (!(strcmp(yn, "Y")) || !(strcmp(yn, "y")))
        {
            setup();
            red();
            printf("正在退出程序");
            Sleep(800);
            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;

            /*STARTUPINFO 和 PROCESS_INFORMATION 这两个结构体
            在调用 CreateProcess 函数时非常重要。
            它们分别用于指定新进程的启动信息和接收新进程的信息*/

            const char* dr = "C:\\up.exe";//定义多字节
            wchar_t wdr[30];//定义宽字节
            MultiByteToWideChar(CP_ACP, 0, dr, -1, wdr, 30); //将多字节字符dr转向宽字节wdr 以兼容LPWSTR

            if (!CreateProcess(
                NULL,                   // 没有模块名称（使用命令行）
                wdr,                    // 命令行
                NULL,                   // 进程句柄不可继承
                NULL,                   // 线程句柄不可继承
                FALSE,                  // 设置句柄继承为 FALSE
                0,                      // 没有创建标志
                NULL,                   // 使用父进程的环境变量
                NULL,                   // 使用父进程的起始目录 
                &si,                    // 指向 STARTUPINFO 结构的指针
                &pi)                    // 指向 STARTUPINFO 结构的指针
                )
            { 
               printf("创建进程失败（错误代码：%d）.\n", GetLastError());
               return;
            }
            // 关闭进程和线程句柄
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            exit(0);
        }
        else if (!(strcmp(yn, "N")) || !(strcmp(yn, "n")))
        {
            printf("\033[1A");
            printf("\033[2K");
            red();
            printf("更新取消！正在启动程序..");
            blue();
            Sleep(2000);
            printf("\033[2K");
            printf("\033[24D");
            printf("欢迎使用！");
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
        printf("已是最新版本！正在启动程序..");
        blue();
        Sleep(2000);
        printf("\033[2K");
        printf("\033[28D");
        printf("欢迎使用！");
        Sleep(1000);
        //printf("\033[1A");
        printf("\033[2K");
        system("cls");
        main2();//
    }
    else if (B232 == 4)
    {
        red();
        printf("服务器连接失败！请检查网络");
        blue();
        Sleep(2000);
        printf("\033[2K");
        printf("\033[26D");
        printf("本次更新停止,正在启动程序....\n");
        Sleep(1300);
        printf("\033[1A");
        printf("\033[2K");
        printf("欢迎使用！");
        Sleep(1000);
        //printf("\033[1A");
        printf("\033[2K");
        system("cls");
        main2();//
    }
}

/*void removegx() //手动删除更新包
{
    char c[2];
    printf("输入'c'来删除更新包:");
    scanf("%s", c);
    if (!(strcmp(c, "C")) || !(strcmp(c, "c")))
    {
        if (!(remove("C:\\up.exe")))
        {
            green();
            printf("成功\n");
            blue();
        }
        else
        {
            red();
            printf("失败\n");
            blue();
        }
    }
    else
    {
        red();
        printf("删除操作已取消\n");
        blue();
    }
    Sleep(1000);
}
*/

void autodelup()
{
    remove("C:\\up.exe");
}
