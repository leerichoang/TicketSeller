#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "Ticket.h"
#include "Seats.h"

#define NUMSELLER 500

using namespace std;

void *buyTicket(void * nullVarible);

int server;
const int bufsize = 1024;
char buffer[bufsize];
char input[bufsize];

Seats e;
int buyerNum = 0;

int main() {

	// Server Variables
	int client;
	int portNum=1500;	//any port from 1000 to 6535 has no specific assigned service

	struct sockaddr_in server_addr;
	socklen_t size;

	//Thread Variables
	pthread_t thread[NUMSELLER];

	//Create Socket
	client = socket(AF_INET, SOCK_STREAM,0);
	if(client <0){
		cout<<"Error: Cannot Establish Socket"<<endl;
		exit(1);
	}
	else {
		cout<<"***Socket Server Established***"<<endl;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr= htons(INADDR_ANY);
	server_addr.sin_port = htons(portNum);

	// Bind Socket
	if((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr)))<0) {
		cout<<"Error: Binding Connect Failed"<<endl;
		exit(1);
	}
	else {
		cout<<"***Server Binded***\n***Now Listening for clients***"<<endl;
	}

	// Listen
	listen(client, 3);
	int numThread = 0;
	while (numThread < NUMSELLER){
		cout<<"   Server Listening # "<< numThread <<endl;
		size = sizeof(server_addr);
		server = accept(client,(struct sockaddr*)&server_addr, &size);
		if (server <0){
			cout<<"Error Accepting Failed"<<endl;
		}
		else {
			cout<<"Client Accepted "<<numThread<< endl;
		}
		strcpy(buffer, "Connected");
	    send(server, buffer, bufsize, 0);
		pthread_create(&thread[numThread], NULL, buyTicket, NULL);
		numThread++;
		buyerNum++;
	}
	for(int i=0; i <numThread; i++){
		pthread_join(thread[i], NULL);
	}
}

void *buyTicket(void * nullVarible) {
	int currBuyer = buyerNum;
	bool isExit = false;
	int seatNum = -1;		// -1 if seat not currently purchased
	while (!isExit) {
		// get user choice
		cout << "Input: " << input << endl;
		e.printBuy();
		recv(server, input, bufsize, 0);
		// buy ticket
		if (input[0] == 'B'||input[0] == 'b') {
			recv(server, input, bufsize, 0);
			int seat = atoi(input);
			if (seat > -1 && seat < 500)
				seatNum = seat;
			if (e.isOpen(seatNum)) {
				e.assignSeat(currBuyer, seatNum);
				strncpy(input, "1", 1);
				cout << "Seat #" << seatNum << " bought by Buyer #" << currBuyer << endl;
			}
			else {
				cout << "Buyer #" << currBuyer << " tried to buy a seat" << endl;
				strncpy(input, "0", 1);
			}
			send(server, input, bufsize, 0);
		}
		// return ticket
		else if (input[0] == 'R'||input[0]=='r') {
			// check if ticket is bought
			if (seatNum != -1) {
				e.returnSeat(seatNum);
				strncpy(input, "1", 1);
				cout << "Seat " << seatNum << " returned by buyer #" << currBuyer << endl;
				seatNum = -1;
			}
			else {
				cout << "Buyer #" << currBuyer << " tried to return a ticket" << endl;
				strncpy(input, "0", 1);
			}
			send(server, input, bufsize, 0);
		}
		// client exits
		else if(input[0] == 'Q'||input[0]=='q'){
			isExit = true;
		}
		else {
			continue;
		}
	}
	close(server);
}
