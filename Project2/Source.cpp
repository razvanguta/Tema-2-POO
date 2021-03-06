#include<iostream>
#include <stdlib.h>
using namespace std;

//Pereche(int,int)
class Pair {
	int a, b;
public:
	Pair() { } // constructor default
	Pair(int a, int b); //constructor pereche
	Pair(const Pair& per); //copy-constructor
	Pair& operator =(const Pair& per); //egal
	friend istream& operator>>(istream& in, Pair& per); //citire
	friend ostream& operator<<(ostream& out, const Pair& per); //afisare
	~Pair();
};
Pair::Pair(int a, int b) : a(a), b(b)
{
}
Pair::Pair(const Pair& per)
{
	a = per.a;
	b = per.b;
}
Pair& Pair:: operator=(const Pair& per)
{
	if (this->a != per.a)
		this->a = per.a;
	if (this->b != per.b)
		this->b = per.b;
	return *this;
}
istream& operator>>(istream& in, Pair& per)
{
	cout << "Perechea: ";
	in >> per.a >> per.b;
	return in;
}
ostream& operator<<(ostream& out, const Pair& per)
{
	cout << "(";
	out << per.a;
	cout << ",";
	out << per.b;
	cout << ")";
	return out;
}
Pair::~Pair()
{

}

//Multime_pereche
class Set_Pair {
protected:
	int n;
	Pair* p;
public:
	Set_Pair() { };//constructor default
	Set_Pair(int n);//constructor care primeste nr de elemente ale multimii de prechi
	Set_Pair(const Set_Pair& sp); //copy constructor
	Set_Pair& operator=(const Set_Pair& sp);// egal
	friend istream& operator>>(istream& in, Set_Pair& sp);//citim multimea de perechi
	friend ostream& operator<<(ostream& out, const Set_Pair& sp);//afisam multimea de perechi
	Pair& operator[](int index); // supraincarcam [] pentru a putea accesa mai usor elementele din multime
	int getnrel() { return this->n; }//returneza nr de elemente ale unei multimi
	void addval(const Pair& per) { n++; p[n-1] = per; } //adauga element in multime
	void eraseval(int x) {
		try {
			if (x >= n)
				throw 0;
		}catch (bool i)
		{
			cout << "Outside the range/n";
			exit(EXIT_FAILURE);
		}
		for (int i = x; i < n - 1; i++) { p[i] = p[i + 1]; }   //sterge element din multime
		n--;
	}
	virtual void typeobj() { cout << "SET\n"; } //pentru a ilustra conceptul de functie virtuala
	~Set_Pair();//destructor multime
};
Set_Pair::Set_Pair(int n) : n(n)
{
	try {
		p = new Pair[10*n];
	}
	catch (bad_alloc elem)
	{
		cout << "Allocation failure\n";
		exit(EXIT_FAILURE);
	}
}
Set_Pair::Set_Pair(const Set_Pair& sp)
{
	p = new Pair[10*sp.n];
	n = sp.n;
	for (int i = 0; i < sp.n; i++)
	{
		Pair* newper = new Pair(sp.p[i]);
		p[i] = *newper;
		delete newper;
	}
}
Set_Pair& Set_Pair:: operator=(const Set_Pair& sp)
{
	this->n = sp.n;
	this->p = new Pair[10*sp.n];
	for (int i = 0; i < sp.n; i++)
	{
		this->p[i] = sp.p[i];
	}
	return *this;
}
istream& operator>>(istream& in, Set_Pair& sp)
{
	cout << "Numarul de perechi: ";
	int nrper;
	cin >> nrper;
	sp.n = nrper;
	sp.p = new Pair[10*sp.n];
	cout << "Multimea de perechi:\n";
	Pair per;
	for (int i = 0; i < sp.n; i++)
	{
		in >> per;
		sp.p[i] = per;
	}
	return in;
}
ostream& operator<<(ostream& out, const Set_Pair& sp)
{
	cout << "Afisam multimea de perechi\n";
	for (int i = 0; i < sp.n; i++)
	{
		out << sp.p[i];
		cout << '\n';
	}
	return out;
}
Pair& Set_Pair::operator[](int index)
{
	if (index == n)
	{
		cout << "Index out of range\n";
	}
	else
		return p[index];
}
Set_Pair::~Set_Pair()
{
	delete[] p;
	n = 0;
}

