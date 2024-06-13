#include <iostream>
#include <vector>
#include <string>

class TrieNode {
	private:
		void insert_dfs(TrieNode* curr, int i, std::string& s); 
		std::string lcp_dfs(TrieNode* curr, int i, std::string& s); 

	public:
		char val;
		bool term;
		std::vector<TrieNode*> next; 
			
		TrieNode(char val, bool term): val(val), term(term) {
			this->next = std::vector<TrieNode*>();
		}

		void print_trie(); 

		void insert_str(TrieNode* root, int i, std::string s);
		
		// return longest commong/matching prefix 
		std::string lcp(TrieNode* root, std::string s);
};

