/**
 * @file Curl.cpp
 * @brief Generic CURL class to fetch data from a source. This file implements the Curl class for basic CURL functionality for fetching data from a URL.
 * @author Brandon Luu
*/

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <curl/curl.h>
#include <iostream>

using namespace std;

#include "Curl.h"

/*
  getinmemory.c's function for writing new data to the MemoryStruct
  Appears to return some size of the data
*/
size_t Curl::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
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
  Creates the request class and stores the url for later use.
*/
Curl::Curl(string u) {
  url = u;
}

/*
  Cleans up the request class upon deletion.
*/
Curl::~Curl() {
    /* we are done with libcurl, so clean it up */
    curl_global_cleanup();
}

/*
  Begins retrieval of the data from the stored url.
  returns a boolean for whether the retrieval was successful or not.
*/
bool Curl::execute() {
  CURL *curl_handle;
  CURLcode res;

  // Free loaded data, if any
  if (data.size > 0) free(data.memory);

  data.memory = (char*)malloc(1);
  data.size = 0;
  
  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&data);

  /* some servers do not like requests that are made without a user-agent
    field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
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
char* Curl::result() {
  return data.memory;
}

/*
  Return the size of the data retrieved in bytes.
*/
size_t Curl::size() {
  return data.size;
}