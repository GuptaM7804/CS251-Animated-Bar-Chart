// barchart.h
// Manav Gupta
// University of Illinois, Chicago
// Project 3, Spring 2022

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Replit (dark mode terminal)
// const string CYAN("\033[1;36m");
// const string GREEN("\033[1;32m");
// const string GOLD("\033[1;33m");
// const string RED("\033[1;31m");
// const string PURPLE("\033[1;35m");
// const string BLUE("\033[1;34m");
// const string WHITE("\033[1;37m");
// const string RESET("\033[0m");

// BarChart
class BarChart {
 private:

    // dynamic array of Bar
    Bar* bars;
    // variable to keep track of total space in array
    int capacity;
    // variable to keep track of # of elements in array
    int size;
    // name of current frame (year, month, date, etc)
    string frame;
    
 public:
    
    // default constructor:
    BarChart() {
        this->bars = nullptr;
        this->capacity = 0;
        this->size = 0;
        this->frame = "";
    }
    
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        this->bars = new Bar[n];
        this->capacity = n;
        this->size = 0;
        this->frame = "";
    }

    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart
    // that contains a copy of an existing BarChart.
    BarChart(const BarChart& other) {
        int total = other.capacity + other.size;
        this->bars = new Bar[total];
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        // check: if other actually has any elements in the array
        if (other.size != 0) {
            for (int i = 0; i < other.size; i++) {
                string name = other.bars[i].getName();
                int value = other.bars[i].getValue();
                string category = other.bars[i].getCategory();
                Bar b(name, value, category);
                this->bars[i] = b;
            }
        }
    }
    
    // copy operator=
    // similar to above, however, called when
    // one barchart is assigned to another
    // with an '=' sign
    BarChart& operator=(const BarChart& other) {
        if (this == &other) {
          return *this;
        }
        delete[] bars;
        int total = other.capacity + other.size;
        this->bars = new Bar[total];
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        if (other.size != 0) {
            for (int i = 0; i < other.size; i++) {
                string name = other.bars[i].getName();
                int value = other.bars[i].getValue();
                string category = other.bars[i].getCategory();
                Bar b(name, value, category);
                this->bars[i] = b;
            }
        }
        return *this;
    }

    // clear
    // frees memory and resets all private member
    // variables to default values.
    void clear() {
        delete[] this->bars;
        this->bars = nullptr;
        this->capacity = 0;
        this->size = 0;
        this->frame = "";
    }
    
    // destructor:
    //
    // Called automatically by C++ to free the
    // memory associated by the BarChart.
    virtual ~BarChart() {
        delete[] bars;
    }
    
    // setFrame, sets the frame given a string
    // as a parameter
    void setFrame(string frame) {
        this->frame = frame;
    }
    
    // getFrame()
    // Returns the frame of the BarChart object.
    string getFrame() {
        return this->frame;
    }

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room, size == capacity
    bool addBar(string name, int value, string category) {
        if (this->capacity == this->size) {
            return false;
        }
        Bar b(name, value, category);
        int i = this->size;
        this->bars[i] = b;
        this->size += 1;
        return true;
    }
    
    // getSize()
    // Returns the size (number of bars/elements)
    // of theBarChart object
    int getSize() {
        return this->size;
    }
    
    // operator[]
    // Returns Bar element in BarChart.
    // To make each Bar accessible in bars
    // with [] operator (like a vector)
    // If i is out of bounds,
    // throw an out_of_range error message
    Bar& operator[](int i) {
        if (i > this->size) {
            throw out_of_range("BarChart: i out of bounds");
        }
        return this->bars[i];
    }
    
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.
    // output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
        sort(bars, bars+size, greater<Bar>());
        output << "frame: " << this->frame << endl;
        for (int i = 0; i < this->size; i++) {
            output << bars[i].getName() << " ";
            output << bars[i].getValue() << " ";
            output << bars[i].getCategory() << endl; 
        }
    }
    
    // graph
    // Used for printing out the bar.
    // output is any stream (cout,
    // file stream, string stream)
    // colorMap chooses which color the BOX
    // should be printed as.
    // top chooses the amount of elements in bars
    // to be outputted
    void graph(ostream &output, map<string, string> &colorMap, int top) {
        int lenMax = 60;
        string color = "";
        sort(bars, bars+size, greater<Bar>());
        int standard = this->bars[0].getValue();
        for (int i = 0; i < top; i++) {
            int numbox = this->bars[i].getValue();
            int val = numbox * lenMax / standard;
            string barstr = "";
            for (int j = 0; j < val; j++) {
                barstr += BOX;
            }
            string cat = this->bars[i].getCategory();
            color = colorMap[cat];
            string name = this->bars[i].getName();
            output << color << barstr << " ";
            output << name << " " << numbox << endl;
        }
    }
};
