#ifndef PRINT_C
#define PRINT_C
// =========================================================

//EC 1 Print queue
//Your name: Christopher Wendling
//Complier:  g++
//File type: printer implementation file

//===========================================================
#include <cmath>
#include <cstdlib>
#include "printer.h"

//CTOR
//--------------------------------------------------
PrintQ::PrintQ()
{
	count = rear = 0;
	for(int i = 0; i < MAX; ++i){	//initialize all values in queue
		queue[i].p_lvl = 0;
		queue[i].id = 0;
	}
	for(int i = 0; i < MEM_MAX; ++i){	//initialize all memory locations in table
		table[i].ID = table[i].priority = 0;
		table[i].state = "NULL";
	}
}
//--------------------------------------------------

void PrintQ::testRun1()
{
	addToQueue(5);
	addToQueue(1);
	addToQueue(8);
	addToQueue(11);
	
	displayQueue();
	printJob();
	displayQueue();
	printJob();
	displayQueue();
	
	addToQueue(3);
	addToQueue(7);
	addToQueue(2);
	addToQueue(12);
	addToQueue(9);
	
	while(count != 0){
		printJob();
		displayQueue();
	}
}
//--------------------------------------------------
void PrintQ::testRun2()
{
	//srand(time(NULL));
	
	int j, p;
	for(int i = 0; i < 10; ++i){	//adds ten random jobs to queue from table
		j = rand() % rear + 1;
		if((table[i-1].state != "NULL") && (table[i-1].state != "READY")){
			p = rand() % 50 + 1;
			addToQueue(i, p);
		}
		else{
			i--;
		}
	}
}
//--------------------------------------------------
//Purpose: To add an element to the queue.
//Param: type el_t given from user.
//Modified: 120113
void PrintQ::insert()
{
	/*
	if(x <= 0){		//when priority passed is invalid
		cout << "***ERROR***: '" << x << "' is an invalid priority." << endl;
		return;
	}*/
	
	if(rear == MEM_MAX)
		rear = 0;
	
	table[rear].ID = 1 + rear;
	table[rear].priority = 50;
	table[rear].state = "NEW";
	rear++;
}
//--------------------------------------------------
void PrintQ::addToQueue(int id, int p)
{
	if(count == MAX){
		table[id-1].state = "WAITING";
		return;
	}
	else{		//otherwise find next open slot
		for(int i = 0; i < MAX;){	//loops until end of queue
			if(queue[i].p_lvl > 0)	//when slot has an element increment i
				i++;
			else{		//otherwise store element in this index
				queue[i].id = id;
				queue[i].p_lvl = p;
				table[id-1].state = "READY";
				count++;
				cout << "Job inserted." << endl;
				reheapify(i);		//resorts the tree
				break;
			}
		}
	}
}
//--------------------------------------------------
//Purpose: To sort a heap tree
//Param: int index of where to begin your sort
//Modified: 120113
void PrintQ::reheapify(int index)
{
	if(count <= 0)	//when nothing in queue to sort
		return;
	else if(index == 0)		//sort from top down
		trickleDown();
	else			//sorts from specific index up to top
		trickleUp(index);
		
	cout << "Reheapified! " << endl;
}
//--------------------------------------------------
//Purpose: To take the bottom, right most element and sort it down from top.
//Modified: 120213
void PrintQ::trickleDown()
{
	if(count <= 0)		//when queue is empty
		return;
		
	el_t temp;		//holds pid elements
	int left, right;	//holds indexes 
	int j = getLast();	//hold the bottom, right most index
	temp = queue[j].id;
	queue[j].p_lvl = 0;
	queue[j].id = 0;
	queue[0].id = temp;
	queue[0].p_lvl = table[temp-1].priority;
	
	for(int i = 0; i < MAX;){	//loop until end of queue
		left = i+(i+1);		//sets left child
		right = i+(i+2);	//sets right child
		if((queue[left].p_lvl == 0) && (queue[right].p_lvl == 0))	//when parent is a leaf
			return;
		else if((queue[left].p_lvl == 0) && (queue[right].p_lvl != 0)){	//when parent only has right child
			if(queue[right].p_lvl < queue[i].p_lvl){	//and that child is less than the parent
				temp = queue[right].id;
				queue[right].p_lvl = queue[i].p_lvl;
				queue[right].id = queue[i].id;
				queue[i].id = temp;
				queue[i].p_lvl = table[temp-1].priority;
				i = right;		//moves parent index to child
			}
			else
				return;
		}
		else if((queue[right].p_lvl == 0) && (queue[left].p_lvl != 0)){	//when parent only has a left child
			if(queue[left].p_lvl < queue[i].p_lvl){		//and that child is less than the parent
				temp = queue[left].id;
				queue[left].p_lvl = queue[i].p_lvl;
				queue[left].id = queue[i].id;
				queue[i].id = temp;
				queue[i].p_lvl = table[temp-1].priority;
				i = left;		//moves parent index to child
			}
			else
				return;
		}
		else if(queue[right].p_lvl <= queue[left].p_lvl){	//when right child is smaller
			if(queue[right].p_lvl < queue[i].p_lvl){		//and is smaller than parent
				temp = queue[right].id;
				queue[right].p_lvl = queue[i].p_lvl;
				queue[right].id = queue[i].id;
				queue[i].id = temp;
				queue[i].p_lvl = table[temp-1].priority;
				i = right;		//moves parent to index of child
			}
			else
				return;
		}
		else if(queue[left].p_lvl <= queue[right].p_lvl){ //when left child is smaller
			if(queue[left].p_lvl < queue[i].p_lvl){		//and is smaller than parent
				temp = queue[left].id;
				queue[left].p_lvl = queue[i].p_lvl;
				queue[left].id = queue[i].id;
				queue[i].id = temp;
				queue[i].p_lvl = table[temp-1].priority;
				i = left;		//moves parent to index of child
			}
			else
				return;
		}
	}
}
//--------------------------------------------------
//Purpose: To sort the heap from a specific index from bottom to top.
//Param: int index of where to start.
//Modified: 120113
void PrintQ::trickleUp(int index)
{
	el_t temp;		//holds elements
	for(int i = index; i >= 0; index=i){	//loop until we reach the root
		i = getParent(index);		//gets the parent index for a child
		if(queue[i].p_lvl <= queue[index].p_lvl)	//when parent is smaller than child
			return;
		else{		//otherwise switch child with parent and continue
			temp = queue[i].id;
			queue[i].id = queue[index].id;
			queue[i].p_lvl = queue[index].p_lvl;
			queue[index].id = temp;
			queue[index].p_lvl = table[temp-1].priority;
		}
	}
}
//--------------------------------------------------
//Purpose: To return the index of a parent.
//Param: int index of the child
//Return: int index of child's parent
//Modified: 113013
int PrintQ::getParent(int i)
{
	if((i % 2) > 0)		//when child is an odd index
		i = int(floor(i / 2));
	else if((i % 2) == 0)	//when child is an even index
		i = (i / 2) - 1;
		
	return i;		//returns parent index
}
//--------------------------------------------------
//Purpose: To get the bottom, right most element's index
//Return: int index for bottom element
//Modified: 113013
int PrintQ::getLast()
{
	int i = MAX - 1;	//starts at rear of queue
	while(queue[i].p_lvl == 0)	//loops while slots are empty
		i--;
		
	if(i <= 0)		//if no element was found, queue is empty
		return 0;
		
	return i;
}
//--------------------------------------------------
//Purpose: To remove first job in queue and print it to the screen.
//Modified: 120213
void PrintQ::printJob()
{
	if(count == 0){		//when queue is empty
		cout << "Queue is empty." << endl;
		return;
	}
	else{		//otherwise print first job
		cout << "Job printed!" << "\tPriority level: " << queue[0].p_lvl << endl;
		table[(queue[0].id)-1].state = "TERMINATED";
		queue[0].p_lvl = 0;	//clears first job from queue
		queue[0].id = 0;
		cout << "Jobs left: " << --count << endl;
		reheapify(0);	//resorts the heap
	}
}
//--------------------------------------------------
//Purpose: To display all remaining jobs in queue
//Modified: 113013
void PrintQ::displayQueue()
{
	if(count == 0){		//when queue is empty
		cout << "Nothing to display." << endl;
		return;
	}
    cout << "\n[";
    for(int i = 0; i < count; ++i){		//displays only up to number of jobs not entire queue
		cout << "(ID:" << queue[i].id << ",Lvl:" << queue[i].p_lvl << ")";
		if(i != count - 1)	//when not at last element
			cout << ", ";
	}
	cout << "]" << endl;
}

#endif

