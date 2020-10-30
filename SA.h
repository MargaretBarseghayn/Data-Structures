#pragma once
class SA
{
	struct Node {
		int*	base_;
		int		size_;
		Node*	next_;
		Node(int* base = 0, int size = 0, Node* next = 0) :
			base_(base), size_(size), next_(next) {}
		~Node() { delete[]base_; }
	};

	struct Position {
		Node*	ptr_;
		int		index_;
		Position(Node* ptr = 0, int index = -1) : ptr_(ptr), index_(index) {}
	};

	//AUXILIARY FUNCTIONS
	//returns the index of the key found (or -1 if there is no such key in the array)  
	static	int			binarySearch(int* base, int size, int key);

	//merges two sorted arrays of the same size and returns the location of the resulting double-sized array 
	static	int*		merge(int* first, int* second, int size);

	//returns a pair (node, index) (or (0, -1) if there is no such key in the structure) 
	Position			search1(int key)const;

	Node head_;
public:
	SA();
	~SA();

	/*1*/	bool	search(int key)const;
	/*2*/	void	insert(int key);  //should be implemented
	/*3*/	void	remove(int key);  //should be implemented

	void	print()const;
};


