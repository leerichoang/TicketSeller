all: program1 program2
program1:
	g++ server.cpp -std=c++14 -pthread -o server.exe
program2:
	g++ client.cpp -std=c++14 -pthread -o client.exe
clean:
	rm *.exe
