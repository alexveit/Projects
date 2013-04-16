#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <iostream>

class Polynomial {
	struct PolyNode {
			int coefficient, degree;
			struct PolyNode* next;
			PolyNode(int c, int d, PolyNode* n): coefficient(c),degree(d),next(n){}
	};
	PolyNode *firstTerm;
	
	struct Ret
	{
		bool contains;
		PolyNode *node;
		Ret() : contains(false), node(nullptr) {}
		Ret& operator=(const Ret &ret);
	};
	
	void remove_zeros_coeffs();


	void del_list(PolyNode* n);

	Ret get_if_contains(int d) const;
	
	PolyNode* get_previous_node(PolyNode *node);
	
	PolyNode* get_node_of_previous_degree(int d);
	
	void push_back(PolyNode *n);
		
public:
	Polynomial() { firstTerm=nullptr; }
	// sets the coefficient for the term with degree d to be c
	// notice a node is created if one for that degree doesn't exist, and
	// that it is destroyed if the coefficient is 0
	void set_coefficient(int c, int d);
	
	// returns the coefficient for the term with degree d
	// zero if it doesn't exist
	int get_coefficient(int d) const;
	
	// returns the result of evaluating the polynomial at x
	int evaluate_at(int x)const ;
	
	// returns the degree of the polynomial
	// which is the highest degree of any term
	int get_degree() const;
	
	// destructor, make sure that all memory is returned correctly
	~Polynomial();
	
	// copy constructor
	Polynomial(const Polynomial& p) ;
	// assignment operator
	Polynomial& operator=(const Polynomial& other); 
	
	// prints the polynomial to the output stream o
	// please use like:   3x^2+5   
	// for the first term, a sign gets printed only if negative
	// if the term has a coefficient of 1 (or -1) the coefficient doesn't get printed 
	// there shouldn't be any terms with zero coefficient, but at least they shouldn't be printed
	// terms must be printed in descending order of degree
	friend std::ostream& operator<<(std::ostream& o, const Polynomial& p);
			
	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);    
};

std::ostream& operator<<(std::ostream& o, const Polynomial& p);
                
Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

#endif