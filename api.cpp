#include <iostream>
#include <string>
#include <curl/curl.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// CURL write callback function
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main()
{   
    int number = 0;
    while(true){
    CURL* curl;
    CURLcode res;
    std::string strNumber = std::to_string(number);
    std::string url = "http://127.0.0.1:8000/items/"+strNumber;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "API request failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            json json_data = json::parse(response);

            // Print individual elements of the JSON data
            
            if (json_data["item"] != "null"){
            std::cout << "ID:" << json_data["item_id"] << std::endl;
            std::cout << "Name:" << json_data["item"] << std::endl;
            }
            else{
                break;
            }
        }

        curl_easy_cleanup(curl);
    }
    number++;
    }
    curl_global_cleanup();

    return 0;
}
