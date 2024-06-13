#include <vector>
#include <stdio.h>

class Segment_Tree {
	/*	POINTS TO REMEMBER
	 *		-> if root node starts at index 0 
	 *			then left and right child are at 2 * node + 1, 2 * node + 2 respectively
	 *		-> if root contains range: (l, r), all ranges are inclusive
	 *			then left child contains (l, mid) and right child contains(mid +1 , r)
	 *			where mid = (l + r) / 2, integer division
	 * */
	// Leaving the implementation details because segment tree implementation
	// heavily depends on the type of operations required
	public:
		Segment_Tree(std::vector<int>& arr, int n) {
			this->tree.resize(4 * n); 
		}
	private:
		std::vector<int> tree;

};
