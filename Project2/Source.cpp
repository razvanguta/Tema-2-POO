//FORMA NEFINALA
#include<iostream>
using namespace std;

//Pereche(int,int)
class Pair {
	int a, b;
public:
	Pair() {} // constructor default
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
	out << per.a;
	cout << " ";
	out << per.b;
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
	Set_Pair() {};//constructor default
	Set_Pair(int n);//constructor care primeste nr de elemente ale multimii de prechi
	Set_Pair(const Set_Pair& sp); //copy constructor
	Set_Pair& operator=(const Set_Pair& sp);// egal
	friend istream& operator>>(istream& in, Set_Pair& sp);//citim multimea de perechi
	friend ostream& operator<<(ostream& out, const Set_Pair& sp);//afisam multimea de perechi
	Pair& operator[](int index); // supraincarcam [] pentru a putea accesa mai usor elementele din multime
	int getnrel() { return this->n; }//returneza nr de elemente ale unei multimi
	~Set_Pair();//destructor multime
};
Set_Pair::Set_Pair(int n) : n(n)
{
	try {
		p = new Pair[n];
	}
	catch (bad_alloc elem)
	{
		cout << "Allocation failure\n";
		exit(EXIT_FAILURE);
	}
}
Set_Pair::Set_Pair(const Set_Pair& sp)
{
	p = new Pair[sp.n];
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
	this->p = new Pair[sp.n];
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
	sp.p = new Pair[sp.n];
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
class Stack_Pair : public Pair {
	int top;
	int maxsize;
	Pair* st;
public:
	Stack_Pair(int nrel); //constructor care primeste nr de elemente al multimii de perechi
	Stack_Pair(const Stack_Pair& stv);
	Stack_Pair& operator=(const Stack_Pair& stv);
	void push(const Pair& p); //adauga element de tip pereche in stiva
	void pop(); //sterge element de tip pereche din stiva
	Pair peek();//returneaza vf stivei
	bool empty();//verifica daca stiva e goala sau nu
	~Stack_Pair();//destructor stiva
};
Stack_Pair::Stack_Pair(int nrel)
{
	top = -1;
	maxsize = nrel;
	try {
		st = new Pair[nrel];
	}
	catch (bad_alloc elem)
	{
		cout << "Allocation failure\n";
		exit(EXIT_FAILURE);
	}
}
Stack_Pair::Stack_Pair(const Stack_Pair& stv)
{
	st = new Pair[stv.maxsize];
	top = stv.top;
	maxsize = stv.maxsize;
	for (int i = 0; i <= top; i++)
	{
		st[i] = stv.st[i];
	}
}
Stack_Pair& Stack_Pair::operator=(const Stack_Pair& stv)
{
	this->st = new Pair[stv.maxsize];
	this->top = stv.top;
	this->maxsize = stv.maxsize;
	for (int i = 0; i <= stv.top; i++)
	{
		
		this->st[i] = stv.st[i];
	}
	return *this;
}
void Stack_Pair::push(const Pair& p)
{
	if (top == maxsize)
		cout << "Stack overflow\n";
	else
	{
		top = top + 1;
		st[top] = p;

	}
}
void Stack_Pair::pop()
{
	if (top < 0)
		cout << "Stack underflow\n";
	else
		top = top - 1;
}
Pair Stack_Pair::peek()
{

	if (top < 0)
	{
		cout << "Stack is empty\n";
	}
	else
		return st[top];
}
bool Stack_Pair::empty()
{
	if (top < 0)
	{
		return true;
	}
	else
		return false;
}
Stack_Pair::~Stack_Pair()
{
	delete[] st;
	maxsize = 0;
	top = -1;
}

//Coada_Pereche
class Queue_Pair : public Set_Pair {
	Pair* q;
	int front;
	int back;
	int maxsize;
public:
	Queue_Pair(int nrel);
	Queue_Pair(const Queue_Pair& qp);
	void enqueue(const Pair& p);
	void dequeue();
	Queue_Pair& operator=(const Queue_Pair& qp);
	Pair qfront();
	bool empty();
	~Queue_Pair();
};
Queue_Pair::Queue_Pair(int nrel)
{
	front = 0;
	back = 0;
	maxsize = nrel;
	try {
		q = new Pair[nrel];
	}
	catch (bad_alloc elem)
	{
		cout << "Allocation failure\n";
		exit(EXIT_FAILURE);
	}
}
Queue_Pair::Queue_Pair(const Queue_Pair& qp)
{
	front = qp.front;
	maxsize = qp.maxsize;
	back = qp.back;
	q = new Pair[this->maxsize];
	for (int i = 0; i < qp.back; i++)
	{
		q[i] = qp.q[i];
	}
}
void Queue_Pair::enqueue(const Pair& p)
{
	if (back == maxsize)
	{
		cout << "Queue overflow\n";
	}
	else
	{
		q[back] = p;
		back++;
	}
}
void Queue_Pair::dequeue()
{
	if (front == back)
		cout << "Queue underflow\n";
	else
	{
		for (int i = 0; i < back - 1; i++)
			q[i] = q[i + 1];
		back--;
	}
}
Queue_Pair& Queue_Pair::operator=(const Queue_Pair& qp)
{
	this->front = qp.front;
	this->maxsize = qp.maxsize;
	this->back = qp.back;
	this->q = new Pair[this->maxsize];
	for (int i = 0; i < qp.back; i++)
	{
		this->q[i] = qp.q[i];
	}
	return *this;
}
Pair Queue_Pair::qfront()
{
	if (front == back)
		cout << "Queue is empty\n";
	else
		return q[front];
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

	delete[] q;
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
int main()
{

	//citirea a n obiecte de tip Set_Pair si afisarea lor
	int n;
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
	delete[] v;
	//????
	/*Pair a(1, 1), b(1, 1), c(2, 3), d(2, 3), e(2, 5);
	Stack_Pair st(1);
	st.push(a);
	st.peek();
	st.pop();
	st.peek();*/


	//test stiva simulata prin 2 cozi;
	/*Set_Pair a;
	cin >> a;
	Stack_Pair s(a.getnrel());
	Queue_Pair q1(a.getnrel()), q2(a.getnrel());
	simulation(q1, q2, a, s);*/


	//test op= si copy constructor pt Pair
	/*Pair a(1, 1), b(-8, 3);
	cout << a << " " << b << " ";
	Pair c = b;
	b = a;
	cout << a << " " << b << " " << c;*/


	//test op= si copy constructor pt set_Pair
	/*Set_Pair a;
	cin >> a;
	Set_Pair b = a;
	Set_Pair c;
	c = a;
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
	}
	*/


	//test op= si copy constructor pt queue_Pair
	/*Pair a(1, 1), b(2, 1), c(2, 7), d(-1, 3), e(2, -5);
	Queue_Pair stv(5);
	stv.enqueue(a);
	stv.enqueue(b);
	stv.enqueue(c);
	stv.enqueue(d);
	stv.enqueue(e);
	Queue_Pair stv2 = stv;
	Queue_Pair stv3(3);
	stv3.enqueue(b);
	stv3.enqueue(d);
	stv3.enqueue(a);
	stv = stv3;
	while (!stv2.empty())
	{
		cout << stv2.qfront() <<endl;
		stv2.dequeue();
	}
	cout << endl;
	while (!stv.empty())
	{
		cout << stv.qfront() << endl;
		stv.dequeue();
	}
	cout << endl;
	while (!stv3.empty())
	{
		cout << stv3.qfront() << endl;
		stv3.dequeue();
	}*/
	return 0;
}
