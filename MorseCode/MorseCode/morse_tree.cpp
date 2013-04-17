#include "morse_tree.h"

using namespace std;

morse_tree::Data::Data()
{
	_letter = 0;
	for(int i = 0; i < CODE_SIZE; i++)
		_code[i] = 0;
}

morse_tree::Data::Data(char l, char c[])
{
	_letter = l;
	for(int i = 0; i < CODE_SIZE; i++)
		_code[i] = c[i];
}

morse_tree::Data& morse_tree::Data::operator=(const Data &d)
{
	_letter = d._letter;
	for(int i = 0; i < 4; i++)
		_code[i] = d._code[i];
	return *this;
}

morse_tree::Node::Node(Data d, Node *left_dot, Node *right_line)
{
	_data = d;
	_left_dot = left_dot;
	_right_line = right_line;
}

void morse_tree::insert(Node *n, const Data &d)
{
}

void morse_tree::insert(const Data &d)
{
}

void morse_tree::load_tree()
{

}

morse_tree::morse_tree()
{
	load_tree();
}

string morse_tree::decode(string input)
{
	return input;
}

string morse_tree::encode(string input)
{
	return input;
}