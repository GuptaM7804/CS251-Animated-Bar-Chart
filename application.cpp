// Manav Gupta
// University of Illinois, Chicago
// CS 251: Spring 2022
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;

void menu(string &filename) {
	cout << "Please input the name of the file ";
	cout << "you would like to view as bar charts" << endl;
	cout << "Your options are 'cities.txt' ";
	cout << "or 'brands.txt' or q to quit: ";
	cin >> filename;
}

int numBars() {
    int x;
    cout << "How many bars would you like to view at a time?" << endl;
	cout << "Select a number between 1-12: ";
	cin >> x;
	return x;
}

int numFrames() {
    int y;
	cout << "And how many frames would you like to view?" << endl;
	cout << "For 'cities.txt' select a number between 1-519" << endl;
	cout << "For 'brands.txt' select a number between 1-217" << endl;
	cout << "Or enter -1 to view all possible frames: " << endl;
	cin >> y;
	return y;
}

int numSpeed() {
    int speed;
    cout << "Enter speed of animation (1 is fastest): ";
	cin >> speed;
	return speed;
}

void handleError(string &filename) {
    cout << "Error: Unable to open " << filename;
    cout << "try again: ";
    cin >> filename;
    cout << endl;
}

int main() {
    cout << "Welcome to Animated Bar Charts!!!" << endl;
	string filename;
    menu(filename);
	while (filename != "q") {
    	ifstream inFile(filename);
    	if (!inFile.fail()) {
        	string title;
        	getline(inFile, title);
        	string xlabel;
        	getline(inFile, xlabel);
        	string source;
        	getline(inFile, source);
        	BarChartAnimate bca(title, xlabel, source);
        	while (!inFile.eof()) {
        		bca.addFrame(inFile);
        	}
        	bca.setSpeed(numSpeed());
        	bca.animate(cout, numBars(), numFrames());
            cout << endl;
            menu(filename);
    	} else {
    	    handleError(filename);
    	}
	}
	cout << "Goodbye!" << endl;
    return 0;
}
