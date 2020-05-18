
#ifndef FUNCS_THREADS_TASK2_H
#define FUNCS_THREADS_TASK2_H

#include <string>
#include <vector>
#include <functional>

using namespace std;

void logProcess(const vector<string> & strings);
void sorted(vector<string> & strings,  const function<bool(string, string)>& comparator);

#endif //FUNCS_THREADS_TASK2_H
