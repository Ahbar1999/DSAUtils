#include <cmath>
#include <iostream>
#include "../include/tree.h"

// constructor
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
