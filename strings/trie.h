#include <stdio.h>

const TrieNode* root('$', false); 

class TrieNode { 
	char val;
	bool term;
	vector<char> next; 
	
	TrieNode(char val, bool term): val(val), term(term) {
		this->next = vector<char>();
	}

	void print_trie() {
		// TODO
		cout << "Trie gets pretty printed" << endl; 
	}

	void insert_dfs(TrieNode* curr, int i, string& s) {
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

	string lcp_dfs(TrieNode* curr, int i, string& s) {
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

	void insert_str(int i, string s) {
		this->insert_dfs(root, i, s);	
	}
	
	// return longest commong/matching prefix 
	string lcp(string s) {
		return this->lcp_dfs(root, 0, s);
	}
}

