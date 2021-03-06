// Project3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>

using namespace std;
// -- TIME CLASS -- //
class Time {
public:
	Time () {}

	int getYear () {
		return year;
	}
	int getMonth () {
		return month;
	}
	int getDay () {
		return day;
	}

	//Function to set the day of a Time object.
	void setDay (int D) { //Assuming days can only be 1-30
		if (D > 0 && D <= 30) {
			this->day = D;
		}
		else {
			cout << "Invalid value for Day." << endl;
		}
	}

	//Function to set the month of a Time object.
	void setMonth (int M) {
		if (M > 0 && M <= 12) {
			this->month = M;
		}
		else {
			cout << "Invalid value for Month." << endl;
		}
	}

	//Function to set the hour of a Time object.
	void setYear (int Y) {
		if (Y > 0 && Y <= 2050) {
			this->year = Y;
		}
		else {
			cout << "Invalid value for Year." << endl;
		}
	}

	//Funcion to compare <= of a Time
	bool operator<=(Time T) {
		if (this->year != T.year) {
			return (this->year < T.year);
		}
		else if (this->month != T.month) {
			return (this->month < T.month);
		}
		else if (this->day != T.day) {
			return (this->day < T.day);
		}
		else {
			return true;
		}
	}

	//Funcion to compare >= of a Time
	bool operator>=(Time T) {
		if (this->year != T.year) {
			return (this->year > T.year);
		}
		else if (this->month != T.month) {
			return (this->month > T.month);
		}
		else if (this->day != T.day) {
			return (this->day > T.day);
		}
		else {
			return true;
		}
	}

	//Funcion to compare == of a Time
	bool operator==(Time T) {
		return ((*this) <= T) && ((*this) >= T);
	}

	//Funcion to compare != of a Time
	bool operator!=(Time T) {
		return !((*this) == (T));
	}

	string print () {
		return to_string (year) + to_string (month) + to_string (day);
	}
private:
	int day;
	int month;
	int year;
};

//-- KEY CLASS --//
class Key {
public:
	//Setters
	void setOrigin (string s) {
		this->origin = s;
	}
	void setDestination (string s) {
		this->destination = s;
	}
	void setDepartureTime (int d, int m, int y) {
		this->departure.setDay (d);
		this->departure.setMonth (m);
		this->departure.setYear (y);
	}

	//Getters
	string getOrigin () {
		return origin;
	}
	string getDestination () {
		return destination;
	}
	Time getDeparture () {
		return departure;
	}

private:
	string origin;
	string destination;
	Time departure;
};

//-- VALUE CLASS --//
class Value {
public:
	//Setters
	void setFlightNumber (string s) {
		this->flightNumber = s;
	}
	void setFlightFare (string s) {
		this->flightFare = s;
	}

	//Getters
	string getFlightNumber () {
		return flightNumber;
	}
	string getFlightFare () {
		return flightFare;
	}

private:
	string flightNumber;
	string flightFare;
};

//-- ENTRY CLASS --//
class Entry {
public:
	Entry () {
		key = string ();
		value = string ();
		next = nullptr;
		prev = nullptr;
	}
	void setKey (string _k) {
		this->key = _k;
	}
	void setValue (string _v) {
		this->value = _v;
	}
	string getKey () {
		return key;
	}
	string getValue () {
		return value;
	}
	void print () {
		cout << "(" + key + "," + value + ")" << endl;
	}
	Entry* next;
	Entry* prev;
private:
	string key;
	string value;
};

//-- MAP CLASS --//
class Map {
public:
	Map () {
		int mSize = 0;
		last = new Entry;
		first = last;
	}

	int getSize () {
		return mapSize;
	}
	bool empty () {
		return (mapSize == 0);
	}
	Entry* begin () {
		return first;
	}
	Entry* end () {
		return last;
	}

