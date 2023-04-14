/**
 * @brief Sends requests to the Spotify API. This file implements the SpotifyWebRequest class to send CURL requests with appropriate headers for any Spotify API call. It is a modified version of a libcurl example.
 * @author Brandon Luu
*/

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <curl/curl.h>
#include <iostream>

using namespace std;

#include "json.hpp"
using json = nlohmann::json;

#include "SpotifyWebRequest.h"

/*
  getinmemory.c's function for writing new data to the MemoryStruct
  Appears to return some size of the data
*/
size_t SpotifyWebRequest::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

/*
// Creates the request class. Sets the Spotify OAuth2 token and headers needed.
*/
SpotifyWebRequest::SpotifyWebRequest(string code, int access = 0) {
  // Allocate memory for strings
  data.memory = (char*)malloc(1);

  // if access flag isnt marked, get a new token
  if (!access) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    // set form data and post
    headerList = curl_slist_append(headerList, "Content-Type: application/x-www-form-urlencoded");
    string formdata = "grant_type=authorization_code&code=" + code + "&redirect_uri=https://www.blank.org/&client_id=" + clientID + "&client_secret=" + clientSecret;

    curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, formdata.c_str());
    
    // send it!
    curl_easy_setopt(curl_handle, CURLOPT_URL, "https://accounts.spotify.com/api/token");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&data);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    res = curl_easy_perform(curl_handle);

    json authdata = json::parse(result());

    // error happened, terminate
    if (authdata.contains("error")) {
      cout << "Failed to fetch Spotify token: " << authdata["error_description"] << endl;
      return;
    }

    access_token = authdata["access_token"];
    cout << "Access Token: " << access_token << "\n" << endl;

    refresh_token = authdata["refresh_token"];
    cout << "Refresh Token: " << refresh_token << "\n" << endl;

    curl_easy_cleanup(curl_handle);
  }
  // access token available
  else access_token = code;
}

// Cleans up the request class upon deletion.
SpotifyWebRequest::~SpotifyWebRequest() {
    /* we are done with libcurl, so clean everything up */
    curl_slist_free_all(headerList);
    curl_global_cleanup();
}

/*
  Begins retrieval of the data from the stored url.
  returns a boolean for whether the retrieval was successful or not.
*/
bool SpotifyWebRequest::execute(string url, int type = 0) {
  if (access_token.empty()) {
    cout << "No Spotify OAuth2 token specified!" << endl;
    return false;
  }

  //cout << "Requesting " << url << endl;

  // if there is data, free previously stored memory and malloc again
  if (data.size > 0) free(data.memory);
  data.memory = (char*)malloc(1);
  data.size = 0;

  // initialize
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();

  // set headers
  string authuri = "Authorization: Bearer " + access_token;
  headerList = NULL;
  headerList = curl_slist_append(headerList, "Accept: application/json");
  headerList = curl_slist_append(headerList, "Content-Type: application/json");
  headerList = curl_slist_append(headerList, authuri.c_str());
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headerList);

  // GET
  if (type == req_GET) curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1L);
  // POST
  else if (type == req_POST) {
    char *post = "";
    curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, post);
  }
  // PUT
  else if (type == req_PUT) curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "PUT");

  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&data);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  res = curl_easy_perform(curl_handle);

  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    return false;
  }
  else {
    //cout << "Successfully fetched " << url << endl;
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    return true;
  }
}

/*
  Returns the result of the data after running execute() (or not).
  If there is no data, it will return an error message.
  Otherwise, returns the string of the data.
*/
string SpotifyWebRequest::result() {
  if (data.size == 0) return "No data found, or request failed!";
  else return data.memory;
}

// Return the access token after authenticating
string SpotifyWebRequest::getAccessToken() {
  return access_token;
}