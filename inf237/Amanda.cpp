#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>

#define INIT -1 //Value for initializing vertices.
#define INF 2<<30

using namespace std;

//Function definitions
int bfs(const vector< vector<int> >& graph, vector<int>& airports, int initV, vector<int>& completed, vector<int>& processed); //Bicolor the graph.

int main(){
	int n, m, a, b, c, lounges = 0; // n = airports and m = routes(max 200000.)
	cin >> n >> m;
	vector<int> airports(n + 1, INIT); //What 
	vector<int> PreprocessedAirports(n + 1, INIT); //What 
	vector<int> completed(n + 1, INF);
	vector<int> processed(n + 1, INF);
	//Graph representation
	vector< vector<int> > graph(n + 1);
	vector< vector<int> > weights(n + 1);

	//Read routes and check for issues
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;

		graph[a].push_back(b);
		graph[b].push_back(a);

		weights[a].push_back(c);
		weights[b].push_back(c);

		if (c == 0){
			if (airports.at(a) == 1 || airports.at(b) == 1){
				cout << "impossible" << endl;
				return 0;
			}
			airports.at(a) = 0;
			airports.at(b) = 0;
			completed.at(a) = 1;
			completed.at(b) = 1;
		}

		else if (c == 2){
			if (airports.at(a) == 0 || airports.at(b) == 0){
				cout << "impossible" << endl;
				return 0;
			}
			airports.at(a) = 1;
			airports.at(b) = 1;
			completed.at(a) = 1;
			completed.at(b) = 1;
		}
	}

	//Check for issues
	for (int i = 1; i < n + 1; i++){
		for (int j = 0; j < graph[i].size(); j++) {
		
			if (weights[i][j] == 1){
				if ((airports.at(i) == 1 && airports.at(graph[i][j]) == 1) || (airports.at(i) == 0 && airports.at(graph[i][j]) == 0)){
					cout << "impossible" << endl;
					return 0;
				}

			}
		}

	}

	//Number of lounges neccassary.
	int counted;
	//Process the preprocessed connected components first.
	for (int i = 0; i < n; i++){
		if (completed.at(i) == 1){
			counted = bfs(graph, airports, i, completed,processed);
			if (counted == -1){
				cout << "impossible" << endl;
				return 0;
			}
			lounges += counted;
		}
	}

	//Process the rest of the connected components.
	for (int i = 0; i < n; i++){
		if (completed.at(i) == INF){
			counted = bfs(graph, airports, i, completed,processed);
			if (counted == -1){
				cout << "impossible" << endl;
				return 0;
			}
			lounges += counted;
		}
	}

	cout << lounges << endl;

	return 0;
}



int bfs(const vector< vector<int> >& graph, vector<int>& airports, int initV, vector<int>& completed, vector<int>& processed)
{

	int lounges = 0;
	int visited = 0;
	bool preprocessed = false;
	queue<int> coloring;
	
	processed[initV] = 0;

	if (airports.at(initV) == -1){
		airports.at(initV) = 0;
	}
	else {
		preprocessed = true;
	}

	coloring.push(initV);
	while (!coloring.empty()) {
		int pos = coloring.front();
		visited++; //Increase number of visited airports.
		coloring.pop();
		completed.at(pos) = 0;
		for (int i = 0; i < graph[pos].size(); ++i) {

			if (processed[graph[pos][i]] == INF) {
				processed[graph[pos][i]] = 1;
				coloring.push(graph[pos][i]);
			}

			// Color vertex. Inner loop runs only once.
			if (airports.at(pos) == -1 && airports.at(graph[pos][i]) != -1){
				airports.at(pos) = abs(airports.at(graph[pos][i]) - 1); //"Color" vertex

				//Check if coloring is valid.
				for (int j = 0; j < graph[pos].size(); ++j) {
					if (airports.at(pos) == airports.at(graph[pos][j])){
						return -1;
					}
				}
			}
		}
		if (airports.at(pos) == 1) lounges++; //Increase number of lounges
	}

	if (!preprocessed) return min(lounges, (visited - lounges));

	return lounges;
}
