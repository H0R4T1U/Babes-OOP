#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Smoothy
{
	int pret;
public:
	virtual string descriere() = 0;
	virtual int getPret() { return pret; }
	Smoothy(int p) : pret{ p } {};
	virtual ~Smoothy() = default;
};

class BasicSmoothy : public Smoothy
{
public:
	string nume;
	string descriere() override
	{
		return nume;
	}
	BasicSmoothy(string n, int p) : nume{ n }, Smoothy(p) {};
	virtual ~BasicSmoothy() = default;
};

class DecoratorSmoothy : public Smoothy
{
	public:
	Smoothy* s;
	virtual string descriere() override
	{
		return s->descriere();
	}
	virtual int getPret() override
	{
		return s->getPret();
	}
	DecoratorSmoothy(Smoothy* _s) :s{ _s }, Smoothy(_s->getPret()) {};
	virtual ~DecoratorSmoothy()
	{
		delete s;
	}
};

class SmoothyCuFrisca : public DecoratorSmoothy
{
public:
	string descriere() override
	{
		return DecoratorSmoothy::descriere() + "cu frisca";
	}
	int getPret() override
	{
		return DecoratorSmoothy::getPret() + 2;
	}
	SmoothyCuFrisca(DecoratorSmoothy* s) : DecoratorSmoothy(s) {}
	~SmoothyCuFrisca() = default;
};

class SmoothyCuUmbreluta : public DecoratorSmoothy
{
public:
	string descriere() override
	{
		return DecoratorSmoothy::descriere() + "cu umbreluta";
	}
	int getPret() override
	{
		return DecoratorSmoothy::getPret() + 3;
	}
	SmoothyCuUmbreluta(DecoratorSmoothy* s) : DecoratorSmoothy(s) {}
	~SmoothyCuUmbreluta() = default;
};

vector<Smoothy*> f()
{
	vector<Smoothy*> v;
	Smoothy* s1 = new SmoothyCuFrisca{ new SmoothyCuUmbreluta{new DecoratorSmoothy{new BasicSmoothy{"kivi",10}}} };
	Smoothy* s2 = new SmoothyCuFrisca{ new DecoratorSmoothy{new BasicSmoothy{"capsuni",15}} };
	Smoothy* s3 = new BasicSmoothy{ "kivi",10 };
	v.push_back(s1);
	v.push_back(s2);
	v.push_back(s3);
	return v;
}

template <typename T>
class Geanta
{
	string proprietar;
	vector<T> obiecte;
public:
	Geanta(string p) : proprietar{ p } {};
	Geanta& operator+(const T& ob)
	{
		obiecte.push_back(ob);
		return *this;
	}
	typename vector<T>::iterator begin()
	{
		return obiecte.begin();
	}
	typename vector<T>::iterator end()
	{
		return obiecte.end();
	}
};

template <typename T>
class Measurement
{
	T val;
public:
	const T value() const { return val; }
	Measurement& operator+(T nr)
	{
		val = val + nr;
		return *this;
	}
	friend bool operator<(T& nr1, T& nr2)
	{
		return nr1.val < nr2.val;
	}
	Measurement(T v) : val { v }{};
};
int main()
{
	vector<Smoothy*>v = f();
	for (int i = 0; i < v.size() - 1; i++)
		if (v[i]->descriere() > v[i + 1]->descriere())
			swap(v[i], v[i + 1]);

	for (auto& sm : v)
	{
		cout << sm->descriere() << ' ' << sm->getPret() << '\n';
		delete sm;
	}
	cout << endl;
	vector<Measurement<int>> v1{ 10,2,3 };
	v1[2] + 3 + 2;
	sort(v1.begin(), v1.end());
	for (const auto& m : v1) cout << m.value() << ',';
}