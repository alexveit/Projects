#include "hash_table_tpt.h"

#include<string>
#include<iostream>

using namespace std;

unsigned hash_string(string s)
{
	return s[0];
}

int main(void)
{
	VectorHashTable<string,string> states(hash_string);
	states.set("GA","Georgia");
	states.set("FL","Florida");
	states.set("AL","Alabama");
	states.set("AK","Alaska");
	states.set("AZ","Arizona");
	states.set("AR","Arkansas");
	states.set("CA","California");
	states.set("CO","Colorado");
	states.set("CT","Connecticut");
	states.set("DE","Delaware");
	states.set("DC","District of Columbia");
	states.set("HI","Hawaii");
	states.set("ID","Idaho");
	states.set("IL","Illinois");
	states.set("IN","Indiana");
	states.set("IA","Iowa");
	
	cout << boolalpha << states.contains("GA") << endl;
	cout << states.contains("YUC") << endl;
	
	cout << states.find("GA") << endl;
	
	states.remove("GA");
	
	cout << states.contains("GA") << endl;

	system("pause");
	
}

