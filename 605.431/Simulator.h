/**
 * 605.431
 * @date 12/15/99
 */

#include <stdio.h>
#include <math.h>
#include "List.h";
#include "ListNode.h";
#include <string.h>
#ifndef SIMULATOR_H_
#define SIMULATOR_H_


class Simulator
{
//Access specifier, accessible outside this class
public:

	/**
	 * Constructor
	 */
	Simulator() : timeSpan(0.0){}
	/**
	 * Destructor:  Simulator
	 */
	~Simulator() {}
	//passing in seed with value of 0
	static void randomizeSeed(int seed = 0); //seed is 0, random
	double procArriveTime(double mean);
	double getTimeStamp();
	double getEntryTime(){return entryTime;}

	List<ListNode> processList;
	ListNode* temp;
	List<ListNode> proclList;
	List<ListNode> proc2List;
	int randomNum();
	void readFile();
	void loadProcessorLists();
	void performSimulation();
private:
	double timeSpan;
	double entryTime;
};


#endif /* SIMULATOR_H_ */
