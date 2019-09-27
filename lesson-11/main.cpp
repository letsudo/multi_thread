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

int mythread2(std::shared_future<int> &temp){
    cout<<"my thread start thread id:\t"<<this_thread::get_id()<<endl;
    chrono::milliseconds dura(5000);
    this_thread::sleep_for(dura);
    cout<<"my thread end thread id:\t"<<this_thread::get_id()<<endl;
    auto result = temp.get();
    cout<<result<<endl;
    return 0;
}

int main(int argc, const char * argv[]) {
    //三、std::shared_future 类模板，普通future的get函数是将数据转移，类似于move， shared_future 是的get是复制
    
   
    cout<<"main thread id:\t"<<this_thread::get_id()<<endl;
    std::packaged_task<int(int)> mypt(mythread);//我们把函数mythread通过packaged_task包装起来
    std::thread t1(std::ref(mypt),1);//线程直接开始执行，第二个参数作为线程入口函数的参数
    t1.join();//等待线程执行完毕
    std::shared_future<int> result_s = mypt.get_future();//std::future 包含线程入口函数的返回结果，
//    bool val = result.valid();
////    std::shared_future<int> result_s(std::move(result));
//    std::shared_future<int> result_s(result.share()); //执行完毕后result_s 里面有值， 而result里面空了
//    val = result.valid();
//
//    auto result___ = result_s.get();
//    result___ = result_s.get();
    std::thread t2(mythread2, std::ref(result_s));
    t2.join();
    cout<<"done!"<<endl;
    return 0;
}
