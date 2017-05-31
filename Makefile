prog: main.cpp
	g++ -o openGL main.cpp -Wall -lGLEW -lglfw -lGL
run:
	DRI_PRIME=1 ./openGL
