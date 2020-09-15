/**
 * 605.421 - Principles of Operating Systems
 * @date 12/15/99
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_



class ListNode {
    friend List <ListNode> ;
    public:
        ListNode():processTime(0), lptr(0), rptr(0) {} //constructor
        ~ListNode() {} //Destructor
		int getRandomNum(int minNum, int maxNum); //Creates a random integer from min to max
		int parseString(char *str); //Extracts the min and max strings from a string
		void parseTupleString(char* str); //Extracts the [FiDj], read or write, i, j into a struct

		/**
		 * Set method called setProcessNumber
		 * @param _processNumber is the process number as it comes in
		 */
		void setProcessNumber(int _processNumber) {
			processNumber = _processNumber;
		}
		void setInitialPriority(int _initialPriority) {
			initialPriority = _initialPriority;
		}
		void setCPUIntStr(char* _cpuIntStr) {
			strcpy(cpuIntStr, _cpuIntStr);
			cpuInt = parseString(cpuIntStr);
		}

		void setIOIntStr(char * _ioIntStr) {
			strcpy(ioIntStr, _ioIntStr);
			ioInt = parseString(ioIntStr);
		}
		void setResourceActivityNum(int _resourceActivityNum) {
			resourceActivityNum = _resourceActivityNum;
		}
		void setFourTupleStr(char* _fourTupleStr) {
			strcpy(fourTupleStr, _fourTupleStr);
			parseTupleString(_fourTupleStr);

		}
		void setArrivalIntervalStr(char * _arrivalIntervalStr) {
			strcpy(arrivalIntervalStr, _arrivalIntervalStr);
			arrivalInterval = parseString(arrivalIntervalStr);
		}
		void setProcessTime(double _processTime) {
			processTime = _processTime;
		}

		/**
		 * Get method getProcessNumber()
		 * @return processNumber
		 */
		int getProcessNumber() {
			return processNumber;
		}
		int getInitialPriority() {
			return initialPriority;
		}

		char * getCPUIntStr() {
			return cpuIntStr;
		}
		int getCPUInt() {
			return cpuInt;
		}
		char * getIOIntStr() {
			return ioIntStr;
		}

		int getIOInt() {
			return ioInt;
		}
		int getResourceActivityNum() {
			return resourceActivityNum;
		}

		char * getFourTupleStr() {
			return fourTupleStr;
		}

		char * getArrivalIntervalStr() {
			return arrivalIntervalStr;
		}
		int getArrivalInterval() {
			return arrivalInterval;
		}

		double getProcessTime() {
			return processTime;
		}

		ListNode * getRptr() {
			return rptr;
		}

		ListNode * getLptr() {
			return lptr;
		}

	/**
	 * Data being used during processing
	 * of the event taking place.
	 */
    private:
        int processNumber;
		int initialPriority;
		int cpuInt;
		int ioInt;
		int resourceActivityNum;
		struct FourTuple{
			int fileNum;
			int diskNum;
			char rwType[10];
			int openFileActivityNum;
			int closeFileActivityNum;
		} fourTuple;
int arrivalInterval;
// temp variables

char cpuIntStr[20];
char ioIntStr[20];
char fourTupleStr[40];
char arrivalIntervalStr[20];
double processTime;

ListNode * lptr;
ListNode * rptr;
};


#endif /* LISTNODE_H_ */
