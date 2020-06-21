//
// Created by Anton Korkunov on 03/06/2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mu;
condition_variable cv;
bool DONE=false;
bool checkITR=false;
bool checkOUT=false;

template<typename _Iterator,typename _Compare>
void Bub_sort(_Iterator frst, _Iterator lst, _Compare cmpr){
    for(auto i=frst; i!=lst; ++i){
        for(auto j=frst; j!=lst-1; ++j){
            if(cmpr(*j,*(j+1))) swap(*j, *(j + 1));
            {
                checkITR = true;
                cv.notify_all();
                unique_lock<mutex> lk(mu);
                cv.wait(lk, []() { return checkOUT; });
                checkOUT = false;
            }
        }
    }
    DONE=true;
    cv.notify_all();
}

int main() {
    vector<string> V={"test", "netest", "peretest", "nedotest", "atest", "ztest", "mnogotest", "tri", "pyatb", "sixsix"};
    thread t1(Bub_sort<vector<string>::iterator, bool(*)(string&, string&)>, V.begin(), V.end(), [](auto lhs, auto rhs) {
        return lhs.size() > rhs.size();
    });
    while(!DONE){
        unique_lock<mutex> lk(mu);
        cv.wait(lk, [](){return checkITR || DONE;});
        checkITR=false;
        for(const auto & i : V) cout << i << " ";
        cout<<"\n";
        checkOUT=true;
        cv.notify_all();
    }
    t1.join();

    return 0;
}
