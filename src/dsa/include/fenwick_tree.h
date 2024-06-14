#include <vector>
// least significant one
#define lsOne(x) (x & -x)

// Mutable range query
// BIT: Binary Indexed Tree
class BIT {
	private:
		std::vector<int> bit_array;
	public:
		// we are not storing original array of elements
		// Constructor is defined here only
		BIT(std::vector<int>& arr) {
			this->bit_array.resize(arr.size());
			int n = arr.size();	
			for (int i = 0; i < n; i++) {
				for (int j = i - lsOne(i); j <= i; j++) {
					bit_array[i] += arr[j];
				}
			}
		}
		// update bit_array[j] for all j's that i is responsible for
		// handle the case for new element's addition
		void set(int i, int x);
		int get_sum(int i, int j); 
};
