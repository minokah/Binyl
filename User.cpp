/**
    @brief Holds user data (only username). This file implements the User class, which stores basic user data. 
    @author Brandon Luu
*/

#include <string>
using namespace std;

#include "User.h"

// Default Constructor
User::User() {}

// Constructor
User::User(string who) {
    username = who;
}

// Get the username
string User::getUsername() {
    return username;
}
