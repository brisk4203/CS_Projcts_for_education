#ifndef CLIENT_C
#define CLIENT_C
// =========================================================

//EC 1 Print queue
//Your name: Christopher Wendling
//Complier:  g++
//File type: printer client file
/*
need to add: 
x struct with ID, state
x make sure array size is 20ish
- randomize priority from 1-50
- add new array or vector of jobs to be added to print queue
- randomly select one process from our job queue/table to add to print queue.
- fix display function to display the PCB table instead of queue

*/
//===========================================================
#include <time.h>
#include <cstdlib>
#include "printer.h"

int main()
{
	cout << "\n\nProgram Created by: Christopher Wendling, Chase Perdue" << endl;
	cout << "========================================================\n" << endl;
	
	srand(time(NULL));
	
	PrintQ printer;
	int p, j; 		//random elements
	
	for(int i = 0; i < 20; ++i)
		printer.insert();
	
	/*
	p = rand() % 50 + 1;
	printer.addToQueue(5,p);
	p = rand() % 50 + 1;
	printer.addToQueue(1,p);
	p = rand() % 50 + 1;
	printer.addToQueue(8,p);
	p = rand() % 50 + 1;
	printer.addToQueue(11,p);
	
	displayQueue();
	printJob();
	displayQueue();
	printJob();
	displayQueue();
	
	p = rand() % 50 + 1;
	printer.addToQueue(3,p);
	p = rand() % 50 + 1;
	printer.addToQueue(7,p);
	p = rand() % 50 + 1;
	printer.addToQueue(2,p);
	p = rand() % 50 + 1;
	printer.addToQueue(12,p);
	p = rand() % 50 + 1;
	printer.addToQueue(9,p);
	
	while(count != 0){
		printJob();
		displayQueue();
	}*/
	printer.testRun1();		//runs first test for assignment
	/*
	int start = clock();
	int iteration = 100;
	int count = 0;*/
	printer.testRun2();
	/*
	while(count != iteration){
		printer.printJob();
		p = rand() % 50 + 1;
		printer.(p)
	*/
	
	

	int end = clock();
	return 0;
}

#endif

