#include <vector>

class Tree{
	private:
		const int tree_max_dist;	// dist of root to leaf i.e. max jumping distance 
		std::vector<int> parent;		// nodes of the tree
		// jumping_table[i][j] = 2 ^j th ancestor of ith node(in nodes array) 
		std::vector<std::vector<int>> jumping_table;
		std::vector<int> depth;

	public:
		// constructor takes in an array of nodes where each node is labelled from 0 to sizeof(nodes) - 1
		// parent[i] is the parent of ith node, with parent[0] = -1;
		Tree(std::vector<int>& parent);
		// lowest common ancestor of node a and node b
		int lca(int a, int b);
		int kth_ancestor(int a, int k);	// kth ancestor of node a 
};
