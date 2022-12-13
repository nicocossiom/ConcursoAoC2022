// CPP code for printing shortest path between
// two vertices of unweighted graph
#include <bits/stdc++.h>
using namespace std;

map<int,char> nodes;
// utility function to form edge between two vertices
// source and dest
void add_edge(vector<int> adj[], int src, int dest)
{
	adj[src].push_back(dest);
	//adj[dest].push_back(src);
}

// a modified version of BFS that stores predecessor
// of each vertex in array p
// and its distance from source in array d
bool BFS(vector<int> adj[], int src, int dest, int v,
		int pred[], int dist[])
{
	// a queue to maintain queue of vertices whose
	// adjacency list is to be scanned as per normal
	// DFS algorithm
	list<int> queue;

	// boolean array visited[] which stores the
	// information whether ith vertex is reached
	// at least once in the Breadth first search
	bool visited[v];

	// initially all vertices are unvisited
	// so v[i] for all i is false
	// and as no path is yet constructed
	// dist[i] for all i set to infinity
	for (int i = 0; i < v; i++) {
		visited[i] = false;
		dist[i] = INT_MAX;
		pred[i] = -1;
	}

	// now source is first to be visited and
	// distance from source to itself should be 0
	visited[src] = true;
	dist[src] = 0;
	queue.push_back(src);

	// standard BFS algorithm
	while (!queue.empty()) {
		int u = queue.front();
		queue.pop_front();
		//cout << nodes.at(u) << " ";
		for (int i = 0; i < adj[u].size(); i++) {
			if (visited[adj[u][i]] == false) {
				visited[adj[u][i]] = true;
				dist[adj[u][i]] = dist[u] + 1;
				pred[adj[u][i]] = u;
				queue.push_back(adj[u][i]);

				// We stop BFS when we find
				// destination.
				if (adj[u][i] == dest)
					return true;
			}
		}
	}

	return false;
}

// utility function to print the shortest distance
// between source vertex and destination vertex
int printShortestDistance(vector<int> adj[], int s,
						int dest, int v)
{
	// predecessor[i] array stores predecessor of
	// i and distance array stores distance of i
	// from s
	int pred[v], dist[v];

	if (BFS(adj, s, dest, v, pred, dist) == false) {
		// cout << "Given source and destination"
		// 	<< " are not connected";
		return INT_MAX;
	}

	// vector path stores the shortest path
	vector<int> path;
	int crawl = dest;
	path.push_back(crawl);
	while (pred[crawl] != -1) {
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}

	// distance from source is in distance array
	// cout << "Shortest path length is : "
	// 	<< dist[dest];

	// printing path from source to destination
	// cout << "\nPath is::\n";
	// for (int i = path.size() - 1; i >= 0; i--)
	// 	cout << nodes.at(path[i]) << " ";
	// cout << "\nPath size is::\n";
	// cout << path.size()-1 << "\n";
	return path.size()-1;
}

bool canClimb(char current, char next){
    return (next!='0') && ((next - current) <= 1);
}

// Driver program to test above functions
int main()
{

    string myText;
    ifstream MyReadFile("input");
    int i = 0;
	int j = 0;
    vector<int> start;
    int end = 0;
    
	vector<vector<int>> parse_matrix;
    while (getline (MyReadFile, myText)) {
        char char_array[myText.length()+1];
        strcpy(char_array, myText.c_str());
		j = 0;
        for(char c : char_array){
			
            if(c == 'S'){
				c = 'a';
            }
            if(c == 'E'){
                end = i*(myText.length()+1)+j;
				c = 'z';
            }
			//save every a position
			if(c=='a'){
				start.push_back(i*(myText.length()+1)+j);
			}
            nodes.insert({i*(myText.length()+1)+j,c});
			if(j==0){
				vector<int> line;
				parse_matrix.push_back(line);
			}
			parse_matrix[i].push_back(i*(myText.length()+1)+j);
            j+=1;
        }
		i+=1;
    }
	// no. of vertices
	int v = parse_matrix.size()*parse_matrix[0].size();

	// array of vectors is used to store the graph
	// in the form of an adjacency list
	vector<int> adj[v];

     for(int i = 0; i < parse_matrix.size(); i++){
        for(int j = 0; j < parse_matrix[0].size(); j++){
            //Check for available neighbors
            
            char curr = nodes.at(parse_matrix[i][j]);
            char nUp = (i == 0)? '0' : nodes.at(parse_matrix[i-1][j]);
            char nDown = i == parse_matrix.size()-1? '0' : nodes.at(parse_matrix[i+1][j]);
            char nLeft = (j == 0)? '0' : nodes.at(parse_matrix[i][j-1]);
            char nRight = (j == parse_matrix[0].size()-1)? '0' : nodes.at(parse_matrix[i][j+1]);
            //Check if available to climb
            if(canClimb(curr, nUp)){
                add_edge(adj, parse_matrix[i][j], parse_matrix[i-1][j]);
            }
            if(canClimb(curr, nDown)){
                add_edge(adj, parse_matrix[i][j], parse_matrix[i+1][j]);
            }
            if(canClimb(curr, nLeft)){
                add_edge(adj, parse_matrix[i][j], parse_matrix[i][j-1]);
            }
            if(canClimb(curr, nRight)){
                add_edge(adj, parse_matrix[i][j], parse_matrix[i][j+1]);
            }
        }
    }
	int min = INT_MAX;
    for(int src : start){
		int source = src, dest = end;
		int res = printShortestDistance(adj, source, dest, v);
		if(res < min){
			min = res;
		}
	}
	cout << min << endl;
	return 0;
}
