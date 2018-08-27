#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main() {
	// Client Variables
	int client;
	int portNum =1500;
	int bufsize =1024;
	char buffer[bufsize];
	char input[bufsize];
//	char* ip="127.0.0.1";
	bool isExit=false;
	struct sockaddr_in server_addr;

	//Create Socket
	client = socket(AF_INET, SOCK_STREAM, 0);
	if(client < 0){
		cout<<"Error: Cannot Establish Socket"<<endl;
		exit(1);
	}
	else {
		cout<<"***Socket Server Established***"<<endl;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);

	//Connect the socket
	if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
		cout<<"Server & Client Connected"<<endl;
	}
	cout<<"Waiting for confirmation from server"<<endl;
	recv(client, buffer, bufsize, 0);
	cout << buffer << endl;

	char option;
	while (!isExit) {
		cout << "\n B) Buy a seat";
		cout << "\n R) Return a Seat";
		cout << "\n Q) Quit";
		cout << "\n>";
		cin >> input;
		send(client, input, bufsize, 0);

		if (input[0] == 'B'||input[0] == 'b') {
			cout << "Enter seat number (1-500): ";
			cin >> input;
			send(client, input, bufsize, 0);
			// check if seat is taken
			recv(client, input, bufsize, 0);
			if (input[0] == '1')
				cout << "Seat sucessfully bought" << endl;
			else
				cout << "Seat not available" << endl;
		}
		else if (input[0] == 'R'||input[0]=='r') {
			recv(client, input, bufsize, 0);
			if (input[0] == '1')
				cout << "Seat sucessfully returned" << endl;
			else
				cout << "No seats bought" << endl;
		}
		else if(input[0] == 'Q'||input[0]=='q'){
			isExit = true;
		}
		else {
			cout << "Input Invalid: Try again" << endl;
		}
	}
	close(client);
}
