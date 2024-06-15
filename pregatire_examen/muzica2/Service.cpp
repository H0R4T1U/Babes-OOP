//
// Created by horatiu on 6/15/24.
//

#include <cassert>
#include "Service.h"
#include <algorithm>
using namespace std;
size_t Service::size() {
    return repo.getSize();
}

vector<Melodie> Service::getAll() {
    return repo.getAll();
}

void Service::add(int id, const string &denumire, const string &artist, const string &tip) {
    if(validate(repo.getAll(),id,denumire,artist,tip) == 1){
        return;
    }
    Melodie m{id,denumire,artist,tip};
    repo.add(m);
    repo.save();
}

void Service::remove(const string &titlu) {
    size_t x = repo.find(titlu);
    if(x != -1){
        repo.remove(x);
        repo.save();

    }
}

int Service::validate(const vector<Melodie> &rep, int id, const string &titlu, const string &artist, const string &tip) {
    int err = 0;
    for(auto& x: rep){
        if(x.getId() == id){
            err=1;
        }
    }
    if(titlu.empty()){
        err=1;
    }
    if(artist.empty()){
        err=1;
    }

    if(tip != "rock" && tip != "pop" && tip != "folk" && tip != "disco"){
        err = 1;
    }
    return err;
}

vector<Melodie> Service::sortArt() {
    vector<Melodie>sorted = repo.getAll();
    sort(sorted.begin(),sorted.end(),[](Melodie& m1,Melodie& m2){
        return m1.getArtist() < m2.getArtist();
    });
    return sorted;}

map<string, int> Service::getNrTypes() {
    map<string,int> tipuri;
    for(auto&x:repo.getAll()){
        tipuri[x.getTip()]++;
    }
    return tipuri;}

void testService() {
    Repository repo{"../testServ.txt"};
    Service service{repo};
    assert(service.size() == 0);
    assert(service.getAll().empty());
    service.add(1,"asdf","dsf","rock");
    assert(service.size() == 1);
    service.add(1,"","","asfa");
    assert(service.size() == 1);
    service.add(2,"aa","aa","pop");
    assert(service.sortArt().at(0).getArtist() == "aa");
    assert(service.getNrTypes()["pop"] == 1);
    service.remove("aa");
    service.remove("asdf");
    assert(service.size() == 0);

}
