#include <iostream>
#include "../include/fenwick_tree.h"
// least significant one
#define lsOne(x) (x & -x)	

// Mutable range query
// BIT: Binary Indexed Tree
void BIT::set(int i, int x) {
	std::cout << "TODO!" << std::endl;
	// update bit_array[j] for all j's that i is responsible for
	// handle the case for new element's addition
} 

int BIT::get_sum(int i, int j) {
	// return sum(arr[i, j]) = sum(arr[0..j]) - sum(arr[0..i-1])
	int total1 = 0;
	for (;i; i -= lsOne(i)) {
		total1 += this->bit_array[i];
	}

	int total2 = 0;
	for (j = j -1; j; j -= lsOne(j)) {
		total2 += this->bit_array[j];
	}

	return total1 - total2;
} 
