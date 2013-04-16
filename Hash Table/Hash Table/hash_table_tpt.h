#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <iostream>

// interface
template <typename K, typename V>
struct AbstractMap {
	virtual void set(K key, V value)=0;
	virtual bool contains(K key)=0;
	virtual V find(K key) =0;
	virtual void remove(K key) =0;
	virtual unsigned size(void) const =0;
};

template<class K, class V>
struct myPair {
	K key;
	V value;
	myPair(K k, V v): key(k), value(v) {}
	myPair& operator=(const myPair& other)
	{
		key = other.key;
		value = other.value;
		return *this;
	}
};

#include <vector>
#include <functional>

template <typename K, typename V>
class VectorHashTable : AbstractMap<K,V>{
private:
	std::function<unsigned(K)> hash_func;
	std::vector< std::vector<myPair<K,V> > > _table; 
	unsigned _size;

	unsigned hash_mod(unsigned hash) { return hash % _table.size();}
	
	void expand_and_disperse_data()
	{
		std::vector< std::vector<myPair<K,V> > > temp(_table);

		for(unsigned i = 0; i < _table.size(); i++)
		{
			_table[i].clear();
		}
		_table.resize(_table.size()*2);

		for(unsigned i = 0; i < temp.size(); i++)
		{
			for(unsigned j = 0; j < temp[i].size(); j++)
			{
				set(temp[i][j].key,temp[i][j].value);
			}
		}
		
	}
	
	void expand_if_necessary()
	{
		unsigned buckets_with_vals = 0;
		unsigned table_size = _table.size();
		unsigned half_table_size = table_size/2;
		for(unsigned i = 0; i < table_size; i++)
		{
			if(buckets_with_vals == half_table_size)
			{
				
				expand_and_disperse_data();
				return;
			}
			if(_table[i].size() > 0)
				buckets_with_vals++;
		}
	}
	
public:
	VectorHashTable(std::function<unsigned(K)>func):hash_func(func), _table(10),_size(10){}
	
	virtual void set(K key, V value) {
		// YOU need to change this so that if the table is >50% full , you grow it to twice its size
		
		expand_if_necessary();
		
		unsigned bucket=hash_mod(hash_func(key)); // we know that it goes in that bucket
		
//		cout << "bucket=" << bucket << endl;
		for(myPair<K,V> entry : _table[bucket]) {
			if(entry.key==key) {
				entry.value=value;
				return;
			}
		}
		// entry wasn't there
		++_size;
		_table[bucket].push_back(myPair<K,V>(key,value));
	}
	
	virtual bool contains(K key) {
		unsigned bucket=hash_mod(hash_func(key)); // we know that it goes in that bucket
		for(myPair<K,V> entry : _table[bucket]) {
			if(entry.key==key) 
				return true;
		}		
		return false;
	}
	
	virtual V find(K key) {
		unsigned bucket=hash_mod(hash_func(key)); // we know that it goes in that bucket
		for(myPair<K,V> entry : _table[bucket]) {
			if(entry.key==key) 
				return entry.value;
		}		
		// for now
		return V();
	};
	
	// you need to implement this
	virtual void remove(K key)
	{
		unsigned bucket = hash_mod(hash_func(key));
		for(unsigned i = 0; i < _table[bucket].size(); i++)
		{
			if(_table[bucket][i].key == key)
			{
				_table[bucket].erase(_table[bucket].begin()+i);
				break;
			}
		}
	}

	virtual unsigned size(void) const {return _size;};
	
};

#endif
