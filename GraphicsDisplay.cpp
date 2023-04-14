/**
    @brief Display text on the physical graphics display. This file implements the GraphicsDisplay class for displaying text on a physical graphics display.
    @author Ryan Cook
    @author Brandon Luu
*/

#include <iostream>
#include <unistd.h>
#include "GraphicsDisplay.h"

using namespace std;

// Constructor.
GraphicsDisplay::GraphicsDisplay() {}

// Destructor.
GraphicsDisplay::~GraphicsDisplay() {}

// Display text on the screen
void GraphicsDisplay::display(string text) {
    // Fork and run the shell script with our text
    pid_t screenFork = fork();
    if (screenFork == 0) {
        cout << "[GraphicsDisplay] Displaying \"" << text << "\"" << endl;
        string command = "./libssd1306/examples/test_i2c_128x32 \"" + text + "\"";
        system(command.c_str());
    }
}

// Clear the screen
void GraphicsDisplay::clear() {
    // Display nothing
    display("");
}