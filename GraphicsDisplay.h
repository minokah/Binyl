#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>

/**
    @brief Display text on the physical graphics display. This header provides a GraphicsDisplay class for displaying text on a physical graphics display.
    @author Ryan Cook
    @author Brandon Luu
*/
class GraphicsDisplay {
    public:
        /**
         * @brief Constructor for the GraphicsDisplay
         * 
         */
        GraphicsDisplay();

        /**
         * @brief Destructor for the GraphicsDisplay
         * 
         */
        ~GraphicsDisplay();

        /**
         * @brief Display some text on the screen
         * @param The text to display
         */
        void display(std::string text);

        /**
         * @brief Clear the screen
         * 
         */
        void clear();
};

#endif