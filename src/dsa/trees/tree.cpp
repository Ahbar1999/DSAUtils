#include <cmath>
#include <iostream>
#include <vector>
#include "../include/tree.h"

// constructor 2
// input: root of a binary tree given by class TreeNode
Tree::Tree(TreeNode* root) : tree_max_dist(0) {
	// build et_tree;
	fill_et_tree(root, this->et_tree);
	// also fill depth array
	// if duplicate values for nodes exist in the tree
	// maintain a unique id for each node 
}

void fill_et_tree(TreeNode* node, std::vector<int>& arr) {
	if (node == nullptr) return;
	fill_et_tree(node->left, arr);
	arr.push_back(node->val);
	// also add depth for each node	
	fill_et_tree(node->right, arr);
}

// constructor 1
// input: an array with ith node's immediate parent at parent[i], this should also include root node with value = -1 
Tree::Tree(std::vector<int>& parent): tree_max_dist(std::ceil(std::log2(parent.size()))) {
	this->parent = parent;
	this->jumping_table = std::vector<std::vector<int>>(this->parent.size(), std::vector<int>(tree_max_dist, -1));
	for (int n = 0; n < this->parent.size(); n++) {
		this->jumping_table[n][0] = this->parent[n];
	}
	
	/*	The table is built level by level instead of all for one node 
	 *	This allows for dynamic programming kind of tabulation 
	 */
	for (int p = 0; p <= tree_max_dist; p++) { 
		for (int n = 1; n < this->parent.size(); n++) {	 
			// instead of directly calculating the jump destination
			// we break it into two parts, first we find the halfway destination and if it exists
			// we find its halfway destination with together forms final destination for the original node 
			int halfway_parent = this->jumping_table[n][p - 1];
			if (halfway_parent == -1) this->jumping_table[n][p] = -1;  
			else this->jumping_table[n][p] = this->jumping_table[halfway_parent][p - 1];
		}
	}
}

int Tree::lca(int a, int b) {
	// 1st method 
	// lift both nodes to a common level then decrement levels until you reach the same node or root
	
	if (this->depth[a] < this->depth[b]) return this->lca(b, a);	// swap so that we have higher depth node as 'a'
	// depth of a is lesser than depth of b	
	// lift a to same depth/height as b	
	a = this->kth_ancestor(a, this->depth[a] - this->depth[b]);
	if (a == b) return b;	// found lca

	// moves nodes up as long as they dont meet
	for (int i =  this->tree_max_dist; i >= 0; i--) {
		// remember i is the power of 2 
		if (this->jumping_table[a][i] != this->jumping_table[b][i]) {
			a = this->jumping_table[a][i];
			b = this->jumping_table[b][i];
		}
	}

	return this->jumping_table[a][0];	// lca will be the parent of either node

	/* 2nd method: euler tour tree */
	// depth array must have been filled by euler tour constructor
	// return node with min(depth[a..k])

	/* 3rd method: tarjan's */
}

// merge two disjoin sets
void dsu_union(int x, int y, std::vector<int>& p) {
	p[y] = dsu_find(x, p);	
}

// find parent
int dsu_find(int x, std::vector<int>& p) {
	if (p[x] == x) return x;
	return p[x] = dsu_find(p[x], p);	// find with path compression
}

int lca_Tarjan(TreeNode* node, int a, int b, std::vector<int>& p) {
	p[node->val] = node->val;	// add node as its own parent
	int ans = -1;
	if (node->left) {
		ans = lca_Tarjan(node->left, a, b, p);
		dsu_union(node->val, dsu_find(node->left->val, p), p);
	}
	if (ans != -1) return ans;
	if (node->right) {
		ans = lca_Tarjan(node->right, a, b, p);
		dsu_union(node->val, dsu_find(node->right->val, p), p);
	}

	if (node->val == a) {
		if (p[b] != -1) return dsu_find(b, p);
	} else if (node->val == b) {
		if (p[a] != -1) return dsu_find(a, p);
	}

	return ans;
}


int Tree::kth_ancestor(int a, int k) {
	int at = a;	// starting position of kth ancestor
	for (int pow = 0; pow <= this->tree_max_dist; pow++) {
		if (k & (1 << pow)) {	// breaking k into powers of 2
			at = this->jumping_table[at][pow];
			if (at == -1) break;	// stop we are past the root
		}
	}
	return at;
}