	//Find - Find an item in the map based on key value, returns a pair.
	pair<Entry*, Entry*> find (string _k) {
		Entry* P;
		Entry* Q;
		Entry* N =  nullptr; //A dummy null Entry for return with the pair.

		for (P = this->begin (); P != this->end (); P = P->next) {
			//if a match if found
			if (P->getKey () == _k) {
				return make_pair(P, N);
			}
			//if a match isnt found, make a recommendation
			else {	
				Entry* earliestFlight = this->begin ();
				Entry* latestFlight = this->begin ();
				Entry* middleFlight = this->begin ();
				Time userTime = getTime(_k);

				//Find the earliest flight in the map.
				for (Q = this->begin (); Q != this->end (); Q = Q->next) {
					if (getTime (Q->getKey()) <= getTime (earliestFlight->getKey())) {
						earliestFlight = Q;
						cout << "early: " + earliestFlight->getValue();
					}
				}

				//Find the latest flight in the map.
				for (Q = this->begin (); Q != this->end (); Q = Q->next) {
					if (getTime (Q->getKey()) >= getTime (latestFlight->getKey())) {
						latestFlight = Q;
						cout << "late: " + latestFlight->getValue ();
					}
				}

				//Find the latest flight in the map.
				for (Q = this->begin (); Q != this->end (); Q = Q->next) {
					if (getTime (Q->getKey ()) != getTime (earliestFlight->getKey ()) &&
						getTime (Q->getKey ()) != getTime (latestFlight->getKey ())) {
							middleFlight = Q;
							cout << "middle: " + middleFlight->getValue ();
					}
				}

				//DETERMINE WHICH FLIGHT(S) TO RECOMMEND
				//flight < earliest flight
				if (userTime <= getTime (earliestFlight->getKey ())){
					cout << "No match found, here is a recommended flight..." << endl;
					return make_pair(earliestFlight, N);
				}
				//flight > latest flight
				else if (userTime >= getTime (latestFlight->getKey ())){
					cout << "No match found, here is a recommended flight..." << endl;
					return make_pair(latestFlight, N);
				}
				//flight < latest flight && flight > middle flight
				else if (userTime <= getTime (latestFlight->getKey ()) && userTime >= getTime (middleFlight->getKey ())) {
					cout << "No match found, here is a recommended flight..." << endl;
					return make_pair(middleFlight, latestFlight);
				}
				//flight > earliest flight && flight < middle flight
				else if (userTime >= getTime (earliestFlight->getKey ()) && userTime <= getTime (middleFlight->getKey ())) {
					cout << "No match found, here is a recommended flight..." << endl;
					return make_pair(earliestFlight, middleFlight);
				}
			}
		}
		return make_pair(this->end (), N);
	}

	//Put - add a new entry to the map with a key and value.
	Entry* put (string _k, string _v) {
		Entry* P;
		for (P = this->begin (); P != this->end (); P = P->next) {
			if (P->getKey () == _k) {//if found, them modify
				P->setValue (_v);
				return P;
			}
		}
		Entry* NewE = new Entry;
		NewE->setKey (_k);
		NewE->setValue (_v);
		P = this->InsertBack (NewE);
		this->mapSize++;
		return P;
	}

	//Print - print the contents of the map
	void print () {
		Entry* P;
		for (P = this->begin (); P != this->end (); P = P->next) {
			P->print();
		}
	}

	//Erase - erasw an entry from the map with the specified key.
	void erase (string _k) {
		if (!this->empty ()) {
			Entry* P;
			for (P = this->begin (); P != this->end (); P = P->next) {
				if (P->getKey () == _k) {
					this->Delete (P);
					this->mapSize--;
					cout << "Entry sucessfully deleted." << endl;
					return;
				}
			}
			cout << "Entry with specified key does not exist." << endl;
		}
		else {
			cout << "The map is empty." << endl;
		}
	}
private:
	int mapSize; //Size of the map
	Entry* first; //The first entry in the map
	Entry* last; //The last entry in the map
	
	//Insert - Inserts a node in to the map
	Entry* InsertBack (Entry* E) {
		//Check if map is empty
		Entry* NewEntry = E;
		if (this->empty ()) {//if map is empty
			//Set references for first and last to new entry
			first = NewEntry;
			NewEntry->next = last;
			last->prev = NewEntry;
		}
		//if not enpty then insert at the back, set references
		else {
			last->prev->next = NewEntry;
			NewEntry->prev = last->prev;

			NewEntry->next = last;
			last->prev = NewEntry;
		}
		return NewEntry;
	}
	
