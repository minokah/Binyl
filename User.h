#ifndef USER_H
#define USER_H

#include <string>

/**
    @brief Holds user data (only username). This header provides the User class, which stores basic user data. 
    @author Brandon Luu
*/
class User {
    private:
        /**
         * @brief The username of the user.
         */
        std::string username;
        
    public:
        /**
         * @brief A default constructor for User. 
         */
        User();

        /**
         * @brief A constructor for User.
         * @param who The username of the user.
         */
        User(std::string who);

        /**
         * @brief Method to get the user's username.
         * @return The user's username. 
         */
        std::string getUsername();
};

#endif
