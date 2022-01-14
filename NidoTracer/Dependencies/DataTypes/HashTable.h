#pragma once
#define macro_KeySize 255
#define macro_ArraySize 10

class HashNode
{
public:
	HashNode() {}
	~HashNode() {}
	
	const char* m_key = nullptr;
	int m_value = 0;
	HashNode* p_next = nullptr;
};

class HashTable
{
protected:
	HashNode* m_hashNodes[macro_ArraySize];

public:
	HashTable();
	virtual ~HashTable();

	HashNode* Get(const char key[macro_KeySize]);
	void Set(const char* key, const int value);

	int Hash(const char* key);
};

