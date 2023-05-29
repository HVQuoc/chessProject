

all: compile link

compile:
	g++ -I"C:\SFML-2.5.1\include" -c *.cpp

link:
	g++ -LC:\SFML-2.5.1\lib *.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  -lsfml-main

clean:
	del *.o