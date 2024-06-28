#include "../include/topological_sort.h"
// #include <iostream>
#include <vector>
#include <unordered_map>

void dfs(int node, std::unordered_map<int, std::unordered_set<int>>& g, std::unordered_set<int>& vis, std::vector<int>& scc) {
	if(vis.find(node) != vis.end()) return;
	scc.push_back(node);
	vis.insert(node);
	for (auto& nb :g[node]) dfs(nb, g, vis, scc);
}

// return all SCCs 
std::vector<std::vector<int>> Graph::get_sccs(std::vector<std::vector<int>>& edges) {
	auto topo_ordering = this->topo_sort();	

	std::vector<std::vector<int>> sccs;
	std::unordered_set<int> vis;
	
	if (this->gT.size() == 0) this->build_gT(edges);

	for (auto it = topo_ordering.rbegin(); it != topo_ordering.rend(); it++) {	// visit nodes in the reverse topological ordering
		int node = *it;
		if (vis.find(node) == vis.end()) {
			auto scc = std::vector<int>();
			dfs(node, this->gT, vis, scc);
			sccs.push_back(scc);
		}
	} 
	
	return sccs;
} 


