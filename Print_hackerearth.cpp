///
/// From input string, how many times can we print "hackerearth"?
///
#include <iostream>
#include <string>

using namespace std;

int main(){

	int n;
	const int letters = 7;
	cin >> n;
	
	int characters_in_word[letters];
	for(int i = 0; i < letters; i++){
		characters_in_word[i] = 0;
	}
	
	string input;
	
	cin.ignore();
	getline(cin, input);
	
	//Count all required characters from input
	for(int i = 0; i<n;i++){
		//cout << "current letter: " << input[i] << endl;
		switch(input[i]){
			case 'a' : 
				characters_in_word[0]++;
				break;
			case 'c' : 
				characters_in_word[1]++;
				break;
			case 'e' : 
				characters_in_word[2]++;
				break;
			case 'h' : 
				characters_in_word[3]++;
				break;
			case 'k' : 
				characters_in_word[4]++;
				break;
			case 'r' : 
				characters_in_word[5]++;
				break;
			case 't' : 
				characters_in_word[6]++;
				break;
			default : 
				break;
		}
		
	}
	
	/*
	for(int i = 0; i < letters; i++){
			cout << characters_in_word[i] << endl;
	}
	*/
	
	//Divide 'a', 'e', 'h' and 'r' by two, to find the correct count.
	
	characters_in_word[0] = characters_in_word[0] / 2;
	characters_in_word[2] = characters_in_word[2] / 2;
	characters_in_word[3] = characters_in_word[3] / 2;
	characters_in_word[5] = characters_in_word[5] / 2;
	int numbers = n;
	//Calculate number of words.
	for(int i = 0; i < letters; i++){
		if(characters_in_word[i] < numbers){
			numbers = characters_in_word[i];
		}
	}

	cout << numbers << endl;
	
	return 0;
}
