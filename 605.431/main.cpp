/**
 * 605.431 - Principles of Operating Systems
 * @date December 15th, 1999
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Simulator.h"
#include "ListNode.h"
#include "List.h"

const double mean = 2.0;
enum boolean {FALSE = 0, TRUE };
using namespace std;


/**
 * This is the main method for the program.  As of right now, it does
 * not take any parameters.  Creates Simulator object and then calls randomize()
 * and performSimulation()
 * @return
 */
int main()
{
	/**
	 * Object to access class Simulator
	 * Object name is "s" to access class data
	 */
	Simulator s;
	s.randomizeSeed();
	s.performSimulation();
	return 0;
}


/**
 * Description:  Method performSimulation calls the method readfile(). Next 2 processor lists
 * are filling containing a max 15 processes per list.  These are process nodes (listNode objects)
 * from the processList and are sorted by priority.  A while oopp is then used to simulate the
 * computer close and incremented counter is use to simulate the clock allowing the program to
 * keep track of how long a process takes in its related processor.
 *
 */
void Simulator::performSimulation()
{
	readFile();
	loadProcessorLists();
}



/**
 * Method:  readfile() reads the data in the input file. As each
 * process with its related data is read, it is placed into variables
 * within an object called process of the class ListNode.  The object process
 * is then inserted at the end of a doubly linked list object called processList
 * of class List.  It should maintain the original file order of the process.
 */
void Simulator::readFile()
{

	int processNumber;
	int initialPriority;
	char cpuIntStr[ 20 ];
	char ioIntStr[ 20 ];
	int resourceActivityNum;
	char fourTupStr[ 40 ];
	char arrivalIntervalStr[ 20 ];

	ifstream inputFile;
	//For now, I hard-coded the input file found in the directory
	inputFile.open("input_file.txt");
	//Can't find the inputFile
	if(!inputFile){
		cout << "Couldn't open the file!" << endl;
		exit(1);
	}
	else
	{
		cout << "File was opened for reading " << endl;

	}

	cout << "Reading in data from file" << endl;
	cout << "Putting data from each process into a process list" <<
	endl << endl;

	while(inputFile)
	{

		inputFile >> processNumber;
		if( processNumber == 999)
			break;
		inputFile >> initialPriority;
		inputFile >> cpuIntStr;
		inputFile >> ioIntStr;
		inputFile >> resourceActivityNum;
		inputFile >> fourTupStr;
		inputFile >> arrivalIntervalStr;

		cout << endl;
		cout << processNumber << " "
		<< initialPriority << " "
		<< cpuIntStr << " "
		<< ioIntStr << " "
		<< resourceActivityNum << " "
		<< fourTupStr << " "
		<< arrivalIntervalStr << endl;

		// create a new process object of class ListNode
		ListNode* process = new ListNode; //new object called process
		// fill up current process object with process data
		process->setProcessNumber( processNumber);
		process->setInitialPriority( initialPriority );
		process->setCPUIntStr(cpuIntStr );
		process->setIOIntStr(ioIntStr );
		process->setResourceActivityNum( resourceActivityNum );
		process->setFourTupleStr( fourTupStr );
		process->setArrivalIntervalStr( arrivalIntervalStr );
		process->setProcessTime(getTimeStamp());

		if (inputFile.eof()){
			processList.insertProcess(process);
			break;
		}
		else{
			// insert process object at end of the processList
			processList.insertProcess(process );

		}

	}

	inputFile.close();
	cout << endl << "Displaying completed process list" << endl;
	processList.displayProcesses();

}

/**
 * Method name:  insertProcess inserts a process into the list
 * @tparam T
 * @param type
 * @return
 */
template <class T>
int List<T>::insertProcess(T* type)
{
	newptr = type;
	//If list is empty, insert first process
	if(front == 0) {
		last = front = newptr;
		*front = *type;
		front->rptr = front->lptr = 0;
		return 1;
}
	//If list is not empty, insert process
	if( last != 0)	{
		*newptr = *type;
		newptr->rptr = 0;
		newptr->lptr = last;
		last->rptr = newptr;
		last = newptr;
	}

	return 0;
}

/**
 * Method entries returns the number of nodes currently in the list
 * @tparam T
 * @return
 */
template <class T>
int List<T>::entries()
{
	T* p;
	int nodeCounter = 0;
	if( front == 0 ){
		nodeCounter = 0;
	}
	else {
		p = front;
		while (p) {
			nodeCounter++;
			p = p->rptr;
		}
	}
	return nodeCounter;

}

