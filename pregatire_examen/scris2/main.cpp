#include <iostream>
#include <vector>

using namespace std;
class Smoothy{
private:
    int pret;
public:
    Smoothy(int pret): pret{pret}{};
    virtual int getPret(){
        return pret;
    }
    virtual string descriere() = 0;

};
class BasicSmoothy:public Smoothy{};
class DecoratorSmoothy: public Smoothy{
private:
    Smoothy* s;

public:
    DecoratorSmoothy(Smoothy* So): Smoothy(So->getPret()),s{So}{};
    virtual  string descriere()override{
        return s->descriere();
    }
    virtual int getPret()override{
        return s->getPret();
    }
};
class SmoothyCuUmbreluta:public DecoratorSmoothy{};

class SmoothyCuFrisca:public DecoratorSmoothy{
    SmoothyCuFrisca(Smoothy* s): DecoratorSmoothy(s){};
    string descriere()override{
        DecoratorSmoothy::descriere() + " cu frisca";
    }
    int getPret()override{
        DecoratorSmoothy::getPret() + 3;
    }
};
int f(){
    std::vector<Smoothy*> s;
    s.push_back(new SmoothyCuFrisca{new SmoothyCuUmbreluta{BasicSmoothy{30,"kiwi"}}})
    s.push_back(new SmoothyCuFrisca{new BasicSmoothy{30,"capsuni"}})
    s.push_back(new {BasicSmoothy{30,"kiwi"}});
    return s;
}
typedef typename <T>
class Geanta
int main() {
    vector<Smoothy*> v = f();
    for(int i = 0 ; i<v.size();i++){
        for(int j = 0 ; j<v.size();j++){
            if(v[j]->descriere() > v[j+1]->descriere()){
                swap(v[j],v[j+1]);
            }
        }
    }
    for(int i = 0 ; i<v.size();i++){
        cout<<v[i]->descriere()<<" "<<v[i]->getPret();
    }
    return 0;
}
