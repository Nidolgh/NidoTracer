#pragma once
#include <cassert>
#include <iterator>

template <class T>
class QueueNode
{
protected:
	T m_data = 0;
	QueueNode* p_next = nullptr;
	QueueNode* p_prev = nullptr;

public:
	QueueNode() {}
	~QueueNode() { assert(p_next == nullptr || p_prev == nullptr); }

	T& get_data() { return m_data; }
	QueueNode<T>* next() { return p_next; }
	QueueNode<T>* prev() { return p_prev; }

	QueueNode<T>* next_amount(int amount = 1)
	{
		if (amount < 1)
			return this;
		amount--;
		QueueNode<T>* next_node = this;
		while (amount-- > 0)
		{
			next_node = next_node->next();
		}
		return next_node;
	}
	QueueNode<T>* prev_amount(int amount = 1)
	{
		if (amount < 1)
			return this;
		amount--;
		QueueNode<T>* prev_node = this;
		while (amount-- > 0)
		{
			prev_node = prev_node->prev();
		}
		return prev_node;
	}
	
	void set_data(T newGetData) { m_data = newGetData; }
	void set_next(QueueNode<T>* newNext) { p_next = newNext; }
	void set_prev(QueueNode<T>* newPrev) { p_prev = newPrev; }
};

template <class T>
class Queue
{
protected:
	QueueNode<T>* m_head = nullptr;
	QueueNode<T>* m_tail = nullptr;

	int m_count = 0;

public:
	Queue()
	{
		m_head = nullptr;
		m_tail = nullptr;
	}

	~Queue()
	{
		while (m_tail != nullptr)
		{
			pop();
		}
	}

	bool is_empty()
	{
		return m_head == nullptr;
	}
	
	QueueNode<T>* get_head_node() const { return m_head; }
	QueueNode<T>* get_tail_node() const { return m_tail; }
	int get_count() const { return m_count; }
	
	int top()
	{
		assert(m_head != nullptr);
		return m_head->get_data();
	}

	int bottom()
	{
		assert(m_tail != nullptr);
		return m_tail->get_data();
	}

	void push(T newData)
	{
		QueueNode<T>* tmpNode = new QueueNode<T>();
		tmpNode->set_data(newData);
		tmpNode->set_next(m_head);
		if (m_head != nullptr)
			m_head->set_prev(tmpNode);
		m_head = tmpNode;

		m_count++;
		
		if (m_tail == nullptr)
		{
			m_tail = tmpNode;
		}
	}

	void pop()
	{
		assert(m_tail != nullptr);
		QueueNode<T>* tmpNode = m_tail;
		m_tail = tmpNode->prev();
		tmpNode->set_prev(nullptr);
		delete tmpNode;
		tmpNode = nullptr;

		m_count--;

		if (m_head == nullptr)
		{
			m_tail = nullptr;
		}
	}
	
	void delete_all_payload()
	{
		while (m_tail != nullptr)
		{
			delete m_tail->get_data();
			pop();
		}
	}
};
