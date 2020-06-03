//
// Created by Anton Korkunov on 03/06/2020.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename _Iterator,typename _Compare>
void Bub_sort(_Iterator frst, _Iterator lst, _Compare cmpr){
    for(auto i=frst; i!=lst; ++i){
        for(auto j=frst; j!=lst-1; ++j){
            if(cmpr(*j,*(j+1))) swap(*j,*(j+1));
        }
    }
}

int main() {
    vector<string> V={"test", "netest", "peretest", "nedotest","atest", "ztest", "mnogotest"};

    vector<string> forsortV = V;
    for(int i =0; i<V.size();i++) cout << V[i] << " ";
    cout<<"\n\n";
    Bub_sort(forsortV.begin(), forsortV.end(), [](auto lhs, auto rhs) {//1
        return lhs > rhs;
    });
    for(int i =0; i<forsortV.size();i++) cout << forsortV[i] << " ";

    forsortV = V;
    Bub_sort(forsortV.begin(), forsortV.end(), [](auto lhs, auto rhs) {//2
        return lhs < rhs;
    });
    cout<<"\n";
    for(int i =0; i<forsortV.size();i++) cout << forsortV[i] << " ";

    forsortV = V;
    Bub_sort(forsortV.begin(), forsortV.end(), [](auto lhs, auto rhs) {//3
        return lhs[0] > rhs[0];
    });
    cout<<"\n";
    for(int i =0; i<forsortV.size();i++) cout << forsortV[i] << " ";

    forsortV = V;
    Bub_sort(forsortV.begin(), forsortV.end(), [](auto lhs, auto rhs) {//4
        return lhs.size() > rhs.size();
    });
    cout<<"\n";
    for(int i =0; i<forsortV.size();i++) cout << forsortV[i] << " ";

    forsortV = V;
    Bub_sort(forsortV.begin(), forsortV.end(), [](auto lhs, auto rhs) {//5
        return lhs.size() < rhs.size();
    });
    cout<<"\n";
    for(int i =0; i<forsortV.size();i++) cout << forsortV[i] << " ";
    return 0;
}