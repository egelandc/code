#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void update(vector<int> & tree, int pos, int value);
int countMovies(vector<int> & tree, int right);

int main(){

	int T;
	int N, M;
	cin >> T;

	while (T--){
		cin >> N;
		cin >> M;
		vector<int> movieMap(N+1);

		int l = ceil(log2(N + M));
		int size = 2 * pow(2, l);

		vector<int> tree(size, 0);

		for (int i = 0; i < N+1; i++){

			movieMap[N - i ] = size - i - 1;

		}

		//Set values for movies.
		for (int i = 1; i < N; i++){
			tree[size - i] = 1;
		}

		//Build sums in tree.
		for (int i = size - 1; i > 1; i--){
			tree[i / 2] += tree[i];
		}
		
		int req;
		int first = size - N;

		for (int i = 0; i < M; i++){
			cin >> req;
			cout << countMovies(tree, movieMap[req]); 
			if (i < (M - 1)){
				cout << " ";
			}
			update(tree, movieMap[req], -1);
			update(tree, first, 1);
			first--;
			movieMap[req] = first;
		}
		cout << endl;

	}


	return 0;
}

void update(vector<int> & tree, int pos, int value){
	tree[pos] += value;
	while (pos > 0){
		pos = pos / 2;
		tree[pos] += value;
	}
}


int countMovies(vector<int> & tree, int right){
	int remove = 0;
	//count movies
	while (right != 0){

		if (right % 2 == 0){
			remove += tree[(right + 1)];
		}

		right = right / 2;
	}

	return tree[1] - remove;
}
