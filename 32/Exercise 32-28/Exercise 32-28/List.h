#pragma once

template <typename T>
class Link {
public:
	T value;
	Link(T t = T{}, Link* p = nullptr, Link* s = nullptr)
		:value{ t }, prev{ p }, succ{ s } { }

	Link* prev;
	Link* succ;
};

template <typename T>
class List {
public:
	List();

	void insert(T t);
	void erase(T t);
	Link<T>* begin() { return b; }
	Link<T>* end() { return e; }
private:
	Link<T>* b;
	Link<T>* e;
};

template <typename T>
List<T>::List()
{
	Link<T>* l = new Link<T>();
	b = l;
	e = l;
}

template <typename T>
void List<T>::insert(T t)
{
	Link<T>* l = new Link<T>(t);
	if (!e->prev) {
		b = l;
		l->succ = e;
		e->prev = l;
		return;
	}
	l->prev = e->prev;
	l->succ = e;
	e->prev->succ = l;
	e->prev = l;
}

template <typename T>
void List<T>::erase(T t)
{
	for (auto p = begin(); p != end(); p = p->succ)
		if (p->value == t) {
			p->prev->succ = p->succ;
			p->succ->prev = p->prev;
			delete p;
			return;
		}
	throw runtime_error("no such value in the list");
}