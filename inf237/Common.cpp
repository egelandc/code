#include <iostream>
#include <algorithm>
#include <vector> 
#include <queue>

using namespace std;

#define INF 2<<28

int findCommonPath(vector< vector<int> >& graph, vector< vector<int> >& weights, int start, int t1, int t2);

int main() {

	int T;
	
	cin >> T;
	
	while (T--){
		int N, M;
		cin >> N >> M;
		//Build graph
		vector< vector<int> > graph(N);
		vector< vector<int> > weights(N);
		int u, v, w;
		int start, P, Q;
		cin >> start >> P >> Q;
		for (int i = 0; i < M; i++){
			cin >> u >> v >> w;
			graph[u].push_back(v);
			graph[v].push_back(u);
			weights[u].push_back(w);
			weights[v].push_back(w);
		}

		findCommonPath(graph, weights, start, P, Q);
	}

	return 0;
}



int findCommonPath(vector< vector<int> >& graph, vector< vector<int> >& weights, int start, int P, int Q){

	vector<int> dist(graph.size(), INF);
	vector<bool> processed(graph.size());
	dist[start] = 0;
	queue<int> q;
	vector< vector<int> > prev(graph.size());
	vector< vector<int> > prevweights(graph.size());
	vector< vector<int> > pathEdges(graph.size(),vector<int>(graph.size(),0));
	prev[start].push_back(start);
	int n = graph.size();
	
	//Find all shortest paths
	while (n--){
		int node;
		for (int i = 0; i < graph.size(); i++){
			if (!processed[i]){
				node = i;
				break;
			}
		}

		for (int i = 0; i < graph.size(); i++){
			if (dist[i] < dist[node] && !processed[i]){
				node = i;
			}
		}

		for (int i = 0; i < graph[node].size(); i++){

			if (!processed[graph[node][i]]){
				if (dist[graph[node][i]] >(dist[node] + weights[node][i])){
					dist[graph[node][i]] = dist[node] + weights[node][i];
					prevweights[graph[node][i]].clear();
					prev[graph[node][i]].clear();
					prev[graph[node][i]].push_back(node);
					prevweights[graph[node][i]].push_back(weights[node][i]);
				}
				else if (dist[graph[node][i]] == dist[node] + weights[node][i]){
					prev[graph[node][i]].push_back(node);
					prevweights[graph[node][i]].push_back(weights[node][i]);
				}
			}
		}
		processed[node] = true;
	}

	vector<bool> vis1(graph.size(), 0);
	vector<bool> vis2(graph.size(), 0);
	vector<bool> vis3(graph.size(), 0);
	q.push(P);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		if (vis1[node] == 0){
		for (int i = 0;i  < prev[node].size(); i++){

			
				if (prev[node][i] != start){
					q.push(prev[node][i]);
				}
				
				if (pathEdges[node][prev[node][i]] == 0){
					pathEdges[node][prev[node][i]]++;
				}

			}
		vis1[node] = true;
		}
	}

	q.push(Q);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		if (vis2[node] == 0){
			for (int i = 0; i < prev[node].size(); i++){
			
				if (prev[node][i] != start){
					q.push(prev[node][i]);
				}

				if (pathEdges[node][prev[node][i]] == 1){
					pathEdges[node][prev[node][i]]++;
				}
				
			}
		vis2[node] = true;
		}
	}
	
	int temp;
	//Maximize time spent 
	vector<int> commontime(graph.size());
	q.push(Q);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		if (vis3[node] == 0){
		for (int i = 0; i < prev[node].size(); i++){
			
				if (prev[node][i] != start){
					q.push(prev[node][i]);
				}
				if (pathEdges[node][prev[node][i]] > 1){
					commontime[prev[node][i]] = max(commontime[prev[node][i]], commontime[node] + prevweights[node][i]);
				}
				
			}
		vis3[node] = true;
		}
	}
	
	cout << commontime[start] << endl;

	 return 0;
}


