#include <stdio.h>
#include <math.h>
#include <string.h>

#ifndef LIST_H_
#define LIST_H_

/**
 * 605.431
 * @date 12/15/99
 */

template<class T>
class List
{
public:
	/**
	 * Constructor called when object is being created
	 */
    List(): front(0),
    last(0),
    newptr(0),
    temp(0)
	{}

    /**
     * Destructor for List
     */
    ~List() {}  //destructor
    int insertProcess(T* type);  //inserts object at end of list
	int insertProcessSorted(T * type); // inserts object sorted by project definitions
	T * getFirstProcess(); // returns first element
	T * firstProcess(); // returns pointer to first element in the list.
	void displayProcesses(); // displays data in each node of the list
	int entries(); // returns number of nodes in the list.

protected:
	T* front;
	T* last;
	T* newptr;
	T* temp;

};


#endif /* LIST_H_ */
