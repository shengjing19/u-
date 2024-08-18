/*该头文件主要功能为
   执行下载
最后改动v1.3 2024-8-17
by shengjing19
*/

#include <iostream>
#include <curl/curl.h>
#include <fstream>

//静态链接库
#pragma comment(lib, "libcurl.lib")

//函数引用
void red();
void blue();
void green();

// 下载进度回调函数，用于显示下载进度和速度
static int download_progress(void* ptr, curl_off_t total, curl_off_t now, curl_off_t, curl_off_t)
{
    if (total <= 0.0) return 0;// 如果总大小未知，则不显示进度条
    int progress = static_cast<int>((now * 14.0) / total);
    // 计算进度条长度（限制在14个等于号以内）
    // 在控制台中显示进度条、百分比、已下载大小和总大小等信息
    std::cout << "\rDownloading: ";
    // 打印由 progress 个 '=' 字符组成的字符串，表示进度的完成部分,然后打印 14 - progress 个空格，表示进度条的剩余部分
    std::cout << std::string(progress, '=') << std::string(14 - progress, ' ');
    std::cout << " " << static_cast<int>((now * 100.0) / total) << "% ";// 显示百分比 ,使用 static_cast<int> 将百分比值转换为整数
    std::cout << static_cast<int>(now / 1024) << "K/" << static_cast<int>(total / 1024) << "K";// 显示已下载大小和总大小
    std::cout << std::flush; // 刷新控制台输出缓冲区
    return 0;
}

// 数据写入回调函数，用于将下载的数据写入文件
static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);// 将数据写入指定的文件流
    return written;
}

void setup() 
{
    CURL* curl;
    FILE* fp;
    CURLcode res;
    const char* url = "http://192.168.1.1:12/exe1/up2.exe"; // 要下载的文件的URL
    const char* outfilename = "C:/up.exe"; // 下载后保存的本地文件路径
    curl_global_init(CURL_GLOBAL_DEFAULT); // 全局初始化CURL库
    curl = curl_easy_init();// 初始化CURL句柄
    if (curl) {
        fp = fopen(outfilename, "wb");// 打开本地文件以保存数据
        curl_easy_setopt(curl, CURLOPT_URL, url); // 设置要下载的文件的URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);// 设置数据写入回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // 设置数据写入回调函数的参数
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);// 启用进度回调函数
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, download_progress); // 设置进度回调函数
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, fp);// 设置进度回调函数的参数
        res = curl_easy_perform(curl);  // 执行传输操作
        if (res != CURLE_OK) {
            red();
            std::cout << "\nDownload 失败: " << curl_easy_strerror(res) << std::endl;
            blue();
        }
        else {
            green();
            std::cout << "\nDownload 成功\n";
            Sleep(1000);
            printf("\033[1A");
            printf("\033[2K");
            std::cout << "安装包文件将在下次运行时删除\n";
            Sleep(1500);
            printf("\033[1A");
            printf("\033[2K");
            blue();
        }
        curl_easy_cleanup(curl);  // 清理CURL句柄
        fclose(fp); // 关闭本地文件
    }
    curl_global_cleanup();// 全局清理CURL库
}
