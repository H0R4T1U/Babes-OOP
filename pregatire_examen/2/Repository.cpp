//
// Created by horatiu on 6/14/24.
//

#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

size_t Repository::size() const {
    return repo.size();
}

vector<Tractor> Repository::getAll() const {
    return repo;
}

void Repository::store(const Tractor& t) {
    repo.emplace_back(t);
    save();
}

void Repository::save() {
    ofstream fout(fileName);
    int i = 0;
    for(auto& x : repo){
        if(i == 0){
            fout<<x.getId()<<","<<x.getDenumire()<<","<<x.getTip()<<","<<x.getRoti()<<",";
        }else{
            fout<<endl<<x.getId()<<","<<x.getDenumire()<<","<<x.getTip()<<","<<x.getRoti()<<",";
        }
        i++;
    }
}

void Repository::load() {
    ifstream fin(fileName);
    string line;
    int i = 0;
    while(getline(fin,line)){
        vector<string> args;
        string cuv;
        auto ss = stringstream(line);
        while(getline(ss,cuv,',')){
            args.push_back(cuv);
        }
        Tractor t{stoi(args[0]),args[1],args[2],stoi(args[3])};
        repo.emplace_back(t);
    }
}

void Repository::remove(const __int64_t pos) {
    repo.erase(repo.begin()+pos);
    save();
}

void testRepo(){
    Repository repo{"../testRepo.txt"};
    repo.load();
    assert(repo.size() == 1);
    assert(repo.getAll().size() == 1);
    Tractor t(2,"John","TIPC",6);
    repo.store(t);
    assert(repo.size() == 2);
    repo.remove(1);
    assert(repo.getAll().at(0).getId() == 1);

}