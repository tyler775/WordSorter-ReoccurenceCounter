#include <iostream>
#include <string>
using namespace std;

#define TABLE_SIZE 100000 // use a large prime number

unsigned int hash_func(const char *key, const unsigned int table_size)
{
	unsigned int h = 0;
	unsigned int o = 31415;
	const unsigned int t = 27183;
	while (*key)
	{
		h = (o * h + *key++) % table_size;
		o = o * t % (table_size - 1);
	}
	return h;
}

class HashtableItem;

class Hashtable
{
private:
	HashtableItem * *table;
	HashtableItem *cur_table_item;
	int cur_index;

public:
	Hashtable();
	~Hashtable();

	// Add a new entry, returns false when the key already exists
	bool Add(const string &key, const string &value);

	HashtableItem *operator[](const string &key) const;

	// removes one table entry
	void Remove(const string &key);

	// removes all the table entries
	void Clear();

	// for looping through the table of kes/values
	HashtableItem *GetFirst();
	HashtableItem *GetNext();
};

class HashtableItem
{
private:
	HashtableItem * pnext;
	string key, value;

	// keep these private to prevent the client from creating this object
	HashtableItem() {}
	HashtableItem(const string &key, const string &value);
	~HashtableItem();

public:
	const string &Key() const;
	const string &Value() const;
	const string &operator=(const string &value);
	const char *operator=(const char *value);

	// some friend functions that can access the private data
	friend bool Hashtable::Add(const string &key, const string &value);
	friend Hashtable::~Hashtable();
	friend void Hashtable::Remove(const string &key);
	friend HashtableItem *Hashtable::operator[](const string &key) const;
	friend HashtableItem *Hashtable::GetNext();
	friend void Hashtable::Clear();
};

// ##################### Hashtable ###########################
Hashtable::Hashtable() : cur_table_item(nullptr), cur_index(0)
{
	table = new HashtableItem*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; table[i++] = nullptr);
}
Hashtable::~Hashtable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i])
			delete table[i];
	}
	delete[]table;
}
bool Hashtable::Add(const string &key, const string &value)
{
	unsigned int i = hash_func(key.c_str(), TABLE_SIZE);
	if (table[i])
	{
		HashtableItem *node;
		for (node = table[i]; node->pnext && (node->pnext->Key() != key); node = node->pnext);
		if (node->pnext)
			return false;
		node->pnext = new HashtableItem(key, value);
		return true;
	}
	table[i] = new HashtableItem(key, value);
	return true;
}
HashtableItem *Hashtable::operator[](const string &key)
{
	unsigned int i = hash_func(key.c_str(), TABLE_SIZE);
	if (table[i])
	{
		if (table[i]->Key() == key)
			return table[i];
		HashtableItem *node;
		for (node = table[i]; node->pnext && (node->pnext->Key() != key); node = node->pnext);
		if (node->pnext)
			return node->pnext;
	}
	return nullptr;
}
void Hashtable::Remove(const string &key)
{
	unsigned int i = hash_func(key.c_str(), TABLE_SIZE);
	if (table[i])
	{
		HashtableItem *node, *tmp;
		if (table[i]->Key() == key)
		{
			tmp = table[i]->pnext;
			table[i]->pnext = nullptr;
			delete table[i];
			table[i] = tmp;
		}
		else
		{
			for (node = table[i]; node->pnext && (node->pnext->Key() != key); node = node->pnext);
			if (node->pnext) // then key found in linked list
			{
				tmp = node->pnext->pnext;
				node->pnext = nullptr;
				delete node->pnext;
				node->pnext = tmp;
			}
		}
	}
}
void Hashtable::Clear()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		delete table[i];
		table[i] = nullptr;
	}
}
HashtableItem *Hashtable::GetFirst()
{
	int i;
	this->cur_table_item = nullptr;
	this->cur_index = 0;

	for (i = this->cur_index; i < TABLE_SIZE && table[i] == nullptr; i++);
	if (i < TABLE_SIZE)
	{
		this->cur_table_item = table[i];
		this->cur_index = i;
	}
	return this->cur_table_item;
}
HashtableItem *Hashtable::GetNext()
{
	if (this->cur_table_item && this->cur_table_item->pnext)
		this->cur_table_item = this->cur_table_item->pnext;
	else
	{
		int i;
		for (i = this->cur_index + 1; i < TABLE_SIZE && table[i] == nullptr; i++);
		if (i < TABLE_SIZE)
		{
			this->cur_table_item = table[i];
			this->cur_index = i;
		}
		else
		{
			this->cur_table_item = nullptr;
			this->cur_index = 0;
		}
	}
	return this->cur_table_item;
}

// ##################### HashtableItem ###########################
HashtableItem::HashtableItem(const string &xKey, const string &xValue) : key(xKey), value(xValue), pnext(nullptr) {}
HashtableItem::~HashtableItem()
{
	if (this->pnext)
		delete this->pnext;
}
const string &HashtableItem::Key()
{
	return this->key;
}
const string &HashtableItem::Value()
{
	return this->value;
}
const string &HashtableItem::operator=(const string &value)
{
	this->value = value;
	return value;
}
const char *HashtableItem::operator=(const char *value)
{
	this->value = value;
	return value;
}

// #################### entry point ####################
// notice how much cleaner the code is here than when compared to the C example

