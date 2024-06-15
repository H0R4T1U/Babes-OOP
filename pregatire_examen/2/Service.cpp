//
// Created by horatiu on 6/14/24.
//

#include "Service.h"
#include <algorithm>
#include <cassert>
#include "Validator.h"
#include <stdexcept>
#include <map>

__int64_t Service::find(const string &den) {
    vector<Tractor> list = repo.getAll();
    auto x = find_if(list.begin(),list.end(),[den](const Tractor& t){
        return t.getDenumire() == den;
    });
    auto y = distance(list.begin(),x);
    if(y - list.size() == 0){
        return -1;}
    return y;
}

void Service::remove(const string &den) {
    __int64_t pos = find(den);
    if(pos == -1){
        throw std::invalid_argument("\"Nu exista!\"");}
    repo.remove(pos);
    notify();

}

void Service::add(int id, const string &den, const string &tip, int roti) {
    validate(repo.getAll(),id,den,tip,roti);
    Tractor t{id,den,tip,roti};
    repo.store(t);
    notify();
}

vector<Tractor> Service::sortDen() {
    vector<Tractor> sorted = repo.getAll();
    sort(sorted.begin(),sorted.end(),[](const Tractor& t1, const Tractor& t2){
        return t1.getDenumire() < t2.getDenumire();
    });
    return sorted;}

size_t Service::size() {
    return repo.size();
}

vector<string> Service::tipuri() {
    map<string,int> t;
    vector<string> tipuri;
    for(auto& x : repo.getAll()){
        if(t[x.getTip()] == 0){
            t[x.getTip()] = 1;
        }else{
            t[x.getTip()] +=1;
        }
    }
    for(auto& x: t){
        tipuri.push_back(x.first);
    }
    return tipuri;
}

void testService() {
    Repository repo{"../testServ.txt"};
    Service service{repo};
    service.add(1,"asdf","bsdf",4);
    assert(service.size() == 1);
    try{
        service.add(1,"","",3);
    assert(0);}catch(exception& ex){
        assert(1);
    }

    service.add(2,"aa","bb",6);
    assert(service.tipuri().size() == 2);
    assert(service.find("aa") == 1);
    assert(service.sortDen().at(0).getDenumire() == "aa");
    service.remove("aa");
    assert(service.size() == 1);
    service.remove("asdf");
    assert(service.size() == 0);
    try{
        service.remove("asdsafsa");
        assert(0);}catch(exception&){
        assert(1);
    }
}
