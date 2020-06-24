//
// Created by aklen on 23.05.2020.
//
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

template <class T1, class T2>
void bubble_sort(vector<T1> &arr, T2 comparator){
    for(size_t i = 0; i < arr.size(); i++){
        for(size_t j = 0; j < arr.size() - i - 1; j++ ){
            if(comparator(arr[j], arr[j+1])){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}



int main(){
    vector <int> int_vector = { 13, 15, 21, 2, 5, 22, 33, 10, 11};
    vector <double> double_vector = { 10.1, 3.3, 2.0, 1.3, 5.7, 6.1, 10.5, 15.3};
    vector <string> string_vector = { "asd", "asdasddas", "dasadsdsass", "a", "dasd", "asddd" };


    bubble_sort(int_vector, [](int a, int b){return a < b;});
    cout<<"int vector\n------------------\n1. from low to high "<<endl;
    for(auto item: int_vector){
        cout<<item<<" ";
    }

    bubble_sort(int_vector, [](int a, int b){return a > b;});
    cout<<"\n\n2. from high to low "<<endl;
    for(auto item: int_vector){
        cout<<item<<" ";
    }

    bubble_sort(double_vector, [](double a, double b){return a < b;});
    cout<<"\n------------------\ndouble vector\n------------------\n1. from low to high "<<endl;
    for(auto item: double_vector){
        cout<<item<<" ";
    }

    bubble_sort(double_vector, [](double a, double b){return a > b;});
    cout<<"\n\n2. from high to low "<<endl;
    for(auto item: double_vector){
        cout<<item<<" ";
    }


    bubble_sort(string_vector, [](const string &a, const string &b){return a.compare(b);});
    cout<<"\n------------------\nstring vector\n------------------\n1. from low to high "<<endl;
    for(auto item: string_vector){
        cout<<item<<" ";
    }

    bubble_sort(string_vector, [](const string &a, const string &b){return b.size() > a.size();});
    cout<<"\n\n2. from high to low "<<endl;
    for(auto item: string_vector){
        cout<<item<<" ";
    }

    return 0;
}