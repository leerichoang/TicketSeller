/*
NOTE: 
	*	Using type long works better with the function pthread, so you won't get casting warnings
	* 	Possible Error Case: at ticket Sold==1000, 1000%20==0 that means the loop 
	-	will keep going until buyer==0 and at buyer equal to 0 there's still 1 ticket left
*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUMTICKETS 1000													
#define NUMSELLER 3
#define NAMELEN 16
using namespace std;
long ticketNum =NUMTICKETS;													// number of ticket =1000
long ticketCounter=0;
long threadCount=0;
char thread_name[NAMELEN];													// char array for thread name
pthread_mutex_t mut;														// our lock
//function prototype
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
		
		if (i==0) {pthread_setname_np(thread[i], "Seller 1");}				// setting name to thread [1] == Seller 1
		else if (i==1) {pthread_setname_np(thread[i], "Seller 2");}			// setting name to thread [2] == Seller 2
		else if (i==2) {pthread_setname_np(thread[i], "Seller 3");}			// setting name to thread [3] == Seller 3
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
	threadCount++;
	
	while (buyerRR >0&&ticketNum>0){										// checking if there are ticket left or buyer left 
		pthread_getname_np(pthread_self(), thread_name, NAMELEN);			// getting name of current thread(Seller #) 
		//pthread_mutex_lock(&mut);											// locking the thread
		randBuy = randNumTicket();											// Random number of ticket to for buyer 
		usleep(200000); 														// simulating grabbing for 2mins, but im setting it to 0.2second 
																			// usleep(microseconds) 1*10^6 microsecond = 1 second 20000microsecond = 0.02second
		if (ticketNum - randBuy>=0){ 										// check if there are ticket left 
			ticketNum = ticketNum - randBuy;								// sell
			ticketCounter+=randBuy;											// counter for how many sold
			cout<<thread_name<<" ";											// Seller #
			cout <<"sell "<< randBuy <<" Ticket REMAIN " <<ticketNum<< " Ticket SOLD "<< ticketCounter<<" Buyer # " << buyerRR <<endl;
		}
		if (ticketCounter>0&&ticketCounter%20==0){							// checking for counter is not 0 and for every 20 tickets
			ticketNum++;													// return 1 ticket for every 20 sold
			ticketCounter --;												// minus 1 ticket from the sold counter
			cout<<thread_name<<" ";											// Seller #
			cout<<"return back 1 ticket"<<endl;
		}
		//pthread_mutex_unlock(&mut);											// unlocking the thread
		buyerRR--;															// minus 1 buyer after every transaction 
	}
}


