/// Application for evaluating mathematical expressions.
///
/// Example input: 
/// > x = y + 200
/// > y = 20
/// Output:
/// ===>y = 20
/// ===>x = 220
///
/// Author: Christian Egeland

#include "expr.h"

int main() {
	string line; //Input expression
	unordered_map<string, int> numbers; //Expressions completely evalueted
	unordered_multimap<string, variable*> unevaluated_numbers; //Partial evaluated expressions

	//Read input, parse and evaluate.
	while (getline(cin, line)) {
		try {
			parse_line(line, numbers, unevaluated_numbers);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}

	return 0;
}

//Function parses an expression string. If function only contains number,
//then print value and store expression value, if not store expression
//until it is completetly evaleated.
void parse_line(string line, unordered_map<string,int>& numbers, unordered_multimap<string, variable*>& unevaluated_numbers) {
	//We first strip the variable name from the string.
	size_t pos = line.find("=");
	string variable_name = line.substr(0, pos);
	variable_name = trim(variable_name);
	variable* var = new variable(variable_name);

	//Setup argument delimiter
	line.erase(0, pos + 1); //Erase variable_name + delimiter '='
	bool evaluated = true;
	string delimiter = "+";
	string token = "";

	//Run over all arguments and update value of current expression
	while (line.length() > 0) {
		//Check if expression contains more than one argument
		if ((pos = line.find(delimiter)) == string::npos) {
			pos = line.length();
		}
		token = line.substr(0, pos);
		line.erase(0, pos + 1); //Erase variable_name + delimiter '+'
		token = trim(token);

		//If argument is an integer then update its current value
		//check whether we already evalueted this expression.
		if (string_to_int(token.c_str())) {
			var->add_to_value(stol(token));
		}
		else {
			unordered_map<string, int>::const_iterator got = numbers.find(token);

			if (got == numbers.end()) {
				evaluated = false;
				var->add_missing_arg();
				unevaluated_numbers.emplace(token, var);
			}
			else {
				var->add_to_value(got->second);
			}
		}
	}

	//If the expression was evaluated, then print and update partially completed 
	//expressions, print them is they are completely evaluated.
	if (evaluated) {
		print_value(var->get_name(), var->get_value());
		numbers.insert(make_pair(var->get_name(), var->get_value()));
		update(var, unevaluated_numbers, numbers);
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
bool string_to_int(const char *s)
{
	int i;
	char c;
	stringstream ss(s);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		// not an integer
		return false;
	}
	return true;
}

//When a new expressions is evaluated, we must update dependent expressions.
void update(variable* var, unordered_multimap<string, variable*>& unevaluated_numbers,
	unordered_map<string, int>& numbers) {
	//Find all unevaluated expressions containing name in an argument.
	auto its = unevaluated_numbers.equal_range(var->get_name());
	//Update every dependent expressions
	for (auto it = its.first; it != its.second; ++it) {
		it->second->add_to_value(var->get_value());
		it->second->decrease_missing_arg();
		if (it->second->number_of_missing_arg() == 0) {
			print_value(it->second->get_name(), it->second->get_value());
			numbers.insert(make_pair(it->second->get_name(), it->second->get_value()));
			update(it->second, unevaluated_numbers, numbers);
		}
	}
}

