#include "polynomial.h"
#include <sstream>

using namespace std;

bool test_empty() {
    Polynomial p; // calls default constructor
	if(p.get_coefficient(3)!=0)
		return false;
	if(p.get_coefficient(0)!=0)
		return false;
    return true;
}

bool test_get_set() {
    Polynomial p; // calls default constructor
    p.set_coefficient(3,0);
    p.set_coefficient(2,5);
    p.set_coefficient(5,0);
    
	if(p.get_coefficient(0)!=5)
		return false;
	if(p.get_coefficient(1)!=0)
		return false;
	if(p.get_coefficient(5)!=2)
		return false;
    return true;
}

bool test_copy_cons() {
    Polynomial pt; // calls default constructor
    pt.set_coefficient(3,0);
    pt.set_coefficient(2,5);

    Polynomial p(pt);
	if(p.get_coefficient(0)!=3)
		return false;
	if(p.get_coefficient(1)!=0)
		return false;
	if(p.get_coefficient(5)!=2)
		return false;
	return true;              
}

bool test_add() {
      Polynomial p1; // calls default constructor
    p1.set_coefficient(2,1);
    p1.set_coefficient(1,3);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p3(p1+p2);
	
	if(p3.get_coefficient(1)!=4)
		return false;
	if(p3.get_coefficient(2)!=2)
		return false;
	if(p3.get_coefficient(3)!=1)
		return false;
	return true;
}

bool test_sub() {
    Polynomial p1; // calls default constructor
    p1.set_coefficient(2,1);
    p1.set_coefficient(1,3);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p3(p1-p2);

	if(p3.get_coefficient(1)!=0)
		return false;
	if(p3.get_coefficient(2)!=-2)
		return false;
	if(p3.get_coefficient(3)!=1)
		return false;
	return true;
}

bool test_mul()
{
    Polynomial p1; // calls default constructor
    p1.set_coefficient(2,1);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
    

	Polynomial p3;
	p3.set_coefficient(2,2);
    p3.set_coefficient(2,1);

    p3=p1*p2;

	if(p3.get_coefficient(0)!=0)
		return false;
	if(p3.get_coefficient(1)!=0)
		return false;
	if(p3.get_coefficient(2)!=4)
		return false;
	if(p3.get_coefficient(3)!=4)
		return false;
	return true;
}

bool test_mul2()
{
    Polynomial p1; // calls default constructor
    p1.set_coefficient(2,3);
	p1.set_coefficient(1,2);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p3(p1*p2);

	if(p3.get_coefficient(0)!=0)
		return false;
	if(p3.get_coefficient(1)!=0)
		return false;
	if(p3.get_coefficient(2)!=0)
		return false;
	if(p3.get_coefficient(3)!=2)
		return false;
	if(p3.get_coefficient(4)!=6)
		return false;
	if(p3.get_coefficient(5)!=4)
		return false;
	return true;
}

bool test_getDegree()
{
    Polynomial p1; // calls default constructor
    p1.set_coefficient(2,3);
	p1.set_coefficient(1,2);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p3(p1*p2);

	if(p3.get_degree()!=5)
		return false;
	return true;
		
}

bool test_evaluateAt()
{
    Polynomial p1; // calls default constructor
    p1.set_coefficient(2,3);
	p1.set_coefficient(1,2);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p3(p1*p2);

	if(p3.evaluate_at(1)!=12)
		return false;
	if(p3.evaluate_at(2)!=240)
		return false;
	return true;
		
}

bool test_out()
{
    Polynomial p1; // calls default constructor
    p1.set_coefficient(2,3);
	p1.set_coefficient(1,2);
                
    Polynomial p2;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p3(p1*p2);

	ostringstream oss;

	oss << p3;

	if(strcmp(oss.str().c_str(),"4x^5+6x^4+2x^3")!=0)
		return false;

	Polynomial p4; // calls default constructor
    p1.set_coefficient(2,1);
    p1.set_coefficient(1,3);
                
    Polynomial p5;
    p2.set_coefficient(2,2);
    p2.set_coefficient(2,1);
                
    Polynomial p6(p1-p2);

	ostringstream oss2;

	oss2 << p6;
	
	if(strcmp(oss2.str().c_str(),"x^3-2x^2")!=0)
		return false;

	return true;
}

int main(void)
{
	int ret = 1;
	if(!test_empty())
	{
		cout << "test_empty does not work" << endl;
		ret = -1;
	}
	if(!test_get_set())
	{
		cout << "test_get_set does not work" << endl;
		ret = -2;
	}
	if(!test_copy_cons())
	{
		cout << "test_copy_cons does not work" << endl;
		ret = -3;
	}
	if(!test_add())
	{
		cout << "test_add does not work" << endl;
		ret = -4;
	}
	if(!test_sub())
	{
		cout << "test_sub does not work" << endl;
		ret = -5;
	}
	if(!test_mul())
	{
		cout << "test_mul does not work" << endl;
		ret = -6;
	}
	if(!test_mul2())
	{
		cout << "test_mul2 does not work" << endl;
		ret = -7;
	}
	if(!test_getDegree())
	{
		cout << "test_getDegree does not work" << endl;
		ret = -8;
	}
	if(!test_evaluateAt())
	{
		cout << "test_evaluateAt does not work" << endl;
		ret = -9;
	}
	if(!test_out())
	{
		cout << "test_out does not work" << endl;
		ret = -10;
	}
	system("pause");
	return ret; 
}