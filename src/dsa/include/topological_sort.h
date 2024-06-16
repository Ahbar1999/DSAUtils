#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph{
	private:
		std::unordered_map<int, std::unordered_set<int>> g;
		std::vector<int> f;		// finishing times for each vertex
		std::vector<int> s; 	// starting time for each vertex
	public:
		// declare and define constructor here only
		Graph(std::vector<std::vector<int>>& edges, bool dir=true){
			// input is an edge list and a boolean for directed or not
			for (auto& e: edges) {
				if (this->g.find(e[0]) == this->g.end()) this->g[e[0]] = std::unordered_set<int>();
				g[e[0]].insert(e[1]);
				if (!dir) {
					if (this->g.find(e[1]) == this->g.end()) this->g[e[1]] = std::unordered_set<int>();
					g[e[1]].insert(e[0]);
				}
			}
		}
		// return topological ordering of vertices of this graph
		std::vector<int> topo_sort();
		// basically add each vertex as it fnishes getting visited to the front of a queue
};
