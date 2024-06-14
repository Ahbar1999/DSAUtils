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

		int substring_search(std::string pattern);

	private:
		std::string s;
		int n;
		// p: stores the starting index(rightmost) of a suffix
		// c: stores equivalence classes/labels of the suffixes; 0 <= c[i] < s.size() 
		std::vector<int> p, c, lcp;  
		void init();

		void make_transitions();
		
		void build_lcp(); 
};
