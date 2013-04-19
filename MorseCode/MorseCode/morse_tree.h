#ifndef _VEIT_MORSE_TREE_
#define	_VEIT_MORSE_TREE_

#include <string>

class morse_tree
{
	struct Data
	{
		char _letter_s;
		char _letter_b;
		std::string _code;

		Data() : _letter_s(0), _letter_b(0), _code("") {}

		Data(std::string d);

		Data& operator=(const Data &d);
	};

	struct Node
	{
		Data _data;
		Node *_left_dot, *_right_line;
		Node() : _left_dot(nullptr), _right_line(nullptr) {}
		Node(Data d, Node *left_dot, Node *right_line);
	};

	Node _root;

	char get_char(Node *n, const int pos, const std::string code);

	std::string get_code(Node *n, const char letter, bool *found);

	void insert(Node *n, int pos, const Data &d);

	void load_tree();

public:

	morse_tree();

	std::string decode(std::string input);

	std::string encode(std::string input);	
};

#endif