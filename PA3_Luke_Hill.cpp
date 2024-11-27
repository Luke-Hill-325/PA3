#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<bool>> GMatrix;

int N;
GMatrix G;

void printSqMatrix(GMatrix& m) {
	for(int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

GMatrix Gk(GMatrix& gprev) {
	GMatrix result = GMatrix(N, vector<bool>(N, false));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int h = 0; h < N; h++)
				result[i][j] = result[i][j] || (gprev[i][h] && G[h][j]);
	return result;
}
GMatrix transitiveClosure() {
	GMatrix curGk = G;
	GMatrix Gplus = G;
	for (int k = 1; k < N; k++) {
		curGk = Gk(curGk);
		cout << "G" << k + 1 << ":\n";
		printSqMatrix(curGk);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				Gplus[i][j] = Gplus[i][j] || curGk[i][j];
	}
	return Gplus;
}

int main(int argc, char *argv[], char *envp[]) {
	N = 4;
	G = {
		{false, true, false, false},
		{false, false, true, true },
		{false, false, false, true},
		{true, false, false, false}
	};
	cout << "G1 (the initial G with paths of length 1):\n";
	printSqMatrix(G);

	GMatrix GClosure = transitiveClosure();
	cout << "Transitive Closure: \n";
	printSqMatrix(GClosure);
}
