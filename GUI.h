#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include "Curl.h"
#include "Controls.h"
#include "Song.h"
#include <vector>

/**
 * @brief Visual GUI built using SFML. This header provides a SFML GUI class, which displays info about the player.
 * @author Armin Farhang-Pour
 * @author Brandon Luu
 */
class GUI {
    private:
        /**
         * @brief A window instance.
        */
        sf::RenderWindow window;
        
        /**
         * @brief Textures for assets used in the GUI.
        */
        sf::Texture cover, bckgrnd, pause_bckgrnd, next, prev, pause, play, queue, quecard, quecover ;
        
        /**
         * @brief Sprites for assets used in the GUI.
        */
        sf:: Sprite coversprite, bckgrndsprite, pause_bckgrndsprite, nextsprite, prevsprite, pausesprite, playsprite, queuesprite, quecardsprite, quecoversprite;

        //defining fonts and colors---------------------------------
       
        /**
         * @brief Fonts used in our GUI. 
        */
        sf::Font ChakReg, chakBold, monstFontItal, monstFontReg;
       
        /**
         * @brief Color palette used in our GUI. 
        */
        sf::Color black, offwhite, greywhite, opacitynone, opacityfull;
        
        /**
         * @brief Text interfaces used in our GUI. 
        */
        sf::Text artisttext, albumtext, songtext,
        next1text, next2text, next3text, next4text,
        next1usertext, next2usertext, next3usertext, next4usertext, queuesizetext, cardtitle, cardsubtitle;


        /**
         * @brief A Controls instance for ensuring our GUI matches what the user requests. 
        */
        Controls& controls = Controls::getInstance();
        
        /**
         * @brief A Song instance representing the current playing song. 
        */
        Song currsong;

        /**
         * @brief Timer instances for the timing of events. 
        */
        sf::Clock vistimer, nexttimer, prevtimer, quecardtimer;


        /**
         * @brief Value to manage the display of a pause event.
        */
        int pausecounter = 0;
        
        /**
         * @brief Value to manage the display of a resume event.
        */
        int resumecounter = 0;
        
        /**
         * @brief Value to manage the display of skipping to the next song. 
        */
        int nextcounter = 0;
        
        /**
         * @brief Value to manage the display of going to the previous song. 
        */
        int prevcounter = 0;
        /**
         * @brief Value to manage the duration of tapped card displayed. 
        */
        int cardcounter = 0;

        std::string truncString(std::string string, int numchar);

        

    public:
        /**
         * @brief Constructor for the GUI class.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param title The title of the window.
         * @param style The style of the window, mainly fullscreen or window.
        */
        GUI (int width, int height, const std::string& title, const std::string& style);
        
        /**
         * @brief Method to set the window to empty (i.e. no song playing). 
        */
        void setEmpty();
        
        /**
         * @brief Method to set the current song given a Song object.
         * @param newsong The song to set as currently playing.
        */
        void setCurrentSong(Song newsong);
        
        /**
         * @brief Method to set the current song given a list of attributes for drawing.
         * @param newartist The artist of the new song. 
         * @param newsong The new song's title. 
         * @param newalbum The new song's associated album title. 
         * @param coverlink A link to the new song's cover art. 
        */
        void setCurrentSong(std::string newartist, std::string newsong, std::string newalbum, std::string coverlink);
        
        /**
         * @brief Method to set the next 4 upcoming songs to be played. 
         * @param next4 A containing the next 4 songs to be played.
         * @param queuesize The amount of songs remaining in the queue.
        */
        void setNextFour(std::vector<Song> next4, int queuesize);
        
        /**
         * Method to set the next upcoming song to be played given a list of attributes.  
         * @param newartist The artist of the next song. 
         * @param newsong The next song's title. 
         * @param username The user who queued this song. 
         * @param numnext The index number for the song.
        */
        void setNext(std::string newartist, std::string newsong, std::string username, int numnext);
        
        /**
         * Method to insert a song in the GUIs upcoming songs. 
         * @param song The song instance to insert.
         * @param numnext The index of the desired song.
        */
        void setNext(Song song, int numnext); 
        
        /**
         * Method to change an element in the GUI 
         * @param background A pointer to the background of the GUI. 
         * @param texture A pointer to the current texture.
         * @param filename A file linking to the texture image.
        */
        void changeElement(sf::Sprite& background, sf::Texture& texture, const std::string& filename);
        
        /**
         * @brief Method to set the screen to paused. 
        */
        void setPauseScreen();

        /**
         * @brief Method to set the screen to playing. 
        */
        void setPlayScreen();

        /**
         * @brief Method to flash the next button. 
        */
        void flashNextLogo();

        /**
         * @brief Method to flash the previous button. 
        */
        void flashPrevLogo();

        /**
         * @brief Method to initialize and run the screen. 
        */
        void runScreen();

        /**
         * @brief Method to display the "queue mode" state.
        */
        void setQueueScreen();

        /**
         * @brief Method to hide the "queue mode" state.
        */
        void removeQueueScreen();

        /**
         * @brief Method to show the card that was tapped.
         * @param song The song object.
         * @param type The type of card (track, album, playlist)
        */
        void flashCard(Song song, std::string type);

        
        




};

#endif // CONTROLS_H
