#ifndef my_header
#define my_header
//Include 
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

// Class declaration containing information about an expression and manipulators
class variable {
private:
	int missing_arguments_ = 0; //Arguments not yet evalueted
	int value_ = 0; //Current value
	string name_;
public:
	variable(string name) {
		name_ = name;
	}

	string get_name() {
		return name_;
	}

	int get_value() {
		return value_;
	}

	void add_to_value(int value) {
		value_ += value;
	}

	void add_missing_arg() {
		missing_arguments_++;
	}

	void decrease_missing_arg() {
		missing_arguments_--;
	}

	int number_of_missing_arg() {
		return missing_arguments_;
	}
};

//Function declarations
void parse_line(string line, unordered_map<string, int>& numbers, unordered_multimap<string, variable*>& unevaluated_numbers);
string trim(string& str);
void print_value(string variable_name, int value);
bool string_to_int(char const *s);
void update(variable* var, unordered_multimap<string, variable*>& unevaluated_numbers,
	unordered_map<string, int>& numbers);

#endif
