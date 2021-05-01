#pragma once
#include <iostream>

const int MAX_DEG = 9;

template <class T>
class Node {
public:
	T data;
	Node<T>* next;
	Node(T _data, Node* p)
	{
		data = _data;
		next = p;
	}
};

template<class T>
class List {
protected:
	Node<T>* head;
	std::size_t size;
public:
	class iterator {
       private:
	      Node<T>* curr;
       public:
	      iterator(Node<T>* pcurr) 
		  { 
			  curr=pcurr;
		  }
	      iterator(const iterator& iter) 
		  { 
			  curr=iter.curr;
		  }
	      Node<T>& operator*()
		  {
			  return *curr;
		  }
		  Node<T>*& get_it()
		  {
			  return curr;
		  }
		  Node<T>* operator->()
		  {
			  return curr;
		  }
		  iterator operator++()
		  {
			  curr=curr->next;
			  return (*this);
		  }
		  bool operator==(iterator iter)
		  {
			  if (curr==iter.curr) return true;
			  else return false;
		  }
		  bool operator !=(iterator iter)
		  {
			  return !(*this==iter);
		  }
     };
	iterator begin() const
	{
		iterator iter(head->next);
		return iter;
	}

	iterator end() const
	{
		iterator iter(head);
		return iter;
	}
	List()
	{
		T m;
		Node<T>* p = new Node<T> (m, nullptr);
		p->next = p;
		head = p;
		size = 0;
	}
	List(Node<T>* p) 
	 {
		 head = p;
		 head->next = head;
		 size = 0;
	 }

	 List(const List& list)
	 {
		 Node<T>* p = new Node<T>(list.get_head()->data, nullptr);
		 head = p;
		 head->next = head;
		 size = 0;
		 iterator it1 = begin();
		 iterator it2 = list.begin();
		 while (it2 != list.end())
		 {
			insert(it2->data, it1.get_it());
			++it1;
			++it2;
		 }
	 }

	 ~List()
	 {
		clear();
	 }

	 void clear() 
	 {
		while (head->next != head)
		     pop_front();
		size = 0;
	 }

	 Node<T>* get_head() const
	 {
		 return head;
	 }

	 bool operator ==(const List& lst) const
	 {
		 iterator it1 = begin(); 
		 iterator it2 = lst.begin();
		 bool flag = true;
		 if (size != lst.get_size())
			 return false;
		 else {
		     do
		     { 
			     if (it1->data != it2->data)
			     { 
				      flag = false;
				      break;
			     }
			     else
			     {
				      ++it1;
				      ++it2;
			     }
		     }
		     while (it1 != end());
		 }
		 return flag;
	 }

	 List& operator =(const List& lst)
	 {
		 if (*this == lst) return (*this);
		 else {
				this->clear();
				iterator it1 = begin();
				iterator it2 = lst.begin();
		        while (it2 != lst.end())
		        { 
			        insert(it2->data, it1.get_it());
					++it1;
					++it2;
		        }
			 }
		 return (*this);
     }

	  void push_front(T elem)
	 {
		Node<T>*p = new Node<T> (elem, head->next);
		head->next = p;
		size++;
	 }

	void pop_front()
	 {
		 Node<T>* p = head->next;
		 head->next = p->next;
		 delete p;
		 size--;
	 }

	void insert(T elem, Node<T>* pn)
	{
		Node<T>* p = new Node<T>(elem, pn->next);
		pn->next = p;
		size++;
	}

	int get_size() const
	{ 
		return size;
	}
};

class Polynom;

class Monom {
public:
	double k;
	int degree;

	Monom(double coeff = 0, int deg = -1);

	Monom(const Monom& a);

	int x_degree() const
	{
		return (degree / 100);
	}

	int y_degree() const
	{
		return ((degree / 10) % 10);
	}
	
	int z_degree() const
	{
		return (degree % 10);
	}

	bool deg_is_correct();
	
	bool operator ==(const Monom& m);

	bool operator !=(const Monom& m);

	Monom operator+(const Monom& a);
	
	Monom operator* (const Monom& a);
	
	Polynom Monom::operator* (const Polynom& pol);

	friend std::ostream& operator<<(std::ostream& os, const Monom& m)
	{
		os<<m.k<<" "<<m.degree;
		return os;
	}
};

class Polynom: public List<Monom> {
public:

	Polynom() : List<Monom>()	{}

	Polynom(Node<Monom>* p) : List<Monom>(p) {}

	Polynom(const Polynom& pol) : List<Monom>(pol) {}

	~Polynom() {
		clear();
	}
	
	Polynom operator+ (const Polynom& pol);

	Polynom operator* (const Polynom& pol);

	friend std::ostream& operator<<(std::ostream& os, const Polynom& pol)
	{
		Polynom::iterator it = pol.begin();
		while (it != pol.end())
		{
			os<<"+"<<it->data;
			++it;
		}
		return os;
	}
};