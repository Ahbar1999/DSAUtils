// least significant one
#define lsOne(x) (x & -x)	

// Mutable range query
// BIT: Binary Indexed Tree
class BIT {
	vector<int> bit_array;
	// we are not storing original array of elements	
	BIT(vector<int>& arr) {
		this->bit_array.resize(arr.size());
		for (int i = 0; i < n; i++) {
			for (int j = i - lsOne(x); j <= i; j++) {
				bit_array[i] += arr[j];
			}
		}
	}

	void set(i, x) {
		// update bit_array[j] for all j's that i is responsible for
		// handle the case for new element's addition
	} 

	int get_sum(i, j) {
		// return sum(arr[i, j]) = sum(arr[0..j]) - sum(arr[0..i-1])
		int total1 = 0;
		for (;i; i -= lsOne(i)) {
			total += this->bit_array[i];
		}

		int total2 = 0;
		for (j = j -1; j; j -= lsOne(j)) {
			total2 += this->bit_array[j];
		}

		return total1 - total2;
	} 
}
