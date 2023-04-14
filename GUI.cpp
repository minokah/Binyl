/**
 * @brief Visual GUI built using SFML. This file implements provides a SFML GUI class, which displays info about the player.
 * @author Armin Farhang-Pour
 * @author Brandon Luu
 */

#include "GUI.h"
using namespace std;
    
GUI::GUI (int width, int height, const std::string& title, const std::string& style): 
    black(0, 0, 0), 
    offwhite(212, 212, 212), 
    greywhite(120, 120, 120),
    songtext("", monstFontItal, 50),
    artisttext("", chakBold, 30),
    albumtext("", monstFontReg, 20),
    next1text("", ChakReg, 30),
    next1usertext("", ChakReg, 30),
    next2text("", ChakReg, 30),
    next2usertext("", ChakReg, 30),
    next3text("", ChakReg, 30),
    next3usertext("", ChakReg, 30),
    next4text("", ChakReg, 30),
    next4usertext("", ChakReg, 30),
    queuesizetext("", monstFontReg, 20),
    cardtitle("", ChakReg, 35),
    cardsubtitle("", ChakReg, 25)

    {
        
        //setting resolution and window type ----------------------------
        if (style =="F" || style == "f"){ //if style = "f" then GUI is fullscreen
            window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
        }
        else{  //else GUI is windowed
            window.create(sf::VideoMode::getDesktopMode(), title);
        }


        //loading textures with error checking ---------------------------
        if (!bckgrnd.loadFromFile("assets/images/gradient-background.png")){
            std::cerr << "Failed to load background image!" << std::endl;
            
        }
        if (!pause_bckgrnd.loadFromFile("assets/images/pause-background.png")){
            std::cerr << "Failed to load pause background image!" << std::endl;
            
        }
        if (!cover.loadFromFile("assets/images/cover.png")){
            std::cerr << "Failed to load default cover image!" << std::endl;
            
            
        }
        if (!next.loadFromFile("assets/images/next.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!prev.loadFromFile("assets/images/prev.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!pause.loadFromFile("assets/images/pause.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!play.loadFromFile("assets/images/play.png")){
            std::cerr << "Failed to load cover album image!" << std::endl;
            
        }
        if (!queue.loadFromFile("assets/images/queue.png")){
            std::cerr << "Failed to load assets/images/queue.png" << std::endl;
            
        }
        if (!quecard.loadFromFile("assets/images/singlecard.png")){
            std::cerr << "Failed to load assets/images/singlecard.png" << std::endl;
            
        }

        //setting sprites -----------------------------------------
        bckgrndsprite.setTexture(bckgrnd);
        pause_bckgrndsprite.setTexture(pause_bckgrnd);
        coversprite.setTexture(cover);
        nextsprite.setTexture(next);
        prevsprite.setTexture(prev);
        pausesprite.setTexture(pause);
        playsprite.setTexture(play);
        queuesprite.setTexture(queue);
        quecardsprite.setTexture(quecard);
        

        //setting opacity of next, play. pause, prev ---------------
        opacitynone = nextsprite.getColor();
        opacityfull = opacitynone;
        opacitynone.a = 0;
        opacityfull.a = 255;

        nextsprite.setColor(opacitynone);
        prevsprite.setColor(opacitynone);
        playsprite.setColor(opacitynone);
        pausesprite.setColor(opacitynone);
        queuesprite.setColor(opacitynone);
        quecardsprite.setColor(opacitynone);
        
        // setting the position of control logos -------------------
        nextsprite.setPosition(1618, 181);
        prevsprite.setPosition(1618, 181);
        playsprite.setPosition(1038, 89);
        pausesprite.setPosition(1038, 101);
        queuesprite.setPosition(1587, 980);
        quecardsprite.setPosition(1584, 665);
        
        //fitting backgrounds to full scale ------------------------
        bckgrndsprite.setScale(
            float(window.getSize().x) / bckgrndsprite.getLocalBounds().width,
            float(window.getSize().y) / bckgrndsprite.getLocalBounds().height
        );
        pause_bckgrndsprite.setScale(
            float(window.getSize().x) / pause_bckgrndsprite.getLocalBounds().width,
            float(window.getSize().y) / pause_bckgrndsprite.getLocalBounds().height
        );

        // loading fonts ---------------------------------
        if (!ChakReg.loadFromFile("assets/fonts/ChakraPetch/ChakraPetch-Regular.ttf") ||
                !chakBold.loadFromFile("assets/fonts/ChakraPetch/ChakraPetch-SemiBoldItalic.ttf") ||
                !monstFontItal.loadFromFile("assets/fonts/Montserrat/Montserrat-Italic.ttf") ||
                !monstFontReg.loadFromFile("assets/fonts/Montserrat/Montserrat-Regular.ttf")            
                ){ // load font files
            std::cerr << "Failed to load font file!" << std::endl;
            
        }

        // configuring text---------------------------------------
        songtext.setPosition(1043, 183);
        artisttext.setPosition(1045, 265);
        albumtext.setPosition(1048, 309);
        
        next1text.setPosition(1057, 452);
        next1usertext.setPosition(1591, 452);
        next1text.setFillColor(offwhite);
        next1usertext.setFillColor(greywhite);
    
        next2text.setPosition(1057, 506);
        next2usertext.setPosition(1538, 506);
        next2text.setFillColor(offwhite);
        next2usertext.setFillColor(greywhite);

        next3text.setPosition(1057, 560);
        next3usertext.setPosition(1478, 560);
        next3text.setFillColor(offwhite);
        next3usertext.setFillColor(greywhite);

        next4text.setPosition(1057, 615);
        next4usertext.setPosition(1428, 615);
        next4text.setFillColor(offwhite);
        next4usertext.setFillColor(greywhite);

        queuesizetext.setPosition(1057, 670);
        queuesizetext.setFillColor(offwhite);

        cardtitle.setOrigin(cardtitle.getLocalBounds().width / 2, cardtitle.getLocalBounds().height / 2);
        cardtitle.setPosition(1735, 974);
        cardtitle.setFillColor(opacitynone);

        cardsubtitle.setOrigin(cardsubtitle.getLocalBounds().width / 2, cardsubtitle.getLocalBounds().height / 2);
        cardsubtitle.setPosition(1735, 1020);
        cardsubtitle.setFillColor(opacitynone);
        
        
    }

// Reset the GUI to be empty on everything
void GUI::setEmpty() {
    coversprite.setScale(1, 1);
    setNext("", "", "", 1);
    setNext("", "", "", 2);
    setNext("", "", "", 3);
    setNext("", "", "", 4);
    songtext.setString("Welcome to Binyl!");
    artisttext.setString("Tap a Binyl card to start queuing!");
    albumtext.setString("");
}


std::string GUI::truncString(std::string string, int numchar){
    if (string.size()>numchar){
        std::string truncated_str = string.substr(0, numchar);
        return truncated_str + "...";
    }
    else {
        return string;
    }
    
}

void GUI::setCurrentSong(std::string newartist, std::string newsong, std::string newalbum, std::string coverlink) {
    Curl coverdl(coverlink);
    coverdl.execute();

    cover.loadFromMemory(coverdl.result(), coverdl.size());
    coversprite.setTexture(cover);
    coversprite.setScale(sf::Vector2f((float)(685.0f / cover.getSize().x), (float)(685.0f / cover.getSize().y)));

    songtext.setString(truncString(newsong, 23));
    artisttext.setString(newartist);
    albumtext.setString(newalbum);

}

void GUI::setCurrentSong(Song newsong) {
    Curl coverdl(newsong.getCoverArt());
    coverdl.execute();
    cover.loadFromMemory((void*)coverdl.result(), coverdl.size());
    coversprite.setTexture(cover);
    coversprite.setScale((float)685/640, (float)685/640);
    
    songtext.setString(truncString(newsong.getName(), 23));
    artisttext.setString(newsong.getArtist());
    albumtext.setString(newsong.getAlbum());
}

void GUI::setNextFour(vector<Song> next4, int queuesize) {
    // Reset everything first
    setNext("", "", "", 1);
    setNext("", "", "", 2);
    setNext("", "", "", 3);
    setNext("", "", "", 4);
    queuesizetext.setString(to_string(queuesize) + " songs left...");

    if (!next4.empty()){
        int amt = next4.size();
        if (amt >= 4) amt = 4;
        for (int i =0; i != amt; i++){
            // setNext(next4[i], i+1);
            setNext(next4[i].getArtist(), next4[i].getName(), next4[i].getUser().getUsername(), i+1);
        }
    }
}



void GUI::setNext(std::string newartist, std::string newsong, std::string username, int numnext){
    std::string printstring ="";
    printstring = newartist + " - " + newsong;
    
    if (numnext == 1){
        next1text.setString((truncString(printstring, 36)));
        next1usertext.setString(username);
        sf::FloatRect textBounds = next1usertext.getLocalBounds();
        next1usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next1usertext.setPosition(1715, 452);
    }
    else if (numnext == 2){
        next2text.setString((truncString(printstring, 36)));
        next2usertext.setString(username);     
        sf::FloatRect textBounds = next2usertext.getLocalBounds();
        next2usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next2usertext.setPosition(1715, 506);      
    }
    else if (numnext == 3){
        next3text.setString((truncString(printstring, 36)));
        next3usertext.setString(username);
        sf::FloatRect textBounds = next3usertext.getLocalBounds();
        next3usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next3usertext.setPosition(1715, 560);
        
    }
    else if (numnext == 4){
        next4text.setString((truncString(printstring, 36)));
        next4usertext.setString(username);
        sf::FloatRect textBounds = next4usertext.getLocalBounds();
        next4usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next4usertext.setPosition(1715, 615);
        
    }
    else {
        std::cerr << "Wrong number specified for upnext!" << std::endl;
        return;
    }

}


void GUI::setNext(Song song, int numnext){
    std::string newartist = song.getArtist();
    std::string newsong = song.getName();
    string username = song.getUser().getUsername();
    //std::string type = song.getType();

    std::string printstring ="";
    printstring = newartist + " - " + newsong;

    if (numnext == 1){
        next1text.setString((truncString(printstring, 36)));
        next1usertext.setString(username);
        sf::FloatRect textBounds = next1usertext.getLocalBounds();
        next1usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next1usertext.setPosition(1715, 452);
    }
    else if (numnext == 2){
        next2text.setString((truncString(printstring, 36)));
        next2usertext.setString(username);     
        sf::FloatRect textBounds = next2usertext.getLocalBounds();
        next2usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next2usertext.setPosition(1715, 506);
    }
    else if (numnext == 3){
        next3text.setString((truncString(printstring, 36)));
        next3usertext.setString(username);
        sf::FloatRect textBounds = next3usertext.getLocalBounds();
        next3usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next3usertext.setPosition(1715, 560);
    }
    else if (numnext == 4){
        next4text.setString((truncString(printstring, 36)));
        next4usertext.setString(username);
        sf::FloatRect textBounds = next4usertext.getLocalBounds();
        next4usertext.setOrigin(textBounds.left + textBounds.width, 0);
        next4usertext.setPosition(1715, 615); 
    }
    else {
        std::cerr << "Wrong number specified for upnext!" << std::endl;
        return;
    }

}

void GUI::changeElement(sf::Sprite& background, sf::Texture& texture, const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load background file: " << filename << std::endl;
        return;
    }
    background.setTexture(texture);
}


void GUI::setPauseScreen(){
    bckgrndsprite.setTexture(pause_bckgrnd);
    pausesprite.setColor(opacityfull);
    if (vistimer.getElapsedTime().asSeconds() > 3) {
        pausesprite.setColor(opacitynone);
        vistimer.restart();
        pausecounter = 2;
    }  
}

void GUI::setPlayScreen(){
    bckgrndsprite.setTexture(bckgrnd);
    playsprite.setColor(opacityfull);
    if (vistimer.getElapsedTime().asSeconds() > 3) {
        playsprite.setColor(opacitynone);
        vistimer.restart();
        resumecounter = 2;
    }  
}

void GUI::flashNextLogo(){
    if (nextcounter == 0){
        nexttimer.restart();
        nextsprite.setColor(opacityfull);
        nextcounter = 2;
    }
    else{
        if (nexttimer.getElapsedTime().asSeconds() > 2) {
            nextsprite.setColor(opacitynone);
            nextcounter = 0;
        }
    }
}

void GUI::flashPrevLogo(){
    if (prevcounter == 0){
        prevtimer.restart();
        prevsprite.setColor(opacityfull);
        prevcounter = 2;
    }
    else{
        if (prevtimer.getElapsedTime().asSeconds() > 2) {
            prevsprite.setColor(opacitynone);
            prevcounter = 0;
        }
    }    
}

void GUI::setQueueScreen(){
    queuesprite.setColor(opacityfull);
}

void GUI::removeQueueScreen(){
    queuesprite.setColor(opacitynone);
}

void GUI::flashCard(Song song, std::string type){ // type detrnine what kind of card to flash (playlist, single, album)
    removeQueueScreen();

    Curl coverdl(song.getCoverArt());
    coverdl.execute();
    quecover.loadFromMemory((void*)coverdl.result(), coverdl.size());
    quecoversprite.setTexture(quecover);
    quecoversprite.setScale((float)250/640, (float)250/640);
    quecoversprite.setPosition(1610, 692);

    if (type == "s"||type == "single"){
        std::string artist=truncString(song.getArtist(), 12);
        std::string songname=truncString(song.getName(), 16);
        
        cardtitle.setString(artist);
        cardtitle.setOrigin(cardtitle.getLocalBounds().width / 2, cardtitle.getLocalBounds().height / 2);
        cardtitle.setFillColor(offwhite);

        cardsubtitle.setString(songname);
        cardsubtitle.setOrigin(cardsubtitle.getLocalBounds().width / 2, cardsubtitle.getLocalBounds().height / 2);
        cardsubtitle.setFillColor(offwhite);

        quecard.loadFromFile("assets/images/singlecard.png");
        quecardsprite.setTexture(quecard);
    }
    else if (type == "a"||type == "album"){
        
        std::string artist=truncString(song.getArtist(), 12);
        std::string album = truncString(song.getAlbum(), 16);
        
        cardtitle.setString(artist);
        cardtitle.setOrigin(cardtitle.getLocalBounds().width / 2, cardtitle.getLocalBounds().height / 2);
        cardtitle.setFillColor(offwhite);

        cardsubtitle.setString(album);
        cardsubtitle.setOrigin(cardsubtitle.getLocalBounds().width / 2, cardsubtitle.getLocalBounds().height / 2);
        cardsubtitle.setFillColor(offwhite);

        quecard.loadFromFile("assets/images/albumcard.png");
        quecardsprite.setTexture(quecard);

    }
    else if (type == "p"||type == "playlist"){
        
        std::string artist=truncString(song.getArtist(), 12);
        std::string playlist = truncString(song.getAlbum(), 16); //set playlist name
        
        cardtitle.setString(artist); 
        cardtitle.setOrigin(cardtitle.getLocalBounds().width / 2, cardtitle.getLocalBounds().height / 2);
        cardtitle.setFillColor(offwhite);

        cardsubtitle.setString(playlist);
        cardsubtitle.setOrigin(cardsubtitle.getLocalBounds().width / 2, cardsubtitle.getLocalBounds().height / 2);
        cardsubtitle.setFillColor(offwhite);
        
        quecard.loadFromFile("assets/images/playlistcard.png");
        quecardsprite.setTexture(quecard);

    }
    quecardtimer.restart();
    quecardsprite.setColor(opacityfull);
    quecoversprite.setColor(opacityfull);
    cardcounter = 2;
}




void GUI::runScreen(){

    //setting textures w/ error checking------------------------
    sf::Texture coverShadow, lPlant, lPlantDs, rPlant, line, upnextBars;
    if (
        !coverShadow.loadFromFile("assets/images/cover-shadow.png") ||
        !lPlant.loadFromFile("assets/images/left-plant.png") ||
        !lPlantDs.loadFromFile("assets/images/left-plant-ds.png") ||
        !rPlant.loadFromFile("assets/images/right-plant.png") ||
        !line.loadFromFile("assets/images/line.png") ||
        !upnextBars.loadFromFile("assets/images/upnextuniform.png"))
        // load image file
    {
        std::cerr << "Failed to load image assets!" << std::endl;
    }

    //setting sprites -------------------------------------
    sf::Sprite coversprite(cover);
    coversprite.setPosition(192, 101);

    sf::Sprite coverShadowsprite(coverShadow);
    coverShadowsprite.setPosition(192, 20);

    sf::Sprite lPlantsprite(lPlant);
    lPlantsprite.setPosition(0, 478);

    sf::Sprite lPlantDssprite(lPlantDs);
    lPlantDssprite.setPosition(0, 455);

    sf::Sprite rPlantsprite(rPlant);
    rPlantsprite.setPosition(442, 653);

    sf::Sprite linesprite(line);
    linesprite.setPosition(1053, 253);

    sf::Sprite upnextBarssprite(upnextBars);
    upnextBarssprite.setPosition(1038, 448);

    //setting static text positions ---------------------------------
    sf::Text nexttext("Up Next", ChakReg, 30);
    nexttext.setPosition(1053, 401);
    nexttext.setFillColor(black);


    //timer and function call counters for test case. enable when running test cases
    // int nextcallcounter = 0;
    // int prevcallcounter = 0;
    // int quecallcounter = 0;
    // sf::Clock timer;
    // timer.restart();

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (controls.isPause()){
            resumecounter =0;
            if (pausecounter == 2){

            }
            else if (pausesprite.getColor() == opacityfull){
                setPauseScreen();
            }
            
            else{
                vistimer.restart();
                setPauseScreen();
            } 
        }
        else{
            pausecounter = 0;
            if (resumecounter == 2){
            }
            else if (playsprite.getColor() == opacityfull){
                setPlayScreen();
            }
            
            else{
                vistimer.restart();
                setPlayScreen();
            }
        }

        if (controls.isQueueMode() && cardcounter == 0){
            setQueueScreen();
        }
        else{
            removeQueueScreen();
        }

        if (nextsprite.getColor() == opacityfull){
            flashNextLogo();
        }
        if (prevsprite.getColor() == opacityfull){
            flashPrevLogo();
        }

        if (cardcounter == 2){
            if (quecardtimer.getElapsedTime().asSeconds() > 4) {
            quecardsprite.setColor(opacitynone);
            quecoversprite.setColor(opacitynone);
            cardtitle.setFillColor(opacitynone);
            cardsubtitle.setFillColor(opacitynone);
            cardcounter = 0;
                if(controls.isQueueMode()){
                    setQueueScreen();
                }
                else{
                    removeQueueScreen();
                }
            
            }

        }




        // ------ test case for cards and queue -----
        // if (timer.getElapsedTime().asSeconds() > 1){
        //     if (quecallcounter == 0){
        //         User Armin("Armin");
        //         // Song song1(Armin, "6UNIv72gsSDnKlYpbOOpfl", "Closed", 170, "single", "plenka", "https://preview.redd.it/nf-hope-album-cover-art-i-recreated-the-album-cover-how-do-v0-pkj3zz4bqtja1.png?width=640&crop=smart&auto=webp&s=7c0f01480877d90630332a8626b0fe754ed970d8" );
        //         Song song1(Armin, "6UNIv72gsSDnKlYpbOOpfl", "", 170, "Dawn FM sdfghjkl", "Lana Del Reyy", "https://preview.redd.it/nf-hope-album-cover-art-i-recreated-the-album-cover-how-do-v0-pkj3zz4bqtja1.png?width=640&crop=smart&auto=webp&s=7c0f01480877d90630332a8626b0fe754ed970d8" );
        //         flashCard(song1, "a");
        //         quecallcounter++;
        //     }
                
        // }
        // if (timer.getElapsedTime().asSeconds() > 7){
        //     if (quecallcounter == 1){
        //         User Armin("Armin");
        //         Song song2(Armin, "6UNIv72gsSDnKlYpbOOpfl", "", 170, "Dawn FM sdfghjkl", "Lana Del Reyy", "https://preview.redd.it/nf-hope-album-cover-art-i-recreated-the-album-cover-how-do-v0-pkj3zz4bqtja1.png?width=640&crop=smart&auto=webp&s=7c0f01480877d90630332a8626b0fe754ed970d8" );
        //         flashCard(song2, "p");
        //         quecallcounter++;
                
        //     }
                
        // }
        // if (timer.getElapsedTime().asSeconds() > 9){
        //     if (quecallcounter == 2){
        //         User Armin("Armin");
        //         Song song3(Armin, "6UNIv72gsSDnKlYpbOOpfl", "Books of Evil", 170, "Dawn FM sdfghjkl", "Lana Del Reyy", "https://preview.redd.it/nf-hope-album-cover-art-i-recreated-the-album-cover-how-do-v0-pkj3zz4bqtja1.png?width=640&crop=smart&auto=webp&s=7c0f01480877d90630332a8626b0fe754ed970d8" );
        //         flashCard(song3, "s");
        //         quecallcounter++;
        //         flashNextLogo();
                
        //     }
                
        // }
        // if (timer.getElapsedTime().asSeconds() > 12){
        //     if (quecallcounter == 3){
        //         User Armin("Armin");
        //         Song song2(Armin, "6UNIv72gsSDnKlYpbOOpfl", "", 170, "Dawn FM", "The Weeknd", "https://m.media-amazon.com/images/W/IMAGERENDERING_521856-T1/images/I/91hqtzfY6BL._AC_SL1500_.jpg" );
        //         // Song song2(Armin, "6UNIv72gsSDnKlYpbOOpfl", "Closed", 170, "single", "Parcels", "https://m.media-amazon.com/images/W/IMAGERENDERING_521856-T1/images/I/91hqtzfY6BL._AC_SL1500_.jpg" );
        //         flashCard(song2, "a");
        //         quecallcounter++;
        //         flashPrevLogo();
        //     }
                
        // }
        /*
        //------------Test Case templates ----------------------
        if (timer.getElapsedTime().asSeconds() > 3){
            controls.setPause(true);
        }
        if (timer.getElapsedTime().asSeconds() > 12){
            controls.setPause(false);
        }
        
        if (timer.getElapsedTime().asSeconds() > 15){
            if (nextcallcounter == 0){
                flashNextLogo();
                nextcallcounter++;
            }
            
        }

        if (timer.getElapsedTime().asSeconds() > 20){
            if (prevcallcounter == 0){
                flashPrevLogo();
                prevcallcounter++;
            }
            
        }
        */
        

        

        window.clear();

        //drawing images --------------------------------
        window.draw(bckgrndsprite);
        window.draw(nextsprite);
        window.draw(prevsprite);
        window.draw(playsprite);
        window.draw(pausesprite);

        window.draw(coverShadowsprite);
        window.draw(coversprite);
        window.draw(lPlantDssprite);
        window.draw(lPlantsprite);
        window.draw(rPlantsprite);
        window.draw(linesprite);
        window.draw(upnextBarssprite);

        //drawing texts --------------------------------
        window.draw(artisttext);
        window.draw(albumtext);
        window.draw(songtext);
        window.draw(nexttext);
        window.draw(next1text);
        window.draw(next1usertext);
        window.draw(next2text);
        window.draw(next2usertext);
        window.draw(next3text);
        window.draw(next3usertext);
        window.draw(next4text);
        window.draw(next4usertext);
        window.draw(queuesizetext);
        
        //draw card elements ---------------------------
        window.draw(queuesprite);
        window.draw(quecardsprite);
        window.draw(quecoversprite);
        window.draw(cardtitle);
        window.draw(cardsubtitle);

        window.display();

    }
}