// SA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SA.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

int main()
{
	SA heap;
	const int n = 15;
	int a[n];
	int i;
	for (i = 0; i <n; i++)
		a[i] = i;

	//***** INSERTION TESTING *****
	cout << endl << "***** INSERTION TESTING *****" << endl;
	//srand((unsigned)time(0));
	random_shuffle(a, a + n); //creates a random permutation of numbers {0, ..., n-1}
	for (i = 0; i < n; i++)
		heap.insert(a[i]);
	heap.print();

	//***** SEARCH TESTING *****
	cout << endl << "***** SEARCH TESTING *****" << endl;
	for (i = 0; i < n; i++)
		cout << heap.search(i) << ' ';
	cout << endl << endl;

	//***** REMOVE TESTING *****
	cout << endl << "***** REMOVE TESTING *****" << endl;
	for (i = 0; i < n; i++) {
		heap.remove(i);
		heap.print();
	}
		

	system("pause");
	return 0;

}