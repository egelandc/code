#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//dimension of honeycomb 
#define DIM 15
vector< vector<int> > generateGraph(int size);
int countWalks(vector< vector<int> >& graph, vector< vector<int> >& table,int steps,int pos,int& number);

int main(){

	int T, n;

	vector< vector<int> > graph = generateGraph(DIM);
	vector< vector<int> > table(DIM*DIM, vector<int>(DIM,-1));

	cin >> T;
	while (T--){
		cin >> n;
		int num;
		cout << countWalks(graph, table, n, ((DIM*DIM) / 2),num) << endl;
		//cout << num << endl;
	}

	return 0;
}


/*
/	Create a Graph representing the honeycomb of dimension n x b.
*/
vector< vector<int> > generateGraph(int size){
	vector< vector<int> > base(DIM,vector<int>(DIM));
	vector< vector<int> > graph(DIM*DIM);

	//Init vector of vectors
	int id = 0;
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			base[j][i] = id++;
		}
	}

	//Create edges representing the honeycomb
	for (int i = 0; i < DIM; i++){
		for (int j = 0; j < DIM; j++){
			if ((j% DIM) > 0){
				graph[base[j][i]].push_back(base[j - 1][i]);
				graph[base[j - 1][i]].push_back(base[j][i]);
			}
			if (i < (DIM - 1) && j < (DIM - 1)){
				graph[base[j][i]].push_back(base[j][i + 1]);
				graph[base[j][i]].push_back(base[j + 1][i + 1]);
				graph[base[j + 1][i + 1]].push_back(base[j][i]);
				graph[base[j][i+1]].push_back(base[j][i]);
			}
			else if (i < (DIM - 1) ){
				graph[base[j][i]].push_back(base[j][i + 1]);
				graph[base[j][i+1]].push_back(base[j][i]);
			}
		}
	}

	return graph;
}

int countWalks(vector< vector<int> >& graph, vector< vector<int> >& table,int steps,int pos,int &number){
	queue<int> que;
	int startPos = (DIM*DIM)/2;
	int sum = 0;
	number++;
	if (steps == 0 && pos == startPos){
		return 1;
	}

	else if (steps == 0){
		return 0;
	}

	for (int i = 0; i < graph[pos].size(); i++){
		que.push(graph[pos].at(i));

	}

	while (!que.empty()){
		int node = que.front();
		que.pop();
		if (table[node][steps - 1] == -1){
			table[node][steps - 1] = countWalks(graph, table, (steps - 1), node,number);
		}
		sum += table[node][steps - 1];
	}
	return sum;
}
