#include "../include/string_hashing.h"

// precalculate hashes of prefixes of string s
// h(s[i..j]) = h(s[..j]) - h(s[..i])
// to make compuation faster multimply h(s[..i]) p[j - i + 1] to make the base same 
void Hashed_string::init_h() {
	this->h[0] = s[0];
	for (int i = 1; i < this->h.size(); i++) this->h[i] = (this->h[i - 1] * this->A + (this->s[i] - 'a' + 1)) % B;   
}

// precalculating powers of 2	
void Hashed_string::init_p() {
	this->p[0] = 1;
	for (int i = 1; i < this->p.size(); i++) this->p[i] = (this->p[i - 1] * this->A) % B;
}

int Hashed_string::get_hash(int i, int j) {
	// multiplying h[i - 1] by p[j - i + 1] allows it to be shifted to the same powers of h[j] 
	// which allows for easy comparison of integers without any need for division 
	return (this->h[j] - this->h[i - 1] * this->p[j - i + 1]) % B;
}

std::vector<int> Hashed_string::RK_Matcher(std::string& p) {
	std::vector<int> occurances;
	int P = p.size();

	// hash of the pattern
	long long h_p  =0;
	for (int i = 0; i < P; i++) {
		h_p = (h_p + (p[i] - 'a' + 1) * this->p[i]) % B;
	}
	// match all length p substrings of s with our pattern 
	for (int i =0; i + P - 1 < this->s.size(); i++) {
		// s[i..i + P - 1]
		long long curr_h = (this->h[i + P] + this->B - h[i] * this->p[P]) % B;	// modular arithmetic
		if (curr_h == (h_p * this->p[i]) % this->B) occurances.push_back(i);	// h_p times this->p[i] so the base is same
																				// for curr_h which has base p[i + P]
																				// and h_p which always has base p[P] 
	} 

	return occurances; 
}