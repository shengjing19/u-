/*��ͷ�ļ���Ҫ����Ϊ
   ִ������
���Ķ�v1.3 2024-8-17
by shengjing19
*/

#include <iostream>
#include <curl/curl.h>
#include <fstream>

//��̬���ӿ�
#pragma comment(lib, "libcurl.lib")

//��������
void red();
void blue();
void green();

// ���ؽ��Ȼص�������������ʾ���ؽ��Ⱥ��ٶ�
static int download_progress(void* ptr, curl_off_t total, curl_off_t now, curl_off_t, curl_off_t)
{
    if (total <= 0.0) return 0;// ����ܴ�Сδ֪������ʾ������
    int progress = static_cast<int>((now * 14.0) / total);
    // ������������ȣ�������14�����ں����ڣ�
    // �ڿ���̨����ʾ���������ٷֱȡ������ش�С���ܴ�С����Ϣ
    std::cout << "\rDownloading: ";
    // ��ӡ�� progress �� '=' �ַ���ɵ��ַ�������ʾ���ȵ���ɲ���,Ȼ���ӡ 14 - progress ���ո񣬱�ʾ��������ʣ�ಿ��
    std::cout << std::string(progress, '=') << std::string(14 - progress, ' ');
    std::cout << " " << static_cast<int>((now * 100.0) / total) << "% ";// ��ʾ�ٷֱ� ,ʹ�� static_cast<int> ���ٷֱ�ֵת��Ϊ����
    std::cout << static_cast<int>(now / 1024) << "K/" << static_cast<int>(total / 1024) << "K";// ��ʾ�����ش�С���ܴ�С
    std::cout << std::flush; // ˢ�¿���̨���������
    return 0;
}

// ����д��ص����������ڽ����ص�����д���ļ�
static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);// ������д��ָ�����ļ���
    return written;
}

void setup() 
{
    CURL* curl;
    FILE* fp;
    CURLcode res;
    const char* url = "http://192.168.1.1:12/exe1/up2.exe"; // Ҫ���ص��ļ���URL
    const char* outfilename = "C:/up.exe"; // ���غ󱣴�ı����ļ�·��
    curl_global_init(CURL_GLOBAL_DEFAULT); // ȫ�ֳ�ʼ��CURL��
    curl = curl_easy_init();// ��ʼ��CURL���
    if (curl) {
        fp = fopen(outfilename, "wb");// �򿪱����ļ��Ա�������
        curl_easy_setopt(curl, CURLOPT_URL, url); // ����Ҫ���ص��ļ���URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);// ��������д��ص�����
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // ��������д��ص������Ĳ���
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);// ���ý��Ȼص�����
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, download_progress); // ���ý��Ȼص�����
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, fp);// ���ý��Ȼص������Ĳ���
        res = curl_easy_perform(curl);  // ִ�д������
        if (res != CURLE_OK) {
            red();
            std::cout << "\nDownload ʧ��: " << curl_easy_strerror(res) << std::endl;
            blue();
        }
        else {
            green();
            std::cout << "\nDownload �ɹ�\n";
            Sleep(1000);
            printf("\033[1A");
            printf("\033[2K");
            std::cout << "��װ���ļ������´�����ʱɾ��\n";
            Sleep(1500);
            printf("\033[1A");
            printf("\033[2K");
            blue();
        }
        curl_easy_cleanup(curl);  // ����CURL���
        fclose(fp); // �رձ����ļ�
    }
    curl_global_cleanup();// ȫ������CURL��
}
