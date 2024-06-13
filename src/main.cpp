#include <iostream>
#include "./dsa/include/trie.h"
// #include "./dsa/include/suffix_arrays.h"


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
	test_trie();
	/*
	std::string s = "ababba";
	std::cout << s << std::endl;
	std::cout << std::endl;
	auto sa = SuffixArrays(s);
	std::cout << "babb found at: " << sa.substring_search("babb") << std::endl;
	std::cout << "babbb fount at: " << sa.substring_search("babbb") << std::endl;
	std::cout << "ba fount at: " << sa.substring_search("ba") << std::endl;
	*/
	
	return 0;
};
