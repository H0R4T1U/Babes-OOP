//
// Created by horatiu on 6/14/24.
//

#include "Service.h"
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <map>

void Service::add(int id, const string &denumire, const string &tip, double pret) {
    validate(repo.getAll(),id,denumire,tip,pret);
    Produs p{id,denumire,tip,pret};
    repo.add(p);
    repo.save();
    notify();
}

void Service::validate(const vector<Produs>& vector1, int id, const string &den, const string &tip, double pret) {
    string err;
    for(auto& x : vector1){
        if(x.getId() == id){
            err+="Id-ul Trebuie sa fie unic!\n";
            break;
        }
    }
    if(pret < 1.0 || pret > 100.0){
        err+="Pretul trebuie sa fie intre 1.0 si 100.0\n";
    };
    if(den.empty()){
        err+="Denumirea nu poate fi goala!\n";
    }
    if(!err.empty()){
        throw invalid_argument(err);
    }
}

vector<Produs> Service::filterPret(double pret) {
    vector<Produs> filtered;
    vector<Produs> lista = repo.getAll();
    copy_if(lista.begin(),lista.end(), back_inserter(filtered),[pret](Produs& p1){
        return p1.getPret() <= pret;
    });
    return filtered;
}

vector<Produs> Service::sortPret() {
    vector<Produs> list = repo.getAll();
    sort(list.begin(),list.end(),[](Produs& p1,Produs& p2){
        return p1.getPret() < p2.getPret();
    });
    return list;
}

size_t Service::size() {
    return repo.size();
}

int Service::nrProdTip(const string &tip) {
    int nr = 0;
    for(auto& x : repo.getAll()){
        if(x.getTip() == tip){
            nr++;
        }
    }
    return nr;
}

vector<string> Service::tipuri() {
    map<string,int> t;
    vector<string> tip;
    for(auto& x : repo.getAll()){
        if(t[x.getTip()] == 0){
            t[x.getTip()] =1;
        }
    }
    for(auto& x : t){
        tip.push_back(x.first);
    }
    return tip;
}

void testService() {
    Repository repo{""};
    repo.save();
    Service service{repo};
    service.add(1,"asdf","tip",3.51);
    service.add(2,"fd","fd",51);
    service.add(3,"ac","ac",1);

    try{
        service.add(1,"","",0);
    }catch(exception&){
        assert(1);
    }
    vector<Produs> filt;
    filt = service.filterPret(50);
    assert(filt.size() == 2);
    assert(service.sortPret().at(0).getPret() == 1);
    assert(service.size() == 3);
    assert(service.nrProdTip("fd") == 1);
    assert(service.tipuri().size() == 3);
}