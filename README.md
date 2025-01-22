# Binyl

Vinyls digitized for Raspberry Pi.

### Authors
* Brandon Luu
* Armin Farhang-Pour
* Irfan Rahul Sharif
* Ryan Cook
* Endreas Yohannes

### Introduction
* This is a program written in C++ for the Raspberry Pi that is meant to emulate the functionality of vinyls (RFID cards) and a vinyl player (this program).
* The program uses Spotify's API to store and play songs, with URLs being loaded onto RFID cards.
* To play a song, tap the corresponding card onto an RFID module attached to a Raspberry Pi while running the program.

### Features
* Automatically queues up songs in a queue to be played using the Spotify API
* Can queue Spotify songs, playlists, and albums
* Tap a Binyl-specific card on an RFID reader to perform actions (such as queuing, skipping, etc.)
* Themed visual GUI which shows your current queue, album art, and more
* Display content on a physical 128x64 OLED graphic display (ssd1306)
* Users can add their own personalized data (like a chosen name) onto the card

### Full Feature Video
[![Binyl Demo Video](https://img.youtube.com/vi/3c5gfZomJ7E/0.jpg)](https://www.youtube.com/watch?v=3c5gfZomJ7E)

### Early Demo Video
From one month in development

https://github.com/minokah/Binyl/assets/42823200/8e2a0603-61f4-44c5-87d9-4bae3b013f99

## Usage

### Dependencies
* A valid Spotify Premium account
* Spotify Developer application
* A physical RC522 RFID reader module
* Programmable MIFARE Classic 1k (or equivalent) cards
* RFID-RC522 - A library for RFID support on Raspberry Pi [https://github.com/paulvha/rfid-rc522]
* BCM2835 - A library for Broadcom BCM 2835 chip support on Raspberry Pi [https://www.airspayce.com/mikem/bcm2835]
* SFML - Multimedia for C++ [https://www.sfml-dev.org]
* libssd1306 - A driver for OLED SSD1306 [https://github.com/stealthylabs/libssd1306]
* curl - For HTTP requests [https://curl.se]

### Building
* You **must** be using a Raspberry Pi to be able to use this program
* Install all of the above dependencies
* Within `SpotifyWebRequest.h`, enter your Spotify application's client ID and client secret in the correct variables
* Run the makefile by running `make`

### Running
To run this program, you must obtain a Spotify authorization code for a valid **Spotify Premium** account (yes, you must have a premium account).
* Visit the site below and login to obtain a new code.
```
https://accounts.spotify.com/authorize?response_type=code&scope=user-read-playback-state user-modify-playback-state&client_id=8692d0967e7d4bd4bf898c2c98b9e64b&redirect_uri=https://www.blank.org
```
* You will be redirected to a blank website with the URL being something like:
    * `https://blank.org/?code=...`
* Copy the `code` value within the URL and run the program using:
    * `sudo ./Binyl [code]` with a fresh token
    * `sudo ./Binyl [access token] 1` if you've already authorized and are using an access token
* Yes, you must give it `sudo` privileges
* Binyl will authenticate your original token with the Spotify API and provide an access token for future requests, valid for one (1) hour. This will be in the console.

### Creating Cards
To create Binyl cards, use an RFID writer program (like the one listed above) and write to the following blocks:
```
Block 8: type
Block 9: first 16 bytes of the URL
Block 10: the next 6 bytes of the URL
Block 12: username
```

For example, given the Spotify URL (right click a song > Share > hold right click and click Copy Spotify URI) `spotify:track:72ahyckBJfTigJCFCviVN7`,
```
Block 8: track
Block 9: 72ahyckBJfTigJCF
Block 10: CviVN7
Block 12: Brandon
```

Available types/commands are: track, playlist, album, skipnext, toggleplay, shuffle, volume, queuemode, clearqueue