//Stiva_perche
class Stack_Pair : public Set_Pair {
	int top;
	int maxsize;
public:
	Stack_Pair(int nrel); //constructor care primeste nr de elemente al multimii de perechi
	Stack_Pair(const Stack_Pair& stv);// copy-constructor
	Stack_Pair& operator=(const Stack_Pair& stv);
	void push(const Pair& p); //adauga element de tip pereche in stiva
	void pop(); //sterge element de tip pereche din stiva
	Pair peek();//returneaza vf stivei
	bool empty();//verifica daca stiva e goala sau nu
	void typeobj()  { cout << "STACK\n"; } //pentru a ilustra conceptul de functie virtuala
	~Stack_Pair();//destructor stiva
};
Stack_Pair::Stack_Pair(int nrel) : Set_Pair(nrel)//trimitem nrel catre clasa pe care o mostenim pentru a folosi array-ul de acolo drept stiva
{
	top = 0;
	maxsize = nrel;
}
Stack_Pair::Stack_Pair(const Stack_Pair& stv) : Set_Pair(stv.maxsize)
{
	top = stv.top;
	maxsize = stv.maxsize;
	for (int i = 0; i < top; i++)
	{
		p[i] = stv.p[i];
	}
}
Stack_Pair& Stack_Pair::operator=(const Stack_Pair& stv)
{
	this->p = new Pair[stv.maxsize];
	this->top = stv.top;
	this->n = stv.top;
	this->maxsize = stv.maxsize;
	for (int i = 0; i < stv.top; i++)
	{
		this->p[i] = stv.p[i];
	}
	return *this;
}
void Stack_Pair::push(const Pair& per)
{
	if (top == maxsize)
		cout << "Stack overflow\n";
	else
	{
		p[top] = per;
		top = top + 1;
		n = top;
	}
}
void Stack_Pair::pop()
{
	if (top < 0)
		cout << "Stack underflow\n";
	else
		top = top - 1, n=top;
}
Pair Stack_Pair::peek()
{
	if (top < 1)
	{
		cout << "Stack is empty\n";
	}
	else
		return p[top-1];
}
bool Stack_Pair::empty()
{
	if (top < 1)
	{
		return true;
	}
	else
		return false;
}
Stack_Pair::~Stack_Pair()
{
	maxsize = 0;
	top = 0;
}

