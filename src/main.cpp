#include <iostream>
#include "./strings/trie.h"
#include "./strings/suffix_arrays.h"


void test_trie() {
	auto root = TrieNode('$', false);
	root.print_trie();
}

void test_fenwick_tree() { 

} 

void test_segment_tree() {

}

void test_suffix_arrays() {

}

int main() {
	std::string s = "ababba";
	std::cout << s << std::endl;
	std::cout << std::endl;
	auto sa = SuffixArrays(s);
	
	return 0;
};
