#pragma once
#include <cassert>
#include <iterator>

#include "../Objects/Surface.h"

template <class T>
class LinkedNode
{
protected:
	T m_data;
	LinkedNode<T>* p_next = nullptr; // Solve problem replacing nullptr
	
public:
	LinkedNode() { p_next = nullptr; }
	~LinkedNode() { assert(p_next == nullptr); }

	const T& GetData() { return m_data; }
	LinkedNode<T>* Next() { return p_next; }
	
	void SetData(T newPayload) { m_data = newPayload; }
	void SetNext(LinkedNode<T>* newNext) { p_next = newNext; }
};

template <class T>
class LinkedList
{
protected:
	LinkedNode<T>* m_head = nullptr;

	int m_count = 0;
public:
	LinkedList() { m_head = nullptr; }
	
	virtual ~LinkedList() {
		while (m_head != nullptr)
		{
			pop();
		}
		
		m_count = 0;
	}

	bool IsEmpty() { return m_head == nullptr; }

	T Top() {
		assert(m_head != nullptr);
		return m_head->GetData();
	}
	
	void push(T new_data)
	{
		LinkedNode<T>* tmpNode = new LinkedNode<T>();
		tmpNode->SetData(new_data);
		tmpNode->SetNext(m_head);
		m_head = tmpNode;

		m_count++;
	}
	
	void pop()
	{
		assert(m_head != nullptr);
		LinkedNode<T>* tmpNode = m_head;
		m_head = tmpNode->Next();
		tmpNode->SetNext(nullptr);
		delete tmpNode;
		tmpNode = nullptr;

		m_count--;
	}
	
	void delete_all_payload()
	{
		while (m_head != nullptr)
		{
			delete m_head->GetData();
			pop();
		}
	}

	LinkedNode<T>* get_top() const { return m_head; }
	int get_count() const { return m_count; }
};