/*********************************************
* ThreadPool.cpp
* Created By: Adam Kozlowski
* Last Updated: 8/4/2016
* A class which manages a pool of threads.
*
*
*********************************************/
#ifdef DEBUG
#include <iostream>
#include <stdio.h>
#endif

#include <pthread.h>
#include <vector>
#include <iostream>

class ThreadPool{
private:
protected:
	unsigned short maxThreads;
public:
	virtual int allocThread(void* function (void*), void* args = NULL) = 0;
	virtual void freeThread(int index) = 0;
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
	ThreadPool_v1(unsigned short max_threads = 8){

		maxThreads = max_threads;
		threads = new pthread_t[maxThreads];
		freeThreads = new std::vector<unsigned short>;
		for(unsigned short i = 0; i < maxThreads; i++){
			freeThreads->push_back(i);
		}

	}
	~ThreadPool_v1(){
		delete[] threads;
		delete freeThreads;
	}
	int allocThread(void* function (void*), void* args = NULL){
		if(!freeThreads->empty()){
			int threadIndex = freeThreads->at(freeThreads->size()-1);
			int thread_error = pthread_create(&threads[threadIndex], NULL, 
				function, args);
			if(!thread_error){
				freeThreads->pop_back();
				return threadIndex;
			}
			else{
				std::cerr << "Error Allocating Thread : " << i << std::endl;
				return -1;
			}
		}
		else{
			return -1;
		}
	}

	void freeThread(int threadIndex){
		pthread_join(threads[threadIndex], NULL);
		freeThreads->push_back(threadIndex);
		//update listeners
		return;
	}

	int numOfAvlblThreads(){
		return freeThreads->size();
	}

	int getMaxThreads(){
		return (int)maxThreads;
	}
};

#ifdef DEBUG
void *overFlow(void*){
	return 0;
}
void *testAlloc(void*){
	pthread_t threadid = pthread_self();
	if(threadid > 0)
		std::cout<< threadid << " : TestAlloc Passed\n";
	else
		std::cout << "TestAlloc Failed\n";
	return 0;
}

void testFree(ThreadPool& tp, int index){
	int beforeFree = tp.numOfAvlblThreads();
	tp.freeThread(index);
	int afterFree = tp.numOfAvlblThreads();
	if(afterFree > beforeFree)
		std::cout<<"TestFree Passed\n";
	else
		std::cout<<"TestFree Failed\n";
}

void testOverAlloc(ThreadPool& tp){
	int indexes[tp.getMaxThreads()];
	for(int i = 0; i < tp.getMaxThreads(); i++){
		indexes[i] = tp.allocThread(overFlow, NULL);
		printf("Thread Pool has %i of %i threads left\n", tp.numOfAvlblThreads(), tp.getMaxThreads());
	}
	int negOne = tp.allocThread(testAlloc, NULL);
	if(negOne == -1)
		std::cout << "OverAllocTest Passed\n";
	else
		std::cout << "OverAllocTest Failed\n";

	for(int i = 0; i < tp.getMaxThreads(); i++){
		tp.freeThread(indexes[i]);
		printf("Thread Pool has %i of %i threads left\n", tp.numOfAvlblThreads(), tp.getMaxThreads());
	}

}

/*/ 
int main(){
	ThreadPool* tp = new ThreadPool_v1();
	printf("Thread Pool has %i of %i threads left\n", tp->numOfAvlblThreads(), tp->getMaxThreads());
	int index = tp->allocThread(testAlloc, NULL);
	printf("Thread Pool has %i of %i threads left\n", tp->numOfAvlblThreads(), tp->getMaxThreads());
	testFree(*tp, index);
	printf("Thread Pool has %i of %i threads left\n", tp->numOfAvlblThreads(), tp->getMaxThreads());
	testOverAlloc(*tp);
	
	return 0;
}
//*/

#endif