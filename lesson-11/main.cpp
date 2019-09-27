#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <future>
#include <atomic>
using namespace std;

std::atomic<int> g_int;
mutex my_mutex;

void mythread(){
    for(int i=0; i<100000000 ;i++){
//        my_mutex.lock();
        g_int++;
//        my_mutex.unlock();
    }
}

int main(int argc, const char * argv[]) {
    // 三、 原子操作 std::atomic
    //互斥量： 多线程中保护共享数据
    //两个线程，对一个变量进行操作，一个线程读值， 一个线程写值
    //原子操作：不会被打断的执行片段，原子操作的效率比加锁要高，但锁可以对代码段进行加锁，原子操作一一般仅针对一个变量
    thread t1(mythread);
    thread t2(mythread);
    t1.join();
    t2.join();
    cout<<g_int<<endl;
    return 0;
}
