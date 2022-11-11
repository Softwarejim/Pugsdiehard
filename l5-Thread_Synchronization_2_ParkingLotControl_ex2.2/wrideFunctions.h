#include <iostream>
using namespace std;

bool entryDoorOpen = false; 
bool exitDoorOpen = false;
bool carWaitingEntry = false;
bool carWaitingExit = false;
bool entryOrccupied = false;
bool exitOrccupied = false;

/***********CAR*****************************************/
void CarDrivesToEntryGarageDoor(string* CarThreadId){
    entryOrccupied = true;
    cout << *CarThreadId << " drives to entry garagedoor! " << endl; 
    carWaitingEntry = true;
}

void CarIsWaitingAtTheEntryGaragedoor(string* CarThreadId){
    cout << *CarThreadId << " is waiting at the Entry garagedoor! " << endl; 
}

void CarDrivesIntoParkinglot(string* CarThreadId){
    cout << *CarThreadId << " drives in to parkinglot! " << endl; 
    carWaitingEntry = false;
}

void CarDrivesToExitGarageDoor(string* CarThreadId){
     exitOrccupied = true;
     cout << *CarThreadId << " drives to exit garagedoor! " << endl; 
     carWaitingExit = true;
}

void CarIsWaitingAtTheExitGaragedoor(string* CarThreadId){
    cout << *CarThreadId << " is waiting at the exit garagedoor! " << endl; 
}

void CarDrivesOutOfParkinglot(string* CarThreadId){
    cout << *CarThreadId << " drives out of parkinglot! " << endl; 
    carWaitingExit = false;
}
void CarIsParktInParkinglot(string* CarThreadId){
    cout << *CarThreadId << " is parkt in parkinglot! " << endl; 
    entryOrccupied = false;
}
void CarIsWaitingOutside(string* CarThreadId){
    cout << *CarThreadId << " is waiting outside parkinglot! " << endl; 
    exitOrccupied = false;
}

/***********GARAGEDOOR*****************************************/
void EntryGaragedoorOpens(){
    cout << "Entry Garagedoor opens! " << endl; 
    entryDoorOpen = true;
}

void EntryGaragedoorIsOpen(){
    cout << "Entry Garageoor is open! " << endl; 
}

void EntryGaragedoorClosses(){
    cout << "Entry Garagedoor closses! " << endl; 
    entryDoorOpen = false;
}

void EntryGaragedoorIsClosse(){
    cout << "Entry Garagedoor is closse! " << endl; 
}
void ExitGaragedoorOpens(){
    cout << "Exit Garagedoor opens! " << endl; 
    exitDoorOpen = true;
}

void ExitGaragedoorIsOpen(){
    cout << "Exit Garageoor is open! " << endl;
    exitDoorOpen = true;

}

void ExitGaragedoorClosses(){
    cout << "Exit Garagedoor closses! " << endl; 
    exitDoorOpen = false;
}

void ExitGaragedoorIsClosse(){
    cout << "Exit Garagedoor is closse! " << endl; 
}