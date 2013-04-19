#include <fstream>
#include <sstream>
#include "morse_tree.h"

using namespace std;

morse_tree::Data::Data(string d)
{
	_letter_s = d[0];
	_letter_b = d[1];
	_code = &d[2];
}

morse_tree::Data& morse_tree::Data::operator=(const Data &d)
{
	_letter_s = d._letter_s;
	_letter_b = d._letter_b;
	_code = d._code;
	return *this;
}

morse_tree::Node::Node(Data d, Node *left_dot, Node *right_line)
{
	_data = d;
	_left_dot = left_dot;
	_right_line = right_line;
}

void morse_tree::insert(Node *n, int pos, const Data &d)
{
	if(d._code[pos] == '.')
	{
		if(!n->_left_dot)
			n->_left_dot = new Node(d,nullptr,nullptr);
		else
			insert(n->_left_dot,pos+1,d);
	}
	else
	{
		if(!n->_right_line)
			n->_right_line = new Node(d,nullptr,nullptr);
		else
			insert(n->_right_line,pos+1,d);
	}
}

char morse_tree::get_char(Node *n, const int pos, const string code)
{
	if(n == nullptr)
		return '0';

	if(n->_data._code.compare(code) == 0)
		return n->_data._letter_s;

	if(code[pos] == '.')
		return get_char(n->_left_dot,pos+1,code);

	return get_char(n->_right_line,pos+1,code);;
}

string morse_tree::get_code(Node *n, const char letter, bool *found)
{
	if(n == nullptr)
		return "";
	if(n->_data._letter_s == letter || n->_data._letter_b == letter)
	{
		*found = true;
		return n->_data._code;
	}

	string temp = get_code(n->_left_dot,letter,found);
	if(!*found)
	{
		temp = get_code(n->_right_line,letter,found);
	}

	return temp;
}

void morse_tree::load_tree()
{
	string line;
	ifstream myfile ("morse-code.txt");
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline(myfile,line);
			insert(&_root,0,Data(line));
		}
		myfile.close();
	}

}

morse_tree::morse_tree()
{
	load_tree();
}

string morse_tree::decode(string input)
{
	string code;
	ostringstream oss;
	istringstream iss(input);
	
	while ( iss.good() )
	{
		iss >> code;
		oss << get_char(&_root,0,code);
	}
	return oss.str();
}

string morse_tree::encode(string input)
{
	ostringstream oss;
	bool f = false;
	for(unsigned i = 0; i < input.size(); i++)
	{
		oss << get_code(&_root,input[i],&f);
		if(f)
			oss << " ";
		f = false;
	}
	return oss.str();
}