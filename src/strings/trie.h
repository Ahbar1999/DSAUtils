#include <iostream>
#include <vector>
#include <string>

class TrieNode {
	private:
		void insert_dfs(TrieNode* curr, int i, std::string& s) {
			if (i == s.size()) return;
			// find a match if exists 
			for (auto& nb: curr->next) {
				if (nb->val == s[i]) {
					curr = nb;
					break;
				}
			}

			if (curr->val != s[i]) {	// match does not exist so insert a new one  
				auto tmp = new TrieNode(s[i], i == s.size() - 1);
				curr->next.push_back(tmp);
				curr = tmp;
			} 
			insert_dfs(curr, i + 1, s); 
		}

		std::string lcp_dfs(TrieNode* curr, int i, std::string& s) {
			if (i == s.size()) return "";
			// find a match if exists 
			for (auto& nb: curr->next) {
				if (nb->val == s[i]) {
					curr = nb;
					break;
				}
			}
			// match does not exist so insert a new 
			if (curr->val != s[i]) return "";
			return s[i] + lcp_dfs(curr, i + 1, s);
		}

	public:
		char val;
		bool term;
		std::vector<TrieNode*> next; 
			
		TrieNode(char val, bool term): val(val), term(term) {
			this->next = std::vector<TrieNode*>();
		}

		void print_trie() {
			// TODO
			std::cout << "Trie gets pretty printed" << std::endl; 
		}

				void insert_str(TrieNode* root, int i, std::string s) {
			this->insert_dfs(root, i, s);	
		}
		
		// return longest commong/matching prefix 
		std::string lcp(TrieNode* root, std::string s) {
			return this->lcp_dfs(root, 0, s);
		}
};

