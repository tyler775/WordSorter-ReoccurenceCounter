#ifndef HTable_H_
#define HTable_H_

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;

class HTable {
public:
	HTable();
	HTable(string filename);

	string find(const string& key);
	void insert(const string& key, const string& value);
	string remove(const string& key);
	void swap(const string& a, const string &b);
	int size_count();
	int partition(const string arr[], int low, int high);
	void quickSort(int low, int high);
	
	

	void printoutput();
protected:
	unsigned int hashing(const string& key);

	int find_index(const string& key, bool override_duplicated_key);

	const static unsigned int size_max = 9000;
    int negone = -1;

	string keys[size_max];
	string values[size_max];
};
#endif