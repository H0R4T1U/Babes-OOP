//
// Created by horatiu on 6/16/24.
//

#include "Repository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

size_t Repository::getSize() {
    return repo.size();
}

vector<Task> Repository::getAll() {
    return repo;
}

void Repository::save() {
    ofstream fout(fileName);
    int i = 0;
    for(auto& x: repo){
        if(i == 0){
            fout<<x.getId()<<","<<x.getDescriere()<<","<<x.getStare()<<",";
            for(auto&y : x.getProgramatori()){
                fout<<y<<",";
            }
        }else{
            fout<<endl<<x.getId()<<","<<x.getDescriere()<<","<<x.getStare()<<",";
            for(auto&y : x.getProgramatori()){
                fout<<y<<",";
            }
        }
        i++;
    }

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
        int id = stoi(args[0]);
        string denumire = args[1];
        string tip = args[2];
        vector<string> programatori;
        for(int i = 3;i<args.size();i++){
            programatori.push_back(args[i]);
        }
        Task t {id,denumire,programatori,tip};
        repo.push_back(t);
    }

}



void Repository::add(Task &t1) {
    repo.push_back(t1);
}

void Repository::modify(size_t pos, const string&  stare) {
    Task t1 = repo.at(pos);
    Task t2 = {t1.getId(),t1.getDescriere(),t1.getProgramatori(),stare};
    repo.at(pos) = t2;
}

void testRepository() {
    Repository r{"../testRepo.txt"};
    r.load();
    assert(r.getSize() == 2);
    assert(r.getAll().at(0).getId() == 1);
    r.save();
    Task t1{3,"asdf3",{"asdf1","asdf2"},"open"};
    r.add(t1);
    r.modify(2,"closed");
    assert(r.getAll().at(2).getStare() == "closed");

}
