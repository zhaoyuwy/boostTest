#include <iostream>
#include <curl/curl.h>
std::string getPostToken();
int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string s_post_return;
//    getPostToken();
    std::cout << " s_post_return = "<<getPostToken() <<std::endl;
//    Json::Reader reader;
    return 0;
}

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

std::string getPostToken()
{
    CURL *curl;
    CURLcode res;

    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "Authorization:basic NWVfeG9fOThOTlhEYUZ0RmU1STFPbkVmX3QwYTo4RWYwVGRwazA3aEFBTnNzR1RaZm1zOHAwVEVh");
    headers = curl_slist_append(headers, "user_name:c00000000");
    headers = curl_slist_append(headers, "service_name:pntl");
    headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");




//    FILE *fp;
//    if((fp =fopen(filename,"w"))==NULL)
//    {
//        return false;
//    }
    curl = curl_easy_init();
//    ;
        std::string s_post_return;
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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        res = curl_easy_setopt(curl,CURLOPT_WRITEDATA,&s_post_return);
        std::cout << "res CURLOPT_WRITEDATA =" <<res<< std::endl;
        curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L); //remove this to disable verbose output



        res = curl_easy_perform(curl);


        std::cout << "res curl_easy_perform=" <<res<<" and  return = "<< s_post_return << std::endl;
        curl_easy_cleanup(curl);
    }
//    fclose(fp);
    return s_post_return;

}