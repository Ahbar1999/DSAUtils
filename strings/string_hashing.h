#include <stdio.h>

class Hashed_string() {
	const int A;
	const int B;
	const string s;
	vector<int> p;
	vector<int> h;

	Hashed_string(int A = 31, int B = (9 << 10), string s): A(A), B(B), s(s) {
		this->p.resize(s.size());
		this->init_p();
		this->h.resize(s.size());
		this->init_h();
	}
	
	void init_h() {
		this->h[0] = s[0];
		for (int i = 1; i < this->h.size(); i++) this->h[i] = (this->h[i - 1] * this->A + (this->s[i] - 'a' + 1)) % B;   
	}
	
	void init_p() {
		this->p[0] = 1;
		for (int i = 1; i < this->p.size(); i++) this->p[i] = (this->p[i - 1] * this->A) % B;
	}

	int get_hash(int i, int j) {
		return (this->h[j] - this->h[i - 1] * this->p[j - i + 1]) % B;
	}
}
