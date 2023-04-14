
#ifndef SPOTIFYWEBREQUEST_H
#define SPOTIFYWEBREQUEST_H

#include <iostream>
#include <curl/curl.h>

/**
 * @brief Sends requests to the Spotify API. This header provides the SpotifyWebRequest class to send CURL requests with appropriate headers for any Spotify API call. It is a modified version of a libcurl example.
 * @author Brandon Luu
*/
class SpotifyWebRequest {
    private:
        /**
            @brief A structure to hold libcurl data.
        */
        struct MemoryStruct {
            char *memory;
            size_t size = 0;
        };

        // libcurl stuff
        struct MemoryStruct data;
        struct MemoryStruct readData;
        CURL *curl_handle;
        CURLcode res;
        struct curl_slist *headerList = NULL;

        const std::string clientID = "Spotify Client ID Goes Here"; /**< Spotify app client ID. */
        const std::string clientSecret = "Spotify Client Secret Goes Here"; /**< Spotify app client secret. */
        std::string access_token; /**< Access token obtained when first authenticating with the Spotify API. */
        std::string refresh_token; /**< Refresh token used to refresh the access token. */

        /**
            @brief libcurl write method.
        */
        static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
    
    public:
        /**
            @brief Constructor. Authenticates the user's token and prepares the headers for an API call.
            @param code The user's authentication token.
            @param access Whether the code is already authorized or not (is it an access token?)
        */
        SpotifyWebRequest(std::string code, int access);

        /**
            @brief Destructor for the Spotify CURL class.
        */
        ~SpotifyWebRequest();

        /**
            @brief Fetches the data at the URL.
            @param url The URL.
            @param type The type of request (GET, POST, PUT).
            @return Returns whether the request was successful or not.
        */
        bool execute(std::string url, int type);

        /**
            @brief Get the result of the call.
            @return Returns the data.
        */
        std::string result();

        /**
            @brief Get the access token after authenticating.
            @return Returns the access token.
        */
        std::string getAccessToken();
        
        // Type of request
        // This can be an enum instead, but this works.
        int req_GET = 0;
        int req_POST = 1;
        int req_PUT = 2;
};

#endif