/**
 * Method getFirstProcess() returns the first process in the list and deletes it from the list
 * @tparam T
 * @return
 */
template <class T>
T* List<T>::getFirstProcess()
{
	if( front != 0 ) {
		temp = front;
		front = front->rptr;
	}
	if(front != 0)
	{
		front->lptr = 0;
	}
	if( front == 0 )
	{
		return front;
	}
return temp;
}


/**
 * Method gets the first process
 * @tparam T
 * @return
 */
template <class T>
T* List<T>::firstProcess()
{
	return front;
}


/**
 * Method displays all the process data in the list
 * @tparam T
 */
template <class T>
void List<T>::displayProcesses()
{
	temp = front;
	while (temp){
		cout << endl;


		cout << endl << endl << "processNumber = " << temp->processNumber << endl << "initialPriority = " << temp->initialPriority << endl
		<< "cpuIntStr = " << temp->cpuIntStr << endl << "ioIntStr = " << temp->ioIntStr << endl << "resourceActivityNum = " << temp-> resourceActivityNum << endl
		<< "fourTupleStr = " << temp->fourTupleStr << endl
		<< "fourTuple.fileNum = " << temp->fourTuple.fileNum
		<< endl << "fourTuple.diskNum = " << temp->fourTuple.diskNum << endl
		<< "fourTuple.rwType = " << temp->fourTuple.rwType << endl
		<< "fourTuple.openFileActivityNum = " << temp->fourTuple.openFileActivityNum << endl
		<< "fourTuple.closeFileActivityNum = " << temp->fourTuple. closeFileActivityNum << endl
		<< "arrivalIntervalStr = " << temp->arrivalIntervalStr << endl
		<< "processTime = " << temp->processTime << endl;
		temp = temp->rptr;
	}

}

/**
 * Method:  randomNum returns a randomly decided integer between a given
 * minimum and max number
 * @param minNum
 * @param maxNum
 * @return
 */
int ListNode::getRandomNum( int minNum, int maxNum)
{
	int x = 1;
	int num = 0;
	while( x ){
		num = (rand()/1000);
		if((num >= minNum)	&& ( num <= maxNum ) ) {
			x = 0;
		}
	}
	return num;
}

/**
 * Description: Method parseString extracts the min and max numbers
 * from a string containing the format " i,j " where i = minNum and
 * j = maxNum. The arguments minNum and maxNum are passed to the method randomNum.
   Method randomNum returns a random decimal number between the min and max
 * @param str
 * @return
 */
int ListNode::parseString(char *str)
{
	char minStr[10];
	char maxStr[10];
	int i = 0, j = 0;
	int maxInt = 0;
	int minInt = 0;

	while(str[i] != ',')
	{
		minStr[i] = str[i];
		i++;
	}
	minStr[i] = '\0';
	i++;
	while(str[i] != '\0')
	{
		maxStr[j] = str[i];
		j++;
		i++;

	}

	maxStr[j] = '\0';

	minInt = atoi(minStr);
	maxInt = atoi(maxStr);

	return(getRandomNum(minInt, maxInt));

}

/**
 * Method:  Method parseTuple returns a struct FourTuple containing
 * usable data extracted from a string (4 tuple from one process
 * foudn in the file (per line)
 * @param str
 */
