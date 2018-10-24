#include <iostream>
#include <ostream>
#include <cstring>
#include <string>
#include "HTable.h"
	using namespace std;
HTable::HTable() {
	int a = 0;
	while(a < size_max)
	{
		keys[a] = "";
		values[a] = "";		
		a++;	
	}
	
}

unsigned int HTable::hashing(const string& k)
{
	unsigned int value = 0;
	for (unsigned int i = 0; i < k.length(); i++)
		value = 37 * value + k[i];
	return value;
}

void HTable::printoutput() {
int a = 0;
while (a < size_max)
{
		if (!keys[a].empty())
			printf ("%s, %s\n", keys[a].c_str(), values[a].c_str());
		a++;
}
	
	
}


int HTable::find_index(const string& key, bool override_duplicate_key = true) {
	unsigned int h = hashing(key) % size_max;
unsigned int setting0 = 0; 
unsigned int i0;

	while (setting0 < size_max) {
		i0 = (h + setting0) % size_max;

		// empty i0 for new entry with key `key`
		// or find the i0 of key `key` in hashing table
		// if `override_duplicate_key` is `false`, return a new, unused i0, used in FindWordHash
		if (keys[i0].empty() ||
			(override_duplicate_key && keys[i0] == key))
			return i0;

		setting0++;
	}
	return -1;
}

void HTable::insert(const string& key, const string& value) {
	int i0 = find_index(key);
	if (i0 == negone) {
		cerr << "Hashmap has been filled!" << endl;
		return;
	}

	keys[i0] = key;
	values[i0] = value;
}

string HTable::find(const string& key) {
	int i0 = find_index(key);
	if (i0 != negone)
		return values[i0];

	return "";
}

string HTable::remove(const string& key) {
	int i0 = find_index(key);
	if (i0 == negone) return "";

	string value = values[i0];
	keys[i0].clear();
	values[i0].clear();

	return value;
}

void HTable::swap(const string& a, const string &b) {
	int a0 = find_index(a);
	int a00 = find_index(b);
	string a1 = keys[a0];
	string a2 = values[a0];
	keys[a0] = keys[a00];
	values[a0] = values[a00];
	keys[a00] = a1;
	values[a00] = a2;
}
int HTable::size_count(){
	int a = 0;
	int b = 0;
	while(b < size_max)
	{
		if(keys[b].empty() == false)
		{
		a++;
		}
		b++;
	}	
	return a;
}

int HTable::partition(const string arr[], int low, int high)
{
	string av = values[high];
	string a1 = "";
	int pivot;
	int lower = 0;
	pivot = atoi(av.c_str());
	

	cout << av << endl;
	
	cout << to_string(pivot) << endl;
	
		int a = low - 1;
		for (int i = low; i <= high - 1; i++)
		{
			a1 = values[i];
			lower = atoi(a1.c_str());
			if (lower <= pivot)
			{
				a++;
				swap(keys[a], keys[i]);
			}

		}
		swap(keys[a + 1], keys[high]);
		return (a + 1);
	

}



 void HTable::quickSort(int low, int high)
{
	string *arr = keys;
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(low, pi-1);
		quickSort(pi + 1, high);

	}
}

class FindWordHash : public HTable {
public:
	FindWordHash() : HTable() {}
	FindWordHash(string filename);
	void insert(const string& key, const string& value);
	
};

void FindWordHash::insert(const string& key, const string& value) {
	int i0 = find_index(key, false);
	if (i0 == negone) {
		cerr << "Table is full!" << endl;
		return;
	}

	keys[i0] = key;
	values[i0] = value;
}