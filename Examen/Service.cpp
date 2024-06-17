//
// Created by horatiu on 6/16/24.
//

#include "Service.h"
#include <algorithm>
#include <cassert>
#include <stdexcept>
bool Service::validate(vector<Task>t, int id, const string &denumire, const vector<string> &programatori,
                       const string &stare) {
    bool flag = true;
    for(auto&x :t ){
        if(x.getId() == id){
            flag= false;
        }
    }
    if(denumire.empty()){
        flag =  false;
    }
    if(programatori.empty() || programatori.size() > 4){
        flag = false;
    }
    if(stare != "open" && stare != "inprogress" && stare != "closed"){
        flag =  false;
    }
    return flag;
}

void Service::add(int id, const string &denumire, const vector<string> &programatori, const string &stare) {
    if(validate(repo.getAll(),id,denumire,programatori,stare)){
        Task t{id,denumire,programatori,stare};
        repo.add(t);
        repo.save();
        notify();
    }else{
        throw invalid_argument("Datele introduse nu sunt valide");
    }
}

vector<Task> Service::sortStare() {
    vector<Task> sorted = repo.getAll();
    sort(sorted.begin(),sorted.end(),[](const Task& t1,const Task& t2){
        return t1.getStare() < t2.getStare();
    });
    return sorted;}

vector<Task> Service::filter(const string &programator) {
    vector<Task> filtered;
    vector<Task> lista = sortStare();
    copy_if(lista.begin(),lista.end(), back_inserter(filtered),[programator](Task& t1){
        for(auto&x : t1.getProgramatori()){
            if(x == programator){
                return true;
            }
        }
        return false;
    });
    return filtered;
}

size_t Service::getSize() {
    return repo.getSize();
}

void Service::modifyStare(const string &denumire, const string &stare) {
    size_t pos = find(denumire);
    repo.modify(pos,stare);
    repo.save();
    notify();
}

size_t Service::find(const string &denumire) {
    vector<Task> list = repo.getAll();
    auto x = find_if(list.begin(),list.end(),[&denumire](Task& t1){
        return t1.getDescriere() == denumire;
    });
    auto y = distance(list.begin(),x);
    if(y - repo.getSize() == 0){
        return -1;
    }
    return y;
}

vector<Task> Service::getAll() {
    return repo.getAll();
}

void testService() {
    Repository repo{"testService.txt"};
    repo.save();
    Service service{repo};
    service.add(1,"d1",{"asdf1"},"open");
    service.add(2,"d2",{"asdf2"},"inprogress");
    service.add(3,"d3",{"asdf3","asdf1"},"closed");
    assert(service.find("d3") == 2);
    assert(service.find("d5") == -1);
    assert(service.getSize() == 3);
    try{
        service.add(1,"",{},"asdf");
        assert(false);}catch(exception&){
        assert(true);
    }
    try{
        service.add(1,"",{"asdf","Asdf2","asdf3","asdf4","asdf5"},"asdf");
        assert(false);}catch(exception&){
        assert(true);
    }
    assert(service.getSize() == 3);
    assert(service.sortStare().at(0).getStare() == "closed");
    assert(service.filter("asdf1").size() == 2);
    assert(service.filter("asdf2").size() == 1);
    service.add(4,"d4",{"asdf3","asdf1"},"closed");
    service.modifyStare("d4","open");
    assert(service.getAll().at(3).getStare() == "open");
}