//Coada_Pereche
class Queue_Pair : public Set_Pair {
	int front;
	int back;
	int maxsize;
public:
	Queue_Pair(int nrel); //constructor
	Queue_Pair(const Queue_Pair& qp); //copy-constructor
	void enqueue(const Pair& p); //adaugare in coada un element de tip pereche
	void dequeue(); //stergere element din coada
	Queue_Pair& operator=(const Queue_Pair& qp); //operator de atribuire
	Pair qfront(); //extrage urm element din coada
	bool empty(); //verifica daca este coada goala
	void typeobj() { cout << "QUEUE\n"; } //pentru a ilustra conceptul de functie virtuala
	~Queue_Pair(); //distrugere obiect
};
Queue_Pair::Queue_Pair(int nrel) : Set_Pair(nrel)
{
	front = 0;
	back = 0;
	maxsize = nrel;
}
Queue_Pair::Queue_Pair(const Queue_Pair& qp) :Set_Pair(qp.maxsize)
{
	front = qp.front;
	maxsize = qp.maxsize;
	back = qp.back;
	for (int i = 0; i < qp.back; i++)
	{
		p[i] = qp.p[i];
	}
}
void Queue_Pair::enqueue(const Pair& per)
{
	if (back == maxsize)
	{
		cout << "Queue overflow\n";
	}
	else
	{
		p[back] = per;
		back++;
		n=back;
	}
}
void Queue_Pair::dequeue()
{
	if (front == back)
		cout << "Queue underflow\n";
	else
	{
		for (int i = 0; i < back - 1; i++)
		 p[i] = p[i + 1];
		back--;
		n = back;
	}
}
Queue_Pair& Queue_Pair::operator=(const Queue_Pair& qp)
{
	this->front = qp.front;
	this->maxsize = qp.maxsize;
	this->back = qp.back;
	this->p = new Pair[this->maxsize];
	for (int i = 0; i < qp.back; i++)
	{
		this->p[i] = qp.p[i];
	}
	return *this;
}
Pair Queue_Pair::qfront()
{
	if (front == back)
		cout << "Queue is empty\n";
	else
		return p[front];
}
bool Queue_Pair::empty()
{
	if (front == back)
		return true;
	else
		return false;
}
Queue_Pair::~Queue_Pair()
{
	back = -1;
	front = -1;
	maxsize = 0;
}
void simulation(Queue_Pair& q1, Queue_Pair& q2, Set_Pair& a, Stack_Pair& s) //simuleaza stiva folosind 2 cozi
{
	int n = a.getnrel();
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		Pair x = a[i];
		q2.enqueue(x);
		s.push(x);
		while (!q1.empty())
		{
			q2.enqueue(q1.qfront());
			q1.dequeue();
		}
		Queue_Pair qaux = q1;
		q1 = q2;
		q2 = qaux;
	}
	while (!q1.empty())  //afisam coada q1 si stiva sa observam in paralel ca simularea se face cum trebuie
	{
		cout << q1.qfront() << " " << s.peek() << '\n';
		q1.dequeue();
		s.pop();
	}
}
void ilustrarevirtual(Set_Pair& sp)
{
	cout << "The element is a:" << " ";
	sp.typeobj();
}
int main()
{
	//citirea a n obiecte de tip Set_Pair si afisarea lor
	/*int n;
	cin >> n;
		Set_Pair* v = new Set_Pair[n];
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << v[i];
	}
	delete[] v;*/

	//test stiva simulata prin 2 cozi;
	/*Set_Pair a;
	cin >> a;
	Stack_Pair s(a.getnrel()); //declaram si o stiva,pentru a verifica la finalul executiei daca simularea prin 2 cozi se face cum trebuie, comparand rezultatele
	Queue_Pair q1(a.getnrel()), q2(a.getnrel());
	simulation(q1, q2, a, s);*/


	//test op= si copy constructor pt Pair
	/*Pair a(1, 1), b(-8, 3);
	cout << a << " " << b << " ";
	Pair c = b;
	b = a;
	cout << a << " " << b << " " << c;*/


	//test op= si copy constructor pt set_Pair
	/*Pair p(2, 2);
	Set_Pair a;
	cin >> a;
	Set_Pair b = a;
	Set_Pair c;
	c = a;
	cout << a << b << c;
	cout << endl;
	c[0]=p;
	c.addval(p);
	c.eraseval(1);
	cout << a << b << c;*/

	//test op= si copy constructor pt stack_Pair
	/*Pair a(1, 1), b(2, 1), c(2, 7), d(-1, 3), e(2, -5);
	Stack_Pair stv(5);
	stv.push(a);
	stv.push(b);
	stv.push(c);
	stv.push(d);
	stv.push(e);
	Stack_Pair stv2 = stv;
	Stack_Pair stv3(3);
	stv3.push(b);
	stv3.push(d);
	stv3.push(a);
	stv = stv3;
	while (!stv2.empty())
	{
		cout << stv2.peek() <<endl;
		stv2.pop();
	}
	cout << endl;
	while (!stv.empty())
	{
		cout << stv.peek() <<endl;
		stv.pop();
	}
	cout << endl;
	while (!stv3.empty())
	{
		cout << stv3.peek() <<endl;
		stv3.pop();
	}*/



	//test op= si copy constructor pt queue_Pair
	/*Pair a(1, 1), b(2, 1), c(2, 7), d(-1, 3), e(2, -5);
	Queue_Pair q(5);
	q.enqueue(a);
	q.enqueue(b);
	q.enqueue(c);
	q.enqueue(d);
	q.enqueue(e);
	Queue_Pair q2 = q;
	Queue_Pair q3(3);
	q3.enqueue(b);
	q3.enqueue(d);
	q3.enqueue(a);
	q = q3;
	while (!q2.empty())
	{
		cout << q2.qfront() <<endl;
		q2.dequeue();
	}
	cout << endl;
	while (!q.empty())
	{
		cout << q.qfront() << endl;
		q.dequeue();
	}
	cout << endl;
	while (!q3.empty())
	{
		cout << q3.qfront() << endl;
		q3.dequeue();
	}*/


   //ilustrare functie virtuala
   /*Set_Pair sp;
	Stack_Pair stv(1);
	Queue_Pair qp(1);
	ilustrarevirtual(sp);
	ilustrarevirtual(stv);
	ilustrarevirtual(qp);*/
	return 0;
}
