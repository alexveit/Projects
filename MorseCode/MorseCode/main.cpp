#include <iostream>
#include "morse_tree.h"

using namespace std;

bool is_valid_args(int argc, char* argv[], int *p)
{
	if(argc < 3)
	{
		cout << "Not enough command line arguments" << endl;
		return false;
	}
	if(argc > 3)
	{
		cout << "To many command line arguments" << endl;
		return false;
	}
	string param = argv[1];
	if(!(param.compare("-d") == 0))
	{
		if(!(param.compare("-e") == 0))
		{
			cout << "Invalid parameter " << param << endl;
			return false;
		}
		else
			*p = 1;
	}
	else
		*p = 2;
	return true;
}

int main(int argc, char* argv[])
{
	int ret = 0;
	int param = 0;
	if(!is_valid_args(argc, argv,&param))
	{
		ret = 1;
	}

	morse_tree mc;

	switch(param)
	{
	case 1:
		cout << mc.encode(argv[2]);
		break;
	case 2:
		cout << mc.decode(argv[2]);
		break;
	}

	system("pause");
	return ret;
}
