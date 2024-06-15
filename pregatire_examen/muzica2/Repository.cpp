//
// Created by horatiu on 6/15/24.
//

#include "Repository.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cassert>

size_t Repository::getSize() {
    return repo.size();
}

vector<Melodie> Repository::getAll() {
    return repo;
}

void Repository::save() {
    ofstream fout(fileName);
    int i = 0;
    for(auto& x : repo){
        if(i == 0){
            fout<<x.getId()<<","<<x.getTitlu()<<","<<x.getArtist()<<","<<x.getTip()<<",";
        }else{
            fout<<endl<<x.getId()<<","<<x.getTitlu()<<","<<x.getArtist()<<","<<x.getTip()<<",";

        }
        i++;
    }
}

void Repository::add(Melodie &m) {
    repo.emplace_back(m);
}

void Repository::remove(size_t pos) {
    repo.erase(repo.begin() + pos);
}

int Repository::find(const string &denumire) {
    auto x = find_if(repo.begin(),repo.end(),[denumire](const Melodie& m){
        return m.getTitlu() == denumire;
    });
    auto y = distance(repo.begin(),x);
    if(y-repo.size() == 0){
        return -1;
    }
    return y;
}

void Repository::load() {
    ifstream fin(fileName);
    string line;
    while(getline(fin,line)){
        vector<string> args;
        string cuv;
        auto ss = stringstream(line);
        while(getline(ss,cuv,',')){
            args.push_back(cuv);
        }
        Melodie m{stoi(args[0]),args[1],args[2],args[3]};
        repo.push_back(m);
    }

}

void testRepository() {
    Repository r{"../testRepo.txt"};
    r.load();
    assert(r.getSize() == 1);
    Melodie m{2,"sdfs","Sdf","asdf"};
    r.add(m);
    r.save();
    assert(r.getSize() == 2);
    assert(r.getAll().size() == 2);
    assert(r.find("sdfs") == 1);
    assert(r.find("cvxcbvxcbv") == -1);
    r.remove(1);
    assert(r.getSize() == 1);
    r.save();
}
