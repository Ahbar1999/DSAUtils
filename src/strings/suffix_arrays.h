#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class SuffixArrays {
	public:
		// sorted array of suffixes
		SuffixArrays(std::string& s) {
			this->s = s;
			this->s.push_back('$');
			this->n = this->s.size();
			this->p.resize(n);
			this->c.resize(n);	
			this->init();
			this->make_transitions();
		}

		int substring_search(std::string pattern) {
			// each susbtring is a prefix of some suffix
			auto i = *std::lower_bound(this->p.begin(), this->p.end(), pattern, [this](int i, std::string p) {
				return this->s.substr(i, -1) <= p;
			});
			return (this->s.substr(i, pattern.size()) == pattern) ? i : -1;  
		}

	private:
		std::string s;
		int n;
		// p: stores the starting index(rightmost) of a suffix
		// c: stores equivalence classes/labels of the suffixes; 0 <= c[i] < s.size() 
		std::vector<int> p; 
		std::vector<int> c;
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
		void init() {
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

		void make_transitions() {
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

			for (int i = 0; i < n; i++) std::cout << s.substr(p[i], n  -p[i]) << "\n";
		}

};
