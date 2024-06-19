#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class SuffixArrays {
	
	public:
		// sorted array of suffixes
		SuffixArrays(std::string& s) {
			// std::cout << "GOT STRING: " << s << std::endl; 
			this->s = s;
			this->s.push_back('$');

			// std::cout << "APPENDED SENTINEL CHARACTER: " << this->s << std::endl; 
			this->n = this->s.size();
			this->p.resize(this->n);
			this->c.resize(this->n);	
			this->lcp.resize(this->n);

			this->init();
			this->make_transitions();
			this->build_lcp();
			std::cout << "lcp[i] " << "p[i] " << "suffix[i]" << std::endl;
			for (int i = 0; i < this->n; i++) {
				std::cout << this->lcp[i] << " " << this->p[i] << " " << this->s.substr(this->p[i], this->n  -this->p[i]) << "\n";
			}
		}

		int substring_search(std::string pattern);
		std::string find_lcp(int i, int j);
		int cnt_unique_substrs();
		std::string longest_common_substr();	// expects an object on composite strings 

	private: 
		// p: stores the starting index(rightmost) of a suffix
		// c: stores equivalence classes/labels of the suffixes; 0 <= c[i] < s.size()
		std::string s;
		int n;	// size of s, also total number of suffixes
		std::vector<int> p, c, lcp;  
		void init();

		void make_transitions();
		
		void build_lcp(); 
};
