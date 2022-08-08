// barchartanimate.h
// Manav Gupta
// University of Illinois, Chicago
// Project 3, Spring 2022

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used in autograder, do not remove
#include "barchart.h"
  
using namespace std;

// BarChartAnimate
class BarChartAnimate {
 private:
 
    // dynamic array of BarChart
    BarChart* barcharts;
    // size variable to keep track of # of elements
    int size;
    // to keep track of total space in the array
    int capacity;
    // map of categories as keys and colors as elements
    map<string, string> colorMap;
    string title; // title of object
    string xlabel; // xlabel of object
    string source; // source of object
    int speed; // speed of animation

 public:

    // a parameterized constructor:
    // the parameters set the title, xlabel, and source
    // for this object
    // the dynamic array is initialized with size 4
    // the speed is initialized with 3
    // as that is the normal speed
    BarChartAnimate(string title, string xlabel, string source) {
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
        barcharts = new BarChart[4];
        this->size = 0;
        this->capacity = 4;
        map<string, string> colorMap;
        this->speed = 3;
    }

    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    virtual ~BarChartAnimate() {
        for (int i = 0; i < this->size; i++) {
            barcharts[i].clear();
        }
        delete[] barcharts;
    }

    // given a string as a parameter
    // finds the first instance of a ','
    // then gets the part of the string before it and
    // deletes that part of the string and the comma
    // and returns that part of the string
    string getInfo(string &line) {
        size_t pos = line.find(",");
        string info = line.substr(0, pos);
        line = line.substr(pos + 1, line.size() - info.size() - 1);
        return info;
    }

    // gets category from the parametrized string
    // then deletes it and returns it
    string getCateg(string &line) {
        string categ = line.substr(0, line.size());
        line.clear();
        return categ;
    }

    // uses string as a parameter
    // codes colors with categories in colorMap
    // using categories as keys and colors as elements
    void colorCoding(string categ) {
        // to not include black as it is not a bar color
        int colSize = COLORS.size() - 1;
        int j = colorMap.size();
        if (!this->colorMap.count(categ)) {
            while (j >= colSize) {
                j -= colSize;
            }
            this->colorMap[categ] = COLORS[j];
        }
    }

    // increase size of barcharts array if it is full
    void increaseSize() {
        if (this->size == this->capacity) {
            int newCap = this->capacity*2;
            BarChart* newBarchart = new BarChart[newCap];
            
            for (int i = 0; i < this->size; i++) {
                newBarchart[i] = this->barcharts[i];
            }
            
            delete[] this->barcharts;
            this->barcharts = newBarchart;
            this->capacity = newCap;
        }
    }

    // takes in an ifstream as a parameter
    // this function adds a new BarChart
    // to the BarChartAnimate object from the file stream.
    // it also icrements the size of BarChartAnimate object.
    void addFrame(ifstream &file) {
        string line;
        getline(file, line, '\n');
        // check: each new frame begins with empty line
        if (line.empty()) {
            // check: last line of files are blank
            if (!file.eof()) {
                getline(file, line, '\n');
                int num = stoi(line);
                BarChart b(num);
                string frame = "";
                for (int i = 0; i < num; i++) {
                    getline(file, line, '\n');
                    frame = getInfo(line);
                    string name = getInfo(line);
                    string country = getInfo(line);
                    string val = getInfo(line);
                    int value = stoi(val);
                    string categ = getCateg(line);
                    colorCoding(categ);
                    b.addBar(name, value, categ);
                }
                b.setFrame(frame);
                increaseSize();
                barcharts[this->size] = b;
                this->size++;
            }
        }
    }

    // given an int, sets speed
    // for speed of barchart animation.
    void setSpeed(int speed) {
        this->speed = speed;
    }

    // this function plays each frame stored in barcharts.
    // There is a delay between each frame due to usleep().
    // The user enters a speed and usleep uses that to
    // either increase or decrease the delay for each frame.
    // CLEARCONSOLE makes sure each frame is output in the same place.
    // Uses graph function from barchart.h to print each frame.
    // the ostream parameter is for he output
    // the top is how many bars appear in each frame
    // the endIter is for how many frames are going to be played
	void animate(ostream &output, int top, int endIter) {
    	unsigned int microsecond = 50000;
        if (endIter == -1) {
            endIter = this->size;
        }
        for (int i = 0; i < endIter; i++) {
            usleep(this->speed * microsecond);
            output << CLEARCONSOLE;
            output << BLACK << this->title << endl;
            output << BLACK << this->source << endl;
            barcharts[i].graph(output, this->colorMap, top);
            output << BLACK << this->xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
        }
	}

    // Returns the size of the BarChartAnimate object.
    int getSize() {
        return this->size;
    }

    // Function to make each barchart accessible
    // in barcharts with [] operator (like a vector)
    // If i is out of bounds,
    // throw an out_of_range error message
    BarChart& operator[](int i) {
        if (i > this->size) {
            throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }
};