void ListNode::parseTupleString(char *str)
{
	char tempFDStr[20]; // holds temp FiDj in a string
	char tempStr[20]; // temp string for parsing
	int i = 0, j = 0, jj = 0;
	boolean loop = TRUE;
	fourTuple.fileNum = 0;
	fourTuple.diskNum = 0;
	fourTuple.closeFileActivityNum = 0;

	/*
	 * Begin parsing the FiDj values within the process line
	 */
	while (str[i] != ',' ){
		tempFDStr[i] = str[i];
		i++;
	}

	tempFDStr[i] = '\0';
	i++;
	j = 0;
	jj = 0;

	if ((tempFDStr[j] == 'F') || (tempFDStr[j] == 'f')){
		j++;
		/*
		 * while boolean true
		 */
		while(loop){
			tempStr[jj] = tempFDStr[j];
			j++;
			jj++;
			if ((tempFDStr[j] == 'D') || (tempFDStr[j] == 'd')){
				loop = FALSE;
			}

		}

		tempStr[jj] = '\0';
		fourTuple.fileNum = atoi(tempStr);
		j++;
		jj = 0;

		while (j <= strlen(tempFDStr)){
			tempStr[jj] = tempFDStr[j];
			j++;
			jj++;
		}
		tempStr[jj] = '\0';
		fourTuple.diskNum = atoi(tempStr);
	}

	/*
	 * Parsing read/write type
	 * within the tuple string
	 */
	j = 0;
	while(str[i] != ','){
		fourTuple.rwType[j] = str[i];
		i++;
		j++;
	}

	fourTuple.rwType[j] = '\0';
	i++;

	//parse for file open activity number
    j = 0;
	while (str[i] != ',') {
		tempStr[j] = str[i];
		i++;
		j++;
	}
	tempStr[j] = '\0';
	fourTuple.openFileActivityNum = atoi(tempStr);
	i++;

	//parse for file close activity number
	j = 0;
	while (str[i] != '\0')
	{
		tempStr[j] = str[i];
		i++;
		j++;
	}

	tempStr[j] = '\0';
	fourTuple.closeFileActivityNum = atoi(tempStr);

	/*
	 * print out our values
	 */
	cout << "tempFDStr = " << tempFDStr << endl;
	cout << "fourTuple.fileNum = " << fourTuple.fileNum << endl;
	cout << "fourTuple.diskNum = " << fourTuple.diskNum << endl;
	cout << "fourTuple.rwType = " << fourTuple.rwType << endl;
	cout << "fourTuple.openFileActivityNum = " <<
	fourTuple.openFileActivityNum << endl;
	cout << "fourTuple.closeFileActivityNum = " <<
	fourTuple.closeFileActivityNum << endl;
}


/**
 * Method name:  randomize()
 * Description:  Randomize method, changes seed to fixed user-supplied value or if 0, sets
 * seed to a randomly selected value for different results from run to run.
 * @param seed
 */
void Simulator::randomizeSeed(int seed)
{
	if (seed == 0) {
		srand (unsigned (time (NULL)));
	}else
		//you can replace with any integer, don't want the same sequence every time
		//can use this for testing reason
		srand (seed);
}

/**
 * Method:  procArriveTime  determines at what time the process arrives.
 * It returns the number of simulate minutes as a double
 * @param mean
 * @return
 */
double Simulator::procArriveTime(double mean){
	double r = rand();
	r /= RAND_MAX;
	return -mean*log(r);
	}

/**
 * Method:  getTimeStamp cacluates the time that each job enters its processor
 * @return
 */
double Simulator::getTimeStamp()
{
	timeSpan = procArriveTime(mean);
	entryTime += timeSpan;
	return entryTime;
}

/**
 *
 * @return 1 or 2 random value
 */
int Simulator::randomNum(){

	int i = ((rand() % 10));
	if ( i < 5 )
		return 1;
	else
		return 2;
}



/**
 * Method:  Pops process from the processList and examines it priority (not implemented yet).  A random
 * processor is then selected.  If the candidate processor list contains < 15 processes it is put into that processor list.
 */
void Simulator::loadProcessorLists()
{
	int processorNum = 0;
	cout << endl;
	temp = processList.getFirstProcess();
	while( temp != 0 ){
		ListNode* tempProcess = new ListNode;
		*tempProcess = *temp;
		processorNum = randomNum(); //picks a random processor, either CPU1 or CPU2
		if( processorNum == 1 ){
			if( proclList.entries() < 15 ){
				cout << "Entering process: " << temp->getProcessNumber() << " into Processor list " << processorNum << endl;
				proclList.insertProcess( tempProcess );
			}
			else{
				//cout << processorNum << " has reached its capacity" << endl;
				if(proc2List.entries() < 15)
				{
					cout << "Entering process " << temp-> getProcessNumber() << " into Processor list  " << processorNum << endl;
					proc2List.insertProcess(tempProcess);
				}

				}
			}

		if( processorNum == 2){
			if(proc2List.entries() < 15)
			{
				cout << "Entering process: " << temp->getProcessNumber() << " into Processor list " << processorNum << endl;
				proc2List.insertProcess(tempProcess);
			}
			else{
				//cout << processorNum << " has reached its capacity" << endl;
				if(proclList.entries() < 15){
					cout << "Entering process: " << temp->getProcessNumber() << " into Processor list " << processorNum << endl;
					proclList.insertProcess(tempProcess);
				}

			}

		}
		temp = temp->getRptr();
		cout << endl;
		cout << proclList.entries() << " process(s) in Processor 1 List " << endl;
		cout << proc2List.entries() << " process(s) in Processor 2 List" << endl;


/*
		if((newptr->getInitialPriority() > last->getInitialPriority()) && (last->rptr == 0)){
			newptr->rptr = 0;
			newptr->lptr = last;
			last->rptr = newptr;
			*newptr = *type;
			return 1;
		}
*/
	}
}




