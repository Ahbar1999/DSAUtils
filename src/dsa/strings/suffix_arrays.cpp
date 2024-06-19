#include <vector>
#include <string>
#include <algorithm>
// #include <iostream>
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


	std::cout << "in init()" << std::endl;	
	// k == 0 phase
	std::vector<std::pair<char, int>> a(this->n);
	for (int i =0; i < this->n; i++) a[i] = {s[i], i};
	std::sort(a.begin(), a.end());
	// now logically all suffixes(size 1) are sorted
	// extract sorted indices
	for (int i =0; i  < this->n; i++) p[i] = a[i].second;
	// assign the first suffix a number
	c[p[0]] = 0;
	// now assign all the different suffixes different labels/classes	
	for (int i = 1; i < this->n; i++) c[p[i]] = c[p[i - 1]] + !(a[i].first == a[i - 1].first);
}

void SuffixArrays::make_transitions() {

	std::cout << "in make_transitions()" << std::endl;	
	// before calling this function\
	// we must have called init function which sets up the p and c arrays
	int k =0;
	// do till (half + half ==) whole size  
	while ((1 << k) < this->n) {
		// k -> k + 1; the length of suffixes doubles every iteration
		// labels of left and right parts of new suffix of size 2^k and its index which is same as previous
		// because we are only appending to the previous strings
		std::vector<std::pair<std::pair<int, int>, int>> a(n);
		for (int i = 0; i < this->n; i++) {
			// {left string's label, right string's label, current index}
			a[i] = {{c[i], c[(i + (1 << k)) % this->n]}, i};
		}
		// radix_sort(a);	// with this step total complexity is O(logn * n)
		sort(a.begin(), a.end());	// total complexity = O(logn * nlogn)
		for (int i =0; i  < this->n; i++) p[i] = a[i].second;
		// assign the first suffix a number
		c[p[0]] = 0;
		// now assign all the different suffixes different labels/classes	
		// note that now a[i].first is actually a pair which together represents a new eq class
		for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + !(a[i].first == a[i - 1].first);
		k++;
	}
}

int SuffixArrays::substring_search(std::string pattern) {

	std::cout << "in substring_search()" << std::endl;	
	// each susbtring is a prefix of some suffix
	auto i = *std::lower_bound(this->p.begin(), this->p.end(), pattern, [this](int i, std::string p) {
		return this->s.substr(i, -1) <= p;
	});
	return (this->s.substr(i, pattern.size()) == pattern) ? i : -1;  
}

void SuffixArrays::build_lcp() {
	std::cout << "in build_lcp()" << std::endl;
	int k = 0;	// character to skip during comparison of current two suffixes
	// lcp of two consecutive suffixes, s[i] and s[i - 1]
	for (int i = 0; i < this->n - 1; i++) {
		// std::cout << i << ", ";
		// we need position of each suffix in the suffix array
		// we have p[i] which gives a suffix for each position
		// array c contains **inverse permutation** of p which is what we need
		// since we are starting from index = 0 we start with the largest suffixes
		// at any point we consider the largest suffix and the one before it in the suffix array (sorted order)
		int pi = this->c[i];	// this is the position of suffix[i] in the array p i.e. suffix array
		int j = this->p[pi - 1];		// this is s[i - 1] i.e. the previous suffix in the suffix array
		// lcp[i] = lcp(s[i..], s[j..])
		while(i + k < this->n && j + k < this->n  && this->s[i + k] == this->s[j + k]) k++;	// k also represents the number of equal characters between the current two suffixes
		
		// while(s.at(i + k) == s.at(j + k)) k++; // using at() method helps print out of bounds errors	
		// std::cout << k << std::endl;
		this->lcp[pi] = k;	// longest common prefix between suffix[i] and suffix[i - 1] 
		k = std::max(0, k - 1);	
	}
}

// find lcp between 2 suffix[i] and suffix[j] in the suffix array 
std::string SuffixArrays::find_lcp(int i, int j) {
	std::cout << "in find_lcp()" << std::endl;	
	return this->s.substr(s[i], *std::min_element(this->lcp.begin() + i, this->lcp.begin() + j)); 
}

int SuffixArrays::cnt_unique_substrs() {

	std::cout << "in cnt_unique_substrs()" << std::endl;	
	int cnt = 0;
	for (int i =0; i < this->n; i++) {
		// the second -1 is to account for endmarker $ character
		cnt += (s.substr(p[i], -1).size() - 1) - lcp[i];
	}
	
	return cnt;
}

std::string SuffixArrays::longest_common_substr() {
	// call constructor and other functions on 
	// concatenation of s1 and s2 like: s#s2
	// < class(0/1), p[i]>
	std::cout << "in longest_common_substr()" << std::endl;	
	std::vector<std::pair<bool, int>> s_p;
	for (int i =0; i < this->n; i++){
		s_p.push_back({this->s.substr(this->p[i], this->n - this->p[i]).find('#') == std::string::npos, this->p[i]});
	}	
	// we need to store <lcp size, p[i]>
	std::pair<int, int> max_lcp = {0, 0};
	for(int i = 0; i < this->n; i++) {
		if (i > 0 && s_p[i].first != s_p[i - 1].first) max_lcp = std::max(std::make_pair(this->lcp[i], s_p[i].second), max_lcp);
	}
	return this->s.substr(max_lcp.second, max_lcp.first);
}



