/*
NOTE: using type works better with the function pthread, so you won't get casting warnings
*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#define NUMTICKETS 1000
#define NUMSELLER 3
using namespace std;
long ticketNum =NUMTICKETS;													// number of ticket =1000
pthread_mutex_t mut;														// our lock
void *buyTicket(void *);													// void * function prototype
long randNumTicket();														// rand function prototype


int main() {
	
	long ranTicket =0;													
	long buyer =1000; 														// 1000 buyer
	pthread_t thread[NUMSELLER];
	
	for (int i =0; i<NUMSELLER; i++) {
		ranTicket=randNumTicket();
		cout<<"thread "<< i << " "<<endl;			
		pthread_create(&thread[i], NULL, buyTicket, (void *) buyer);		// creating 3 threads, passing in the buyTicket function, and void * buyer( number of buyer)
	}
	for (int i =0; i<NUMSELLER; i++) {										// joining the threads( Basically trash collector **I THINK* NOT TOO SURE)
		pthread_join(thread[i], NULL);
	}
	
	cout<<"tickNum "<<ticketNum<<endl;										// test to make sure 0 ticket left
	
	cout<<"done"<<endl;
	return 0;
	
}

long randNumTicket(){														// generate random #ticket to buy
	return rand() % 3 + 1;													// rand() % max + min 
}
void *buyTicket(void * buyeR){
	long buyerRR =  (long) buyeR;											// long cast void * buyeR to long
	long randBuy;															// Random number of ticket to for buyer 
	while (buyerRR >0||ticketNum>0){										// checking if there are ticket left or buyer left 
		
		pthread_mutex_lock(&mut);											// locking the thread
		randBuy = randNumTicket();											// Random number of ticket to for buyer 
		if (ticketNum - randBuy>=0){ 										// check if there are ticket left 
			ticketNum = ticketNum - randBuy;								// sell
			cout <<"sell "<< randBuy <<" "<<ticketNum<<endl;
		}
		pthread_mutex_unlock(&mut);											// unlocking the thread
		buyerRR--;															// minus 1 buyer after every transaction 
	}
}