	//Delete - deletes a node from the map
	void Delete (Entry* E) {
		//case 1: is entry to be deleted is first in the map
		if (E == first) {
			first = first->next; //set reference to next entry.
			delete E;
		}
		else {//case 2: entry is not the first in the map.
			Entry* beforeE = E->prev;
			Entry* afterE = E->next;
			beforeE->next = afterE;
			afterE->prev = beforeE;
			delete E;
		}
	}

	//getTime - extracts and returns a time object from a key value for comparasin.
	Time getTime (string _k) {
		string key = _k;
		string dest;
		string origin;
		string stime;
		string sTimeY;
		string sTimeM;
		string sTimeD;
		Time time;
		string delim = ",";

		//Get origin based off of a delim
		int pos = key.find_first_of(",");
		origin = key.substr(0,pos);
		key.erase(0, key.find(delim) + delim.length());

		//Get destination based off of a delim
		pos = key.find_first_of (",");
		dest = key.substr(0,pos);
		key.erase (0, key.find (delim) + delim.length ());

		//remainder of key is the time.
		stime = key;

		sTimeY = stime.substr(0,4);
		sTimeM = stime.substr(4,2);
		sTimeD = stime.substr(6,2);
			
		//Use string stream to turn string into int for Time class.
		stringstream year(sTimeY);
		stringstream month(sTimeM);
		stringstream day(sTimeD);
		int y = 0;
		int m = 0;
		int d = 0;
		year >> y;
		month >> m;
		day >> d;

		//set d m y in Time object
		time.setDay(d);
		time.setMonth(m);
		time.setYear(y);	

		return time;
	}
};


int main()
{
	//Create the map
	Map FlightDatabase;

	while (true)
	{	
		cout << "(1) - Insert new record to flight database (existing entry will be overwritten)." << endl;
		cout << "(2) - Lookup a flight from the database (closest match will be returned if not found)." << endl;
		cout << "(3) - Delete a record from flight database." << endl;
		cout << "(4) - Print all records in the database." << endl;
		cout << "(5) - exit." << endl;
		cout << "Please make a selection: ";
		
		int input;
		cin >> input;
		cout << endl << "==========" << endl;

		if (input == 5) {
			break;
		}

		switch (input) {
		case 1: { //INSERT/UPDATE A NEW ENTRY
			cout << "Please enter an origin, destination and time seperated by commas: ";
			string key;
			cin >> key;

			cout << "Please enter a flight number and fare seperated by commas: ";
			string value;
			cin >> value;
			
			FlightDatabase.put (key, value);
			cout << "==========" << endl << endl;
			break;
		}
		case 2: {//SEARCH FOR AN ENTRY, CAN PROVIDE A RECOMMENDATION IF NOT FOUND
			cout << "To look up a flight enter the origin, destination and time seperated by commas: ";
			string key;
			cin >> key;
			pair<Entry*, Entry*> E = FlightDatabase.find (key); //Set the seturn value to a pair so i can easily return 2 values if needed
			Entry* entry1 = E.first; //first item in the pair
			Entry* entry2 = E.second; //second item in the pair

			if (entry2 == nullptr) {
				cout << "The flight number and fare are: " << entry1->getValue () << endl;
				cout << "==========" << endl << endl;
			}
			else {
				cout << "The flight number and fare are: " << endl;
				cout << entry1->getValue () << endl << entry2->getValue() << endl;
				cout << "==========" << endl << endl;
			}
			break;
		}
		case 3: {//DELETE A FLIGHT
			cout << "To delete a flight enter the origin, destination and time seperated by commas: ";
			string key;
			cin >> key;
			FlightDatabase.erase (key);
			cout << "==========" << endl << endl;
			break;
		}
		case 4: {//PRINT THE FLIGHT DATABASE
			FlightDatabase.print();
			cout << "==========" << endl << endl;
			break;
		}
		default: {
			cout << "That option is not available, please try again." << endl;
		}
		}
	}
	return 0;
}