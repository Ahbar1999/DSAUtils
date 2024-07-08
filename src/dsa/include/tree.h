#include <vector>

class TreeNode {
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
};

class Tree{
	private:
		int tree_max_dist;		// dist of root to leaf i.e. max jumping distance 
		std::vector<int> parent;		// nodes of the tree
		// jumping_table[i][j] = 2 ^j th ancestor of ith node(in nodes array) 
		std::vector<std::vector<int>> jumping_table;
		std::vector<int> depth;
		std::vector<int> et_tree;		// euler tour tree array, nodes of the tree appear in a dfs order


	public:
		// constructor takes in an array of nodes where each node is labelled from 0 to sizeof(nodes) - 1
		// parent[i] is the parent of ith node, with parent[0] = -1;
		Tree(std::vector<int>& parent);	// constructor 1
		Tree(TreeNode* root);	// constructor 2
		// lowest common ancestor of node a and node b
		int lca(int a, int b);
		int kth_ancestor(int a, int k);	// kth ancestor of node a 
};
