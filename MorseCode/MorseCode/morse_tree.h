#ifndef _VEIT_MORSE_TREE_
#define	_VEIT_MORSE_TREE_

#include <string>

class morse_tree
{
	struct Data
	{
	#define CODE_SIZE	5

		char _letter;
		char _code[CODE_SIZE];

		Data();

		Data(char l, char c[]);

		Data& operator=(const Data &d);
	};

	struct Node
	{
		Data _data;
		Node *_left_dot, *_right_line;

		Node(Data d, Node *left_dot, Node *right_line);
	};

	Node *_root;

	void insert(const Data &d);

	void insert(Node *n, const Data &d);

	void load_tree();

public:

	morse_tree();

	std::string decode(std::string input);

	std::string encode(std::string input);	
};

#endif