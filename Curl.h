#ifndef CURL_H
#define CURL_H

using namespace std;

/**
 * @brief Generic CURL class to fetch data from a source. This header provides the Curl class for basic CURL functionality for fetching data from a URL.
 * @author Brandon Luu
*/
class Curl {
    private:
        /**
            @brief A structure to hold libcurl data.
        */
        struct MemoryStruct {
            char *memory;
            size_t size = 0;
        };
        /**
            @brief An instance of MemoryStruct to hold libcurl data for an instance of Curl.
        */
        struct MemoryStruct data;
        /**
            @brief A link to the page that Curl will request. 
        */
        string url;

        /**
            @brief libcurl write method.
            @param contents A pointer to the response of the request.
            @param size The size of the buffer.
            @param nmemb The size of each element in the buffer.
            @param userp An instance of MemoryStruct that will hold the response. 
        */
        static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    
    public:
        /**
            @brief Constructor for the Spotify CURL class.
            @param u The URL to be requested.
        */
        Curl(string u);

        /**
            @brief Destructor for the Spotify CURL class.
        */
        ~Curl();

        /**
            @brief Fetches the data at the URL.
            @return True if the request was successful, false otherwise.
        */
        bool execute();

        /**
            @brief Get the result of the call.
            @return Returns the data.
        */
        char* result();

        /**
            @brief Get the size in bytes of the data.
            @return Returns size of the data in bytes.
        */
        size_t size();
        
};

#endif