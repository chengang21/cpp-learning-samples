/**
  tested using compiler option: -std=c++14  -static-libgcc
*/
// thread & mutex
#include <thread>
#include <mutex>

// queue & vector
#include <queue>
#include <vector>
#include <cstdio>

// random, usleep,  time
#include <cstdlib>
#include <unistd.h>
#include <time.h>

using std::queue;
using std::thread;
using std::mutex;
using std::vector;

queue<int> message;
bool all;
mutex lock;

void producer(){
	all = false;
	for (int i = 0; i < 10; ++i){
	
		lock.lock();  
		
		if (message.size() < 5)
			message.push(rand() % 1000);
			
		lock.unlock();  
		
		// sleep 0 - 999 milis 
		usleep((rand() % 1000) * 1000);
	}
	all = true;
}

void consumer(int id){
	
	while(!all)
	{
		lock.lock();  
		
		if (message.size() > 0){
			int m = message.front(); message.pop();
			printf("thread %d: %d\n", id, m);
		}
		
		lock.unlock();  
		
		// sleep 500 milis 
		usleep(500 * 1000);
	}
}

int main(){
	srand(time(NULL));
	vector<thread> c;
	
	thread p(producer);
	
	for (int i = 0; i < 3; i++){
		c.push_back(thread(consumer, i));
	}
	
	p.join();
	
	for (int i = 0; i < 3; i++){
		c[i].join();
	}
}


