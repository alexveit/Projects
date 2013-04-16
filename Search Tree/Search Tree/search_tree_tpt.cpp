#include <iostream>

template<typename T>
class tree {

	struct tree_node {
		T data;
		tree_node *left, *right;		
		tree_node(T d, tree_node *l, tree_node *r):data(d),left(l),right(r){}
	};

	tree_node *root;

	T greates_of_these_two(T a, T b) { return (a>b ? a : b); }
	
	T est(tree_node *tn, bool small)
	{
		if(tn == nullptr)
			return 0;
		
		if(small)
		{
			if(tn->left == nullptr)
				return tn->data;
				
			return est(tn->left, true);	
		}
		
		if(tn->right == nullptr)
			return tn->data;
		
		return est(tn->right, false);		
	}
	
	T sum(tree_node *tn)
	{
		if(tn == nullptr)
			return 0;
		
		return tn->data + sum(tn->left) + sum(tn->right);
	}

	void del_tree(tree_node* tn)
	{
		if(tn==nullptr)
			return;
			
		del_tree(tn->left);
		del_tree(tn->right);
		delete tn;
	}	

public:
	void print_spaces(int n) { 
		for(int i=0; i<n; ++i)
			std::cout << " ";
	}	
	
	tree():root(nullptr){}
	
	tree(const T& d) { root=new tree_node(d,nullptr,nullptr); }

	/* for you to do */
	// returns the smallest value in tree
	T smallest() { return est(root,true); }
	
	// returns the largest value in tree
	T largest() { return est(root,false); }
	
	// returns the sum of all elements in tree, 0 if empty
	T sum() { return sum(root); }

	// destructor, call delete on all nodes
	~tree()
	{
		del_tree(root);
	}
	
	// copy constructor
	tree(const tree &other)
	{
	}
	
	// assignment operator
	tree& operator=(const tree&other)
	{
		return *this;
	}

	/* you're done now */
	void pre_print(tree_node*r,int level) {
		if(r==nullptr)
			return;
		print_spaces(level*3);
		std::cout << r->data << std::endl;
		if(r->right && ! r->left) {
			print_spaces(level*3+3);
			std::cout << "no left"<< std::endl;
		}
		pre_print(r->left,level+1);
		if(!r->right && r->left) {
			print_spaces(level*3+3);
			std::cout << "no right" << std::endl;			
		}
		pre_print(r->right,level+1);
	}
	
	void pre_print(void) {
		pre_print(root,0);
	}

	bool contains(tree_node* r, const T& val) const {
		if(r==nullptr)
			return false;
		if(r->data==val)
			return true;
		if(r->data>val)
			return contains(r->left,val);
		else
			return contains(r->right,val);
	}
	
	void insert(tree_node*r, const T&val) {
		if(r->data==val)
			return;
		if(r->data > val) {
			if(r->left==nullptr) 
				r->left= new tree_node(val,nullptr,nullptr);
			else
				insert(r->left,val);
		}
		else {
			if(r->right==nullptr) 
				r->right= new tree_node(val,nullptr,nullptr);
			else
				insert(r->right,val);
		}
	}

	void insert(const T&val) {
		if(root==nullptr)
			root=new tree_node(val,nullptr,nullptr);
		else
			insert(root,val);
	}

	bool contains(const T& value) const { return contains(root,value); }

};
