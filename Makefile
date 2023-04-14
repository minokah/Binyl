all:
	make Curl
	make SpotifyWebRequest
	make SpotifyService
	make User
	make Song
	make Controls
	make GUI
	make FeedbackSound
	make GraphicsDisplay
	make Queue
	make Binyl
	g++ -o Binyl Curl.o SpotifyWebRequest.o SpotifyService.o ./RFIDModule/*.c ./RFIDModule/*.cpp User.o Song.o Controls.o GUI.o FeedbackSound.o GraphicsDisplay.o Queue.o Binyl.o -Wno-write-strings -lcurl -lpthread -lbcm2835 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -std=c++11

build:
	g++ -o Binyl Curl.o SpotifyWebRequest.o SpotifyService.o ./RFIDModule/*.c ./RFIDModule/*.cpp User.o Song.o Controls.o GUI.o FeedbackSound.o GraphicsDisplay.o Queue.o Binyl.o -Wno-write-strings -lcurl -lpthread -lbcm2835 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -std=c++11

Curl: Curl.cpp Curl.h
	g++ -c Curl.cpp

SpotifyWebRequest: SpotifyWebRequest.o SpotifyWebRequest.cpp SpotifyWebRequest.h
	g++ -c SpotifyWebRequest.cpp -Wno-write-strings

SpotifyService: SpotifyService.o SpotifyService.cpp SpotifyService.h
	g++ -c SpotifyService.cpp -Wno-write-strings

User: User.cpp User.h
	g++ -c User.cpp User.h

Song: Song.cpp Song.h
	g++ -c Song.cpp

Controls: Controls.cpp Controls.h
	g++ -c Controls.cpp

GUI: GUI.cpp GUI.h
	g++ -c GUI.cpp

FeedbackSound: FeedbackSound.cpp FeedbackSound.h
	g++ -c FeedbackSound.cpp -std=c++11 -Wno-write-strings

GraphicsDisplay: GraphicsDisplay.cpp GraphicsDisplay.h
	g++ -c GraphicsDisplay.cpp

Queue: Queue.cpp Queue.h
	g++ -c Queue.cpp

Binyl: Binyl.cpp
	g++ -c Binyl.cpp -Wno-write-strings

clean:
	rm -f *.o
	rm -f *app
	rm ./RFIDModule/*.o

cleanall:
	rm Binyl
	rm -f *.o
	rm -f *app
	rm ./RFIDModule/*.o