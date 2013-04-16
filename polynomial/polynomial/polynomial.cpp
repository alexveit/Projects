#include "polynomial.h"
#include <iostream>

using namespace std;

Polynomial::Ret& Polynomial::Ret::operator=(const Ret &ret)
{
	contains = ret.contains;
	node = ret.node;
	return *this;
}

Polynomial::Ret Polynomial::get_if_contains(int d) const
{
	Ret ret;
	for(PolyNode *curr = firstTerm; curr != nullptr; curr = curr->next)
	{
		if(curr->degree == d)
		{
			ret.contains = true;
			ret.node = curr;
		}
	}
	return ret;
}

Polynomial::PolyNode* Polynomial::get_previous_node(PolyNode *node)
{
	for(PolyNode *curr = firstTerm; curr != nullptr; curr = curr->next)
	{
		if(curr->next == node)
			return curr;
	}
	return nullptr;
}

Polynomial::PolyNode* Polynomial::get_node_of_previous_degree(int d)
{
	for(PolyNode *curr = firstTerm; curr != nullptr; curr = curr->next)
	{
		if(curr->next == nullptr && curr->degree > d)
			return curr;
		if(curr->degree > d && curr->next->degree < d)
			return curr;
	}
	return nullptr;
}

void Polynomial::set_coefficient(int c, int d)
{
	if(c == 0)
	{
		Ret ret = get_if_contains(d);
		if(ret.contains)
		{
			PolyNode *prev = get_previous_node(ret.node);
			prev->next = ret.node->next;
			delete ret.node;
		}
		return;
	}
	
	Ret ret = get_if_contains(d);
	if(ret.contains)
	{
		ret.node->degree = d;
		ret.node->coefficient = c;
		return;
	}
	
	if(firstTerm == nullptr)
		firstTerm = new PolyNode(c,d,nullptr);
	else
	{
		PolyNode *prev = get_node_of_previous_degree(d);
		if(prev != nullptr)
			prev->next = new PolyNode(c,d,prev->next);
		else
			firstTerm = new PolyNode(c,d,firstTerm);
	}
}

int Polynomial::get_coefficient(int d) const
{
	Ret ret = get_if_contains(d);
	if(ret.contains)
		return ret.node->coefficient;
	return 0;
}

int Polynomial::evaluate_at(int x) const
{
	int result = 0;
	for(PolyNode *curr = firstTerm; curr != nullptr; curr = curr->next)
	{
		int var = 1;
		for(int i = 0; i < curr->degree; i++)
		{
			var *= x;
		}
		result += curr->coefficient*var;
	}
	return result;
}

int Polynomial::get_degree() const
{
	if(firstTerm == nullptr)
		return 0;
	return firstTerm->degree;
}

void Polynomial::del_list(PolyNode* n)
{
	if(n==0)
		return;
			
	del_list(n->next);
	delete n;
}	

Polynomial::~Polynomial()
{
	del_list(firstTerm);
}

void Polynomial::push_back(PolyNode *n)
{
	if(firstTerm == nullptr)
	{
		firstTerm = new PolyNode(n->coefficient,n->degree,nullptr);
		return;
	}
	PolyNode* last_ptr;
	for(last_ptr=firstTerm;last_ptr->next != nullptr; last_ptr=last_ptr->next);
	
	last_ptr->next=new PolyNode(n->coefficient,n->degree,nullptr);
}

Polynomial::Polynomial(const Polynomial& p)
{
	firstTerm = nullptr;
	for(PolyNode *current_other = p.firstTerm;
		current_other != nullptr;
		current_other = current_other->next)
	{
		push_back(current_other);
	}
}

Polynomial& Polynomial::operator=(const Polynomial& other)
{
	del_list(firstTerm);
	firstTerm = nullptr;
	for(PolyNode *curr_other = other.firstTerm; curr_other != nullptr; curr_other = curr_other->next)
	{
		push_back(curr_other);
	}
	return *this;
}

ostream& operator<<(ostream& o, const Polynomial& p)
{
	for(Polynomial::PolyNode *curr = p.firstTerm; curr != nullptr; curr = curr->next)
	{

		if(curr->coefficient == 1)
		{
			if(curr == p.firstTerm)
				o << "x^";
			else
				o << "+x^";
		}
		else if(curr->coefficient == -1)
			o << "-x^";
		else if(curr->coefficient > 0)
		{
			if(curr == p.firstTerm)
				o << curr->coefficient << "x^";
			else
				o << "+" << curr->coefficient << "x^";
		}
		else
			o << curr->coefficient << "x^";

		o << curr->degree;
	}
	return o;
}
     
void Polynomial::remove_zeros_coeffs()
{
	for(Polynomial::PolyNode *curr = firstTerm; curr != nullptr; curr = curr->next)
	{
		if(curr->next != nullptr && curr->next->coefficient == 0)
		{
			Polynomial::PolyNode *next = curr->next;
			curr->next = next->next;
			delete next;
		}
	}
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial retp(p1);
	for(Polynomial::PolyNode *curr = retp.firstTerm, *p2curr = p2.firstTerm; curr != nullptr;)
	{
		if(curr->degree == p2curr->degree)
		{
			curr->coefficient += p2curr->coefficient;
			curr = curr->next;
			p2curr = p2curr->next;
		}
		else if(curr->degree > p2curr->degree)
		{
			retp.set_coefficient(p2curr->coefficient,p2curr->degree);
			curr = curr->next->next;
			p2curr = p2curr->next;
		}
		else
		{
			retp.set_coefficient(p2curr->coefficient,p2curr->degree);
			curr = curr->next;
			p2curr = p2curr->next->next;
		}
	}
	retp.remove_zeros_coeffs();
	return retp;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial retp(p1);
	for(Polynomial::PolyNode *curr = retp.firstTerm, *p2curr = p2.firstTerm; curr != nullptr;)
	{
		if(curr->degree == p2curr->degree)
		{
			curr->coefficient -= p2curr->coefficient;
			curr = curr->next;
			p2curr = p2curr->next;
		}
		else if(curr->degree > p2curr->degree)
		{
			retp.set_coefficient(p2curr->coefficient*(-1),p2curr->degree);
			curr = curr->next->next;
			p2curr = p2curr->next;
		}
		else
		{
			retp.set_coefficient(p2curr->coefficient*(-1),p2curr->degree);
			curr = curr->next;
			p2curr = p2curr->next->next;
		}
	}
	retp.remove_zeros_coeffs();
	return retp;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial ret;
	for(Polynomial::PolyNode *p1curr = p1.firstTerm; p1curr != nullptr; p1curr = p1curr->next)
	{
		for(Polynomial::PolyNode *p2curr = p2.firstTerm; p2curr != nullptr; p2curr = p2curr->next)
		{
			Polynomial::PolyNode pnode(p1curr->coefficient * p2curr->coefficient,p1curr->degree+p2curr->degree,nullptr);
			ret.push_back(&pnode);
		}
	}
	for(Polynomial::PolyNode *curr = ret.firstTerm; curr != nullptr; curr = curr->next)
	{
		if(curr->next != nullptr && curr->degree == curr->next->degree)
		{
			Polynomial::PolyNode *next = curr->next;
			curr->coefficient += next->coefficient;
			curr->next = next->next;
			delete next;
		}
	}
	ret.remove_zeros_coeffs();
	return ret;
}