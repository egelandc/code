#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

//Simple class containing information about an expression
class variable {
public:
	int missing_arguments_ = 0; //Arguments not yet evalueted
	int value_ = 0; //Current value
	string name_;
	variable(string name) {
		name_ = name;
	}
};

//Function declarations
void parse_line(string line, unordered_map<string, int>& numbers, unordered_multimap<string, variable*>& unevaluated_numbers);
bool is_number(string number_string);
string trim(string& str);
void print_value(string variable_name, int value);
bool str2int(char const *s);
void recursive_update(string name, unordered_multimap<string, variable*>& unevaluated_numbers, int sum);

int main() {
	string line;
	unordered_map<string, int> numbers; //Expressions completely evalueted
	unordered_multimap<string, variable*> unevaluated_numbers; //Partial evaluated expressions

	//Read input, parse and evaluate.
	while (getline(cin, line)) {
		parse_line(line,numbers, unevaluated_numbers);
	}

	return 0;
}

// Function parses an expression string. If function only contains number,
// then print value and store expression value, if not store expression
// until it is completetly evaleated.
// This function contains redundant code, and should be separeted into 
// more functions, it should only parse the line and hand it over to
// another function evaluating the expression.
void parse_line(string line, unordered_map<string,int>& numbers, unordered_multimap<string, variable*>& unevaluated_numbers) {
	//We first strip the variable name from the string.
	size_t pos = line.find("=");
	string variable_name = line.substr(0, pos);
	variable_name = trim(variable_name);
	variable* var = new variable(variable_name);

	//Setup argument delimiter
	line.erase(0, pos + 1); //Erase variable_name + delimiter
	bool evaluated = true;
	string delimiter = "+";
	string token;

	//TODO: remove this variable, value is on variable object.
	int partial_sum = 0;

	//Run over all arguments and update value of current expression
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		token = trim(token);

		//If argument is an integer then update its current value
		//check whether we already evalueted this expression.
		if (str2int(token.c_str())) {
			partial_sum += stol(token);
			var->value_ += stol(token);
		}
		else {
			std::unordered_map<std::string, int>::const_iterator got = numbers.find(token);

			if (got == numbers.end()) {
				evaluated = false;
				var->missing_arguments_++;
				unevaluated_numbers.emplace(token, var);
			}
			else {
				partial_sum += got->second;
				var->value_ += got->second;
			}
		}
	}

	//This part is only for the last argument in the parsed string and should 
	//be integrated with the above code. //No time to fix this.
	line = trim(line);
	if (str2int(line.c_str())) {
		partial_sum += stol(line);
		var->value_ += partial_sum;
	}
	else {
		std::unordered_map<std::string, int>::const_iterator got = numbers.find(line);
		if (got == numbers.end()) {
			evaluated = false;
			var->missing_arguments_++;
			unevaluated_numbers.emplace(line, var);
		}
		else {
			partial_sum += got->second;
		}
	}

	//If the expression was evaluated, then print and update partially completed 
	//expressions, print them is they are completely evaluated.
	if (evaluated) {
		print_value(variable_name, partial_sum);
		numbers.insert(make_pair(variable_name, partial_sum));

		//Update expressions missing this argument.
		auto its = unevaluated_numbers.equal_range(variable_name);
		for (auto it = its.first; it != its.second; ++it) {
			it->second->value_ += partial_sum;
			it->second->missing_arguments_--;
			
			//If the new updated expressions are completly evaluated, store and print.
			if (it->second->missing_arguments_ == 0) {
				print_value(it->second->name_, it->second->value_);
				recursive_update(it->second->name_, unevaluated_numbers,it->second->value_);
			}
		}
	}
}

//Print expressions
void print_value(string variable_name, int value) {
	cout << "===>" << variable_name << " = " << value << endl;
}

//Remove whitespaces from start and ending of str.
string trim(string& str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

//Function for testing if a substring is an integer.
bool str2int(const char *s)
{
	int i;
	char c;
	std::stringstream ss(s);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		// not an integer
		return false;
	}
	return true;
}

//When a new expressions is evaluated, we must update dependent expressions.
void recursive_update(string name, unordered_multimap<string, variable*>& unevaluated_numbers,int sum) {
	//Find all unevaluated expressions containing name in an argument.
	auto its = unevaluated_numbers.equal_range(name);
	//Update every expression
	for (auto it = its.first; it != its.second; ++it) {
		it->second->value_ += sum;
		it->second->missing_arguments_--;
		if (it->second->missing_arguments_ == 0) {
			print_value(it->second->name_, it->second->value_);
			recursive_update(it->second->name_, unevaluated_numbers, it->second->value_);
		}
	}
}

