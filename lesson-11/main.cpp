#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <future>
using namespace std;

int mythread(int para){
    cout<<para<<endl;
    cout<<"my thread start thread id:\t"<<this_thread::get_id()<<endl;
    chrono::milliseconds dura(5000);
    this_thread::sleep_for(dura);
    cout<<"my thread end thread id:\t"<<this_thread::get_id()<<endl;
    return 5;
}

int main(int argc, const char * argv[]) {

    int temp =12;
    cout<<"main thread id:\t"<<this_thread::get_id()<<endl;
//    std::future<int> result = std::async(mythread); //创建一个线程并开始执行
    std::future<int> result = std::async(mythread,temp); //创建一个线程并开始执行
    std::future_status status = result.wait_for(std::chrono::seconds(6)); //等待一秒， 如果是deferred这里不会等待
     cout<<"continue!"<<endl;
    if( status == std::future_status::timeout){ //超时
        cout<<"time out"<<endl;
    }else if( status == std::future_status::ready){
        cout<<"ready"<<endl;
         cout<<result.get()<<endl;//卡在这里等待mythread执行完拿到结果
    }else if (status == std::future_status::deferred){
        // 如果async 的第一个参数被设置为deferred， 则次条件成立
         cout<<"deferred"<<endl;
         cout<<result.get()<<endl;//卡在这里等待mythread执行完拿到结果
    }
   
    cout<<"done!"<<endl;
    return 0;
}
