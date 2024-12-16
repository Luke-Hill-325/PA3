#include<iostream>
#include<vector>
#include<string>
#include<sstream>
//#include<graphviz/cgraph.h>
#include<graphviz/gvc.h>

using namespace std;

typedef vector<vector<bool>> GMatrix;

int N;
GMatrix G;
int curNodeID = 1;
int curEdgeID = 0;

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
		//cout << "G" << k + 1 << ":\n";
		//printSqMatrix(curGk);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				Gplus[i][j] = Gplus[i][j] || curGk[i][j];
	}
	return Gplus;
}

void renderSqMatrix(GMatrix& m, Agraph_t* g) {
	vector<Agnode_t*> nodes;
	for (int i = 0; i < N; i++){
		char id[1];
		id[0] = char(curNodeID++);
		Agnode_t* newnode = agnode(g, id, 1);
		nodes.push_back(newnode);
		//agidnode(g, (ulong)i, 1);
	}
	for (int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if (m[i][j]){
				//agidedge(g, agidnode(g, (ulong)i, 0), agidnode(g, (ulong)j, 0), (ulong)(i * 10 + j), 1);
				char id[1];
				id[0] = char(curEdgeID++);
				agedge(g, nodes[i], nodes[j], id, 1);
			}
		}
	}
}

int main(int argc, char** argv) {
	GVC_t *gvc = gvContext();
	gvParseArgs(gvc, argc, argv);
	Agraph_t *g = agopen("g", Agdirected, 0);
	agattr(g,AGNODE,"shape","point");
	agattr(g,AGNODE,"width","1");

	int a,b;
	string in;
	getline(cin, in);
	while(getline(cin, in)){
		if (!in.empty() && isdigit(in.front())) {
			stringstream(in) >> N; 
			G = GMatrix(N, vector<bool>(N, false));
			while(true) {
				getline(cin, in);
				while(in.empty()){
					getline(cin, in);
				}
				stringstream(in) >> a >> b;
				if (a == 0 && b == 0)
					break;
				G[a - 1][b - 1] = true;
			}
			//cout << "G1 (the initial G with paths of length 1):\n";
			//printSqMatrix(G);

			GMatrix GClosure = transitiveClosure();
			//cout << "Transitive Closure: \n";
			//printSqMatrix(GClosure);

			GMatrix GReflexiveTransitiveClosure = GClosure;
			for (int ij = 0; ij < N; ij++){
				GReflexiveTransitiveClosure[ij][ij] = GReflexiveTransitiveClosure[ij][ij] || true;
			}
			//cout << "Reflexive Transitive Closure: \n";
			//printSqMatrix(GReflexiveTransitiveClosure);

			//Agraph_t *Gr = agsubg(g, "G", 1);
			renderSqMatrix(G, g);
			
			//Agraph_t *RTCG = agsubg(g, "ReflexiveTransitiveClosure", 2);
			//cout << "sub2: " << RTCG << endl;
			renderSqMatrix(GReflexiveTransitiveClosure, g);
		}
	}
  	// Compute a layout using layout engine from command line args
  	gvLayoutJobs(gvc, g);

  	// Write the graph according to -T and -o options
  	gvRenderJobs(gvc, g);

  	// Free layout data
  	gvFreeLayout(gvc, g);

  	// Free graph structures
  	agclose(g);
	
	return gvFreeContext(gvc);
}
