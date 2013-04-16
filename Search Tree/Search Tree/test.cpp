
#include <stdexcept>
#include "search_tree_tpt.cpp"

using namespace std;

tree<int> it;

bool test_smallest() {
	if(it.smallest()!=8)
		return false;
	it.insert(5);
	if(it.smallest()!=5)
		return false;
	return true;
}

bool test_largest() {
	if(it.largest()!=21)
		return false;
	it.insert(50);
	if(it.largest()!=50)
		return false;
	return true;
}
	
bool test_sum() {
	if(it.sum()!=140)
		return false;
	it.insert(15);
	if(it.sum()!=155)
		return false;
	return true;
}
	
bool test_copy() {
	tree<int> t2(it);

	if(t2.sum()!=85)
		return false;
	t2.insert(50);
	if(it.largest()!=21)
		return false;
	if(t2.largest()!=50)
		return false;
	return true;
}
		
bool test_assignment() {
	tree<int> t2;
		
	t2.insert(-1);
		
	t2= it;

	if(t2.sum()!=85)
		return false;
	t2.insert(50);

	if(it.largest()!=21)
		return false;
	if(t2.largest()!=50)
		return false;
	return true;

}

int main() {
	it.insert(10);
	it.insert(8);
	it.insert(12);
	it.insert(18);
	it.insert(16);
	it.insert(21);

	int ret = 0;

	if(!test_smallest())
	{
		cout << "test_smallest" << endl;
		ret += -1;
	}

	if(!test_largest())
	{
		cout << "test_largest" << endl;
		ret += -2;
	}

	if(!test_sum())
	{
		cout << "test_sum" << endl;
		ret += -3;
	}

	system("pause");

	return ret;
}
