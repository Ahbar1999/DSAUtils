#include <stdio.h>
#include <vector>
#include <string>

class Hashed_string {
	private:
		std::vector<int> p;
		std::vector<int> h;
		void init_h();
		void init_p(); 


	public:
		const int A;
		const int B;
		const std::string s;
		Hashed_string(std::string s, int A = 31, int B = (9 << 10)): A(A), B(B), s(s) {
			this->p.resize(s.size());
			this->init_p();
			this->h.resize(s.size());
			this->init_h();
		}
		
		int get_hash(int i, int j); 
};
