#include <iostream>
#include <stdio.h>
#include <map>
#include <set>

typedef struct a1{
    std::string name;
    std::map<int, a2> prefList;
    std::set<a2> proposed;
    bool paired = false;
    bool emptyProp = (proposed.size() == prefList.size());
    a1(std::string, std::map<int, a2>, std::set<a2>);
};

typedef struct a2{
    std::string name;
    std::map<std::string, int> prefList;
    a1* engaged;
    bool paired = false;
    a2(std::string name, std::map<std::string, int> prefList, a1* engaged);
};

std::set<a1> setIsFinished(std::set<a1> setA1){
    std::set<a1> response;
    for(a1 auxIter: setA1){
        if(auxIter.paired == false && auxIter.emptyProp == false){
            response.insert(auxIter);
        }
    }
    return response;
}

void stableMatching(std::set<a1> a1s){
    while(setIsFinished(a1s).size() != 0){
        for(a1 a1Iter : a1s){
            if(!a1Iter.prefList.find(1)->second.paired){
                a1Iter.prefList.find(1)->second.engaged = new a1(a1Iter);
                a1Iter.proposed.insert(a1Iter.prefList.find(1)->second);
                a1Iter.paired = true;
            }else{
                if(a1Iter.prefList.find(1)->second.prefList.find(a1Iter.prefList.find(1)->second.engaged->name)->second < a1Iter.prefList.find(1)->second.prefList.find(a1Iter.name)->second){
                    a1Iter.proposed.insert(a1Iter.prefList.find(1)->second);
                    a1Iter.paired = false;
                }else{
                    a1Iter.prefList.find(1)->second.engaged->paired = false;
                    a1Iter.proposed.insert(a1Iter.prefList.find(1)->second);
                    a1Iter.prefList.find(1)->second.engaged = new a1(a1Iter);
                    a1Iter.paired = true;
                }
            }
        }
    } 
}

//generate a1 constructor
a1::a1(std::string name, std::map<int, a2> prefList, std::set<a2> proposed){
    this->name = name;
    this->prefList = prefList;
    this->proposed = proposed;
}


// generate a2 constructor
a2::a2(std::string name, std::map<std::string, int> prefList, a1* engaged){
    this->name = name;
    this->prefList = prefList;
    this->engaged = engaged;
}



int main(){
    return 0;
}
