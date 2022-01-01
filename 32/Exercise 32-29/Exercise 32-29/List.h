#pragma once
#include <vector>
using namespace std;

template <typename T> 
class List {
	vector<T*> v;
	vector<T*> owned;
public:
	List() {}

	List(initializer_list<T*> lst);

	~List();

	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	void erase(T* p);

	auto begin() { return v.begin(); }
	auto end() { return v.end(); }

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }
	int size() const { return v.size(); }
};

template <typename T>
List<T>::List(initializer_list<T*> lst)
{
	for (auto p = lst.begin(); p != lst.end(); p++) {
		push_back(*p);
	}
}

template <typename T>
List<T>::~List() 
{ 
	for (T* t : owned) 
		delete t; 
}

template <typename T>
void List<T>::erase(T* p) 
{
	for (auto x = v.begin(); x != v.end(); x++)
		if (*x == p) {
			v.erase(x);
			break;
		}
	for (auto x = owned.begin(); x != owned.end(); x++)
		if (*x == p) {
			delete p;
			owned.erase(x);
			break;
		}
}