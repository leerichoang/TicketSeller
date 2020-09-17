#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <iomanip>
#include <ctype.h>

using namespace std;

class Ticket {
public:
	Ticket() : buyerID(0) {};
	Ticket(int newBuyer);
	void setSeat(int);
	void setBuyer(int);
	bool isAvaliable();
	int getBuyer();
private:
	int buyerID;
};

Ticket::Ticket(int newBuyer) {
	buyerID = newBuyer;
}

void Ticket::setBuyer(int ticketBuyer) {
	buyerID = ticketBuyer;
}

bool Ticket::isAvaliable() {
	if (buyerID == 0) return true;
	return false;
}

int Ticket::getBuyer() {
	return buyerID;
}

#endif
