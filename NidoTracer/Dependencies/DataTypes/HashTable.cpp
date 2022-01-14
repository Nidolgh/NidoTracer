#include "HashTable.h"

HashTable::HashTable() : m_hashNodes()
{
	for (int i = 0; i < macro_ArraySize; i++)
	{
		m_hashNodes[i] = nullptr;
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < macro_ArraySize; i++)
	{
		if (m_hashNodes[i] != nullptr)
		{
			HashNode* curNode = m_hashNodes[i]->p_next;

			while (curNode != nullptr)
			{
				HashNode* tmpNode = curNode->p_next;
				delete curNode;
				curNode = nullptr;
				curNode = tmpNode;
			}
			
			delete m_hashNodes[i];
			m_hashNodes[i] = nullptr;
		}
	}
}

HashNode* HashTable::Get(const char* key)
{
	int hashed = Hash(key);
	
	HashNode* curNode = m_hashNodes[hashed];
	while (curNode != nullptr && curNode->p_next != nullptr)
	{
		if (curNode->m_key == key)
		{
			return curNode;
		}
		
		curNode = curNode->p_next;
	}
	
	return curNode;
}

void HashTable::Set(const char key[macro_KeySize], const int value)
{
	const int hashed = Hash(key);

	HashNode* tmpNode = new HashNode();
	tmpNode->m_key = key;
	tmpNode->m_value = value;
	
	if (m_hashNodes[hashed] == nullptr)
	{
		m_hashNodes[hashed] = tmpNode;
	}
	else
	{
		HashNode* curNode = m_hashNodes[hashed];

		while (curNode->p_next != nullptr)
		{
			if (curNode->m_key == key)
			{
				curNode->m_key = key;
				curNode->m_value = value;
				return;
			}
			
			curNode = curNode->p_next;
		}
		
		if (curNode->m_key == key)
		{
			curNode->m_key = key;
			curNode->m_value = value;
			return;
		}
		
		curNode->p_next = tmpNode;
	}
}

int HashTable::Hash(const char* key) {
	int hash = 5381;

	while (*key != '\0') {
		hash = ((hash << 4) + static_cast<int>(*key)) % macro_ArraySize;
		key++;
	}

	return hash;
}// introduction to ray tracing