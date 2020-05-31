//
//  main.cpp
//  lab9
//
//  Created by Андрей Журавлев on 18.05.2020.
//  Copyright © 2020 Андрей Журавлев. All rights reserved.
//
#include "task1.h"
#include "task2.h"
#include "task3.h"

int main(int argc, const char * argv[]) {
	testTask1();
	testTask2();
	
	Shop s;
	s.work(40);
	
	return 0;
}
