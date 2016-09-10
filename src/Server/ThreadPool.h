/*********************************************
* ThreadPool.h
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* A class which manages a pool of threads.
*
*
*********************************************/

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <vector>
#include <iostream>

class ThreadPool{
private:
protected:
	unsigned short maxThreads;
public:
	virtual int allocThread(void* function (void*), void* args = NULL) = 0;
	virtual void freeThread(int threadIndex) = 0;
	virtual int numOfAvlblThreads() = 0;
	virtual int getMaxThreads() = 0;
};

class ThreadPool_v1: public ThreadPool{
private:
	pthread_t* threads;
	std::vector<unsigned short>* freeThreads; //indexes of free threads
	//include a list of listeners
protected:
public:
	ThreadPool_v1(unsigned short max_threads = 8);
	~ThreadPool_v1();
	int allocThread(void* function (void*), void* args = NULL);
	void freeThread(int threadIndex);
	int numOfAvlblThreads();
	int getMaxThreads();
};


#endif
