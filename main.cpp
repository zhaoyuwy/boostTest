#include <iostream>
#include <curl/curl.h>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost::property_tree;
std::string GetTokenString();
std::string getPostToken();
int SendPostData(char *filename);
int main() {
    std::cout << "Hello, World!" << std::endl;
    int n =SendPostData("/tmp/post2.html");
//    SendPostData{"/tmp/post2.html"};
    cout<< n<<endl;
    cout<< n<<endl;
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
//        std::cout << "res CURLOPT_HTTPHEADER =" <<res<< std::endl;
//        curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"/tmp/cookie.txt");
//        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"canshu");
        res = curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"grant_type=client_credentials");
//        std::cout << "res CURLOPT_POSTFIELDS =" <<res<< std::endl;

        res= curl_easy_setopt(curl,CURLOPT_URL,"https://cas.lf.hwclouds.com:8243/token");
//        std::cout << "res CURLOPT_URL =" <<res<< std::endl;
        res= curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0);
//        std::cout << "res CURLOPT_SSL_VERIFYPEER =" <<res<< std::endl;
//        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0);
//        curl_easy_setopt(curl,CURLOPT_URL,"http://code.huawei.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        res = curl_easy_setopt(curl,CURLOPT_WRITEDATA,&s_post_return);
//        std::cout << "res CURLOPT_WRITEDATA =" <<res<< std::endl;
//        curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L); //remove this to disable verbose output



        res = curl_easy_perform(curl);


//        std::cout << "res curl_easy_perform=" <<res<<" and  return = "<< s_post_return << std::endl;
        curl_easy_cleanup(curl);
    }
//    fclose(fp);
    return s_post_return;

}


string GetTokenString(){
    istringstream iss;

    std::string s_post_return;
//    getPostToken();
//    std::cout << " s_post_return = "<<getPostToken() <<std::endl;

    s_post_return = getPostToken();
    iss.str(s_post_return);

    ptree item;
    read_json(iss,item);

    string n = item.get<string>("access_token");
//    cout << "n = " <<n<<endl;
    return n;
}

int SendPostData(char *filename)
{
    cout<<"#######################postdata = "<<filename;
    CURL *curl;
    CURLcode res;

    struct curl_slist *headers = NULL;
    string tokenstring ="Authorization:Bearer "+GetTokenString();
    cout<<"get token ok and tokenstring is =" << tokenstring<<endl;
    headers = curl_slist_append(headers, tokenstring.c_str());
    headers = curl_slist_append(headers, "user_name:c00000000");
    headers = curl_slist_append(headers, "service_name:pntl");
    headers = curl_slist_append(headers, "Content-Type:application/json");

    curl = curl_easy_init();
    std::string s_post_return;

//        FILE *fp;
//    if((fp =fopen(filename,"w"))==NULL)
//    {
//        return false;
//    }
    if(curl)
    {

        res= curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        res= curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"{\"test\":\"11233\"}");

        res= curl_easy_setopt(curl,CURLOPT_URL,"https://cas.lf.hwclouds.com:8243/Kafka/v1/mq/pntl");
        res= curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        res = curl_easy_setopt(curl,CURLOPT_WRITEDATA,&s_post_return);
//        res = curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
        curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L); //remove this to disable verbose output


        res = curl_easy_perform(curl);

        cout<<"curl_easy_perform rst ="<<res<<endl;

        curl_easy_cleanup(curl);
    }


    istringstream iss;

//    getPostToken();
//    std::cout << " s_post_return = "<<getPostToken() <<std::endl;

    iss.str(s_post_return);

    ptree item;
    read_json(iss,item);

    int n = item.get<int>("code");
    return n;

}