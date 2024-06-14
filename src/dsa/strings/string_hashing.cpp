#include "../include/string_hashing.h"

void Hashed_string::init_h() {
	this->h[0] = s[0];
	for (int i = 1; i < this->h.size(); i++) this->h[i] = (this->h[i - 1] * this->A + (this->s[i] - 'a' + 1)) % B;   
}
	
void Hashed_string::init_p() {
	this->p[0] = 1;
	for (int i = 1; i < this->p.size(); i++) this->p[i] = (this->p[i - 1] * this->A) % B;
}

int Hashed_string::get_hash(int i, int j) {
	return (this->h[j] - this->h[i - 1] * this->p[j - i + 1]) % B;
}
