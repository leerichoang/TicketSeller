#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#define NUMTICKETS 500
#define NUMSELLER 3
using namespace std;

//long ticket = NUMTICKETS;
long ticketNum =NUMTICKETS;
pthread_mutex_t mut;
void *buyTicket(void *);
long randNumTicket();


int main() {
	long ranTicket =0;
	int counter =0;
	pthread_t thread[NUMSELLER];
	while(ticketNum>0){
		for (int i =0; i<NUMSELLER; i++) {
			ranTicket=randNumTicket();
			pthread_create(&thread[i], NULL, buyTicket, (void *) ranTicket);
		}
		for (int i =0; i<NUMSELLER; i++) {
			pthread_join(thread[i], NULL);
		}
	}
	cout<<"tickNum "<<ticketNum<<endl;
	cout<<"done"<<endl;
	return 0;
	
}

long randNumTicket(){		// generate random #ticket to buy
	return rand() % 3 + 1;	//rand() % max + min 
}
void *buyTicket(void * ranT){
	long randBuyTicket =  (long) ranT;
	//pthread_mutex_lock(&mut);
	
	if (ticketNum - randBuyTicket>=0){ // check if there are ticket left
		ticketNum = ticketNum - randBuyTicket;
		cout <<"sell "<< randBuyTicket <<" "<<ticketNum<<endl;
	}
	//pthread_mutex_unlock(&mut);
}


