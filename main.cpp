#include <iostream>
#include <curl/curl.h>
bool getPostToken(char *filename);
int main() {
    std::cout << "Hello, World!" << std::endl;
    getPostToken("/tmp/post.html");
    return 0;
}

bool getPostToken(char *filename)
{
    CURL *curl;
    CURLcode res;

    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "Authorization:basic NWVfeG9fOThOTlhEYUZ0RmU1STFPbkVmX3QwYTo4RWYwVGRwazA3aEFBTnNzR1RaZm1zOHAwVEVh");
    headers = curl_slist_append(headers, "user_name:c00000000");
    headers = curl_slist_append(headers, "service_name:pntl");
    headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");




    FILE *fp;
    if((fp =fopen(filename,"w"))==NULL)
    {
        return false;
    }
    curl = curl_easy_init();
//    string strNew = " ";
    if(curl)
    {

        res= curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        std::cout << "res CURLOPT_HTTPHEADER =" <<res<< std::endl;
//        curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"/tmp/cookie.txt");
//        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"canshu");
        res = curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"grant_type=client_credentials");
        std::cout << "res CURLOPT_POSTFIELDS =" <<res<< std::endl;

        res= curl_easy_setopt(curl,CURLOPT_URL,"https://cas.lf.hwclouds.com:8243/token");
        std::cout << "res CURLOPT_URL =" <<res<< std::endl;
        res= curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0);
        std::cout << "res CURLOPT_SSL_VERIFYPEER =" <<res<< std::endl;
//        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0);
//        curl_easy_setopt(curl,CURLOPT_URL,"http://code.huawei.com");
        res = curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
        std::cout << "res CURLOPT_WRITEDATA =" <<res<< std::endl;
        res = curl_easy_perform(curl);


        std::cout << "res curl_easy_perform=" <<res<< std::endl;
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return true;

}