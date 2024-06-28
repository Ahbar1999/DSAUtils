#include "../include/topological_sort.h"
// #include <iostream>
#include <vector>
#include <unordered_map>

// to simulate visit of nodes in the reverse order of their finishing times(i.e. largest finish time first) we can use a stack
// instead of actually storing timestamps
void dfs(int node, std::unordered_map<int, std::unordered_set<int>>& g, std::vector<int>& stk) {
	for (auto nb: g[node]) {
		dfs(nb, g, stk);	
	}
	stk.push_back(node);
}

std::vector<int> Graph::topo_sort() {
	auto stk = std::vector<int>();
	dfs(0, this->g, stk);	
	std::reverse(stk.begin(), stk.end());
	return stk;
} 
