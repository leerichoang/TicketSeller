#ifndef SEATS_H
#define SEATS_H

#include "Ticket.h"

const int R = 50;
const int C = 10;

class Seats {
public:
	Seats();
	bool seatsAvailable();		// return true if no more room
	Ticket * getID(int seatNumber);
	bool seatExists(int seatNumber);
	void assignSeat(int buyerID, int numSeats);
	void returnSeat(int numSeats);
	void printSeats();
	void printBuy();
	bool isOpen(int seatNum);
private:
	Ticket * seats[R][C];		// every seat has an ID, ex) seat 25 = row 3, col 5
	int emptySeats;
};

Seats::Seats() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			Ticket * a = new Ticket();
			seats[i][j] = a;
		}
	}
	emptySeats = R * C;
}

// return true if no more room
bool Seats::seatsAvailable() {
	if (emptySeats = 0) return false;
	return true;
}

// given seatnumber, return position in seat array
Ticket * Seats::getID(int seatNumber) {
	Ticket * seat;
	seatNumber -= 1;
	int sRow = seatNumber / C;
	int sCol = seatNumber % C;
	seat = seats[sRow][sCol];
	return seat;
};

bool Seats::seatExists(int seatNumber) {
	if (seatNumber > R * C - 1) return false;
	return true;
}

//makes the seats in chart
void Seats::assignSeat(int buyerID, int numSeats) {
	Ticket * current;
	current = getID(numSeats);
	//if(current->isAvaliable()){
	current->setBuyer(buyerID);
	emptySeats -= numSeats;
	//}
}

// given seat position, set seat to 0
void Seats::returnSeat(int numSeats) {
	Ticket * current;
	current = getID(numSeats);
	current->setBuyer(0);
	 emptySeats += numSeats;
}

// Print seats, bought seats are marked with X
void Seats::printSeats() {
	cout << "\nCOLUMN: |";
	int seatNumber = 1;
	for (int j = 0; j < C; j++) {
		cout << setw(4) << j + 1 << setw(3) << '|';
	}
	cout << '\n';
	for (int i = 0; i < R; i++) {
		cout << "ROW # " << setw(3) << i + 1 << ':';
		for (int j = 0; j < C; j++) {
			cout << '[';

			if (seats[i][j]->getBuyer() > 0) cout << "XXXX";
			else cout << setw(4) << seatNumber;
			cout << "] ";

			seatNumber++;
		}
		cout << '\n';
	}
}

// Print seat, bought seats show buyerID
void Seats::printBuy() {
	cout << "\nCOLUMN: |";
	int seatNumber = 1;
	for (int j = 0; j < C; j++) {
		cout << setw(4) << j + 1 << setw(3) << '|';
	}
	cout << '\n';
	for (int i = 0; i < R; i++) {
		cout << "ROW # " << setw(3) << i + 1 << ':';
		for (int j = 0; j < C; j++) {
			cout << '[';
			if (seats[i][j]->getBuyer() > 0) cout << setw(4) << seats[i][j]->getBuyer();
			else cout << "XXXX";
			cout << "] ";
			seatNumber++;
		}

		cout << '\n';
	}
}

bool Seats::isOpen(int seatNum){
    Ticket * temp = NULL;
    temp = getID(seatNum);
    return temp->isAvaliable();
}

#endif
