
windows: windows.c socketAB.h 
	g++ -c windows.c -lws2_32 -I./ 

linux: linux.c socketAB.h 
	gcc -c linux.c -I./
