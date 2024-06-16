#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "../include/suffix_arrays.h"
		// lcp(i, j) = longest common prefix of two suffixes: s[i..n-1] and s[j..n-1]
		/*	
		 *	1) calculate lcp of adjacent suffixes in the suffix array
		 *		eg. lcp[i] store lcp between suffix[i] and suffix[i + 1]
		 *	2) lcp(i, j) where i and j are not adjacent is given by:
		 *		min(lcp[pos[i]..pos[j] -1]); 
		 *			this works because the suffixes are sorted so all the suffixes
		 *			inbetween have the same common prefix
		 *		hence our problem becomes: finding the minimmum in a segment which can be solved by:
		 *								build		query	
		 *			1) segment tree 	O(n)		O(logn)
		 *			2) sparse table	O(nlogn)		O(1)
		 *
		 *		sparse table approach is better because we dont have dyanmic input(string s) and query is faster 
		 * */
		
		// p: stores the starting index(rightmost) of a suffix
		// c: stores equivalence classes/labels of the suffixes; 0 <= c[i] < s.size() 
		// std::vector<int> p, c, lcp;
		/*
		// RADIX SORT is too complicated to use and just using regular sort() should be good enough
		void radix_sort(std::vector<std::pair<std::pair<int, int>, int>>& a) {
			int n = a.size();
			std::vector<int> cnt(n);
			// sort by second pair 
			for (auto& x: a) cnt[x.first.second]++;	// count elements of each type based on second pair's class/label
			std::vector<std::pair<std::pair<int, int>, int>> a_new(n);	
			std::vector<int> pos(n);	// starting position/size of each bucket, this is the sorting step actually
			pos[0] = 0;	// position of the first bucket
			for (int i =1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
			for (auto x: a) {
				int i = x.first.second;	// index
				a_new[pos[i]] = x; 
				pos[i]++;
			}
		}
		*/
		// initialize out suffix arrays with 1 element suffixes and sort them
		// transitions will be made in make_transitions function  
void SuffixArrays::init() {
	// k == 0 phase
	std::vector<std::pair<char, int>> a(n);
	for (int i =0; i < n; i++) a[i] = {s[i], i};
	std::sort(a.begin(), a.end());
	// now logically all suffixes(size 1) are sorted
	// extract sorted indices
	for (int i =0; i  < n; i++) p[i] = a[i].second;
	// assign the first suffix a number
	c[p[0]] = 0;
	// now assign all the different suffixes different labels/classes	
	for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + !(a[i].first == a[i - 1].first);
}

void SuffixArrays::make_transitions() {
	// before calling this function\
	// we must have called init function which sets up the p and c arrays
	int k =0;
	// do till (half + half ==) whole size  
	while ((1 << k) < n) {
		// k -> k + 1; the length of suffixes doubles every iteration
		// labels of left and right parts of new suffix of size 2^k and its index which is same as previous
		// because we are only appending to the previous strings
		std::vector<std::pair<std::pair<int, int>, int>> a(n);
		for (int i = 0; i < n; i++) {
			// {left string's label, right string's label, current index}
			a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
		}
		// radix_sort(a);	// with this step total complexity is O(logn * n)
		sort(a.begin(), a.end());	// total complexity = O(logn * nlogn)
		for (int i =0; i  < n; i++) p[i] = a[i].second;
		// assign the first suffix a number
		c[p[0]] = 0;
		// now assign all the different suffixes different labels/classes	
		// note that now a[i].first is actually a pair which together represents a new eq class
		for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + !(a[i].first == a[i - 1].first);
		k++;
	}

}

int SuffixArrays::substring_search(std::string pattern) {
	// each susbtring is a prefix of some suffix
	auto i = *std::lower_bound(this->p.begin(), this->p.end(), pattern, [this](int i, std::string p) {
		return this->s.substr(i, -1) <= p;
	});
	return (this->s.substr(i, pattern.size()) == pattern) ? i : -1;  
}

void SuffixArrays::build_lcp() {
	int k = 0;	// character to skip during comparison of current two suffixes
	// lcp of two consecutive suffixes, s[i] and s[i - 1]
	for (int i = 0; i < this->n - 1; i++) {
		// we need position of each suffix in the suffix array
		// we have p[i] which gives a suffix for each position
		// array c contains **inverse permutation** of p which is what we need
		// since we are starting from index = 0 we start with the largest suffixes
		// at any point we consider the largest suffix and the one before it in the suffix array (sorted order)
		int pi = this->c[i];	// this is the position of suffix[i] in the array p i.e. suffix array
		int j = p[pi - 1];		// this is s[i - 1] i.e. the previous suffix in the suffix array
		// lcp[i] = lcp(s[i..], s[j..])
		while(s[i + k] == s[j + k]) k++;	// k also represents the number of equal characters between the current two suffixes 
		this->lcp[pi] = k;	// longest common prefix between suffix[i] and suffix[i - 1] 
		k = std::max(0, k - 1);	
	}
}
