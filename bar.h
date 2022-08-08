// bar.h
// Manav Gupta
// University of Illinois, Chicago
// Project 3, Spring 2022

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove

using namespace std;

// Bar
class Bar {
 private:

    // variable for name of object (new york, starbucks, etc)
    string name;
    // variable for the value assigned to it (population, etc)
    int value;
    // variable for the category it comes under
    // used later to decide color for this object
    string category;

 public:

    // default constructor:
    Bar() {
        this->name = "";
        this->value = 0;
        this->category = "";
    }

    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    Bar(string name, int value, string category) {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // destructor:
    virtual ~Bar() {
    }

    // getName:
	string getName() {
        return this->name;
	}

    // getValue:
	int getValue() {
        return this->value;
	}

    // getCategory:
	string getCategory() {
        return this->category;
	}

	// operators
    // returns 
	bool operator<(const Bar &other) const {
	    // true if this value is less than other
	    return (this->value < other.value);
	}

	bool operator<=(const Bar &other) const {
	    // true if this value is not greater than other
        return !(this->value > other.value);
	}

	bool operator>(const Bar &other) const {
	    // true if this value is greater than other
	    return (this->value > other.value);
	}

	bool operator>=(const Bar &other) const {
	    // true if this value is not less than other
        return !(this->value < other.value);
	}
};
