#include <iostream>

/**
 * @brief Library to interface with the RFID Module. This header provides the RFIDModule class for interfacing with the RFID receiver.
 * @author Brandon Luu
 
    A modified version of paulvha's RFIDModule code: https://github.com/paulvha/rfid-rc522

    Changes were made to make reading the cards more convenient, such as
    converting the hex bytes into proper C++ style strings, as well as returning the specified block
    without having to input it through the terminal.
*/
class RFIDModule {
    private:
        /**
            @brief The constructor for the class.
        */
        RFIDModule();

        /**
            @brief The destructor for the class.
        */
        ~RFIDModule();
    public:
        /**
        * @brief Method to initialize and return a single RFIDModule instance.
        * @return Returns the RFIDModule instance.
        */
        static RFIDModule& getInstance();

        /**
            @brief Get the data stored within a MIFARE Classic block.
            @param block The block number.
            @return Returns the data as a decoded string.
        */
        std::string get(int block);
};