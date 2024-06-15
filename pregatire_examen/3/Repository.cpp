//
// Created by horatiu on 6/14/24.
//

#include "Repository.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cassert>

using namespace std;


void Repository::save() {
    ofstream fout(fileName);
    int i = 0;
    for(auto& x : repo){
        if(i == 0){
            fout<<x.getId()<<","<<x.getNume()<<","<<x.getTip()<<","<<x.getPret()<<",";

        }else{
            fout<<endl<<x.getId()<<","<<x.getNume()<<","<<x.getTip()<<","<<x.getPret()<<",";

        }
        i++;
    }
}

void Repository::add(Produs& p) {
    repo.emplace_back(p);
}


__int64_t Repository::find(const std::string &denumire) {
    auto x = find_if(repo.begin(),repo.end(),[denumire](const Produs& p){
        return p.getNume() == denumire;
    });
    auto y = distance(repo.begin(),x);
    if(y-repo.size() == 0){
        return -1;
    }
    return y;
}

void Repository::load() {
    ifstream fin(fileName);
    string linie;
    while(getline(fin,linie)){
        vector<string> args;
        string cuv;
        auto ss = stringstream(linie);
        while(getline(ss,cuv,',')){
            args.push_back(cuv);
        }
        Produs p{stoi(args[0]),args[1],args[2],stod(args[3])};
        repo.push_back(p);

    }

}

size_t Repository::size() {
    return repo.size();
}

vector<Produs> Repository::getAll() {
    return repo;
}

void testRepository() {
    Repository repo{"../testRepo.txt"};
    repo.load();
    assert(repo.size() == 2);
    repo.save();
    Produs p{2,"asdf","bsdf",2.31};
    repo.add(p);
    assert(repo.getAll().size() == 3);
    assert(repo.find("asdf") == 2);
    assert(repo.find("xzc") == -1);

}