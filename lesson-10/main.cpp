#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <future>
using namespace std;
int mythread(){
    cout<<"my thread start thread id:\t"<<this_thread::get_id()<<endl;
    chrono::milliseconds dura(5000);
    this_thread::sleep_for(dura);
    cout<<"my thread end thread id:\t"<<this_thread::get_id()<<endl;
    return 5;
}

int main(int argc, const char * argv[]) {
    
    // 一 async，future 创建后台任务并返回值
    //希望子线程返回一个结果
    //std::async 是函数模板，用来启动一个异步任务， 启动后返回一个std::future 对象
    //std::future  类模版
    //启动一个异步任务： 就是自动创建一个线程并开始执行线程的入口函数，返回future包含线程的返回结果，可以通过调用future的get（）获得结果
    //futrue 在线程执行完毕后能拿到的结果
    cout<<"main thread id:\t"<<this_thread::get_id()<<endl;
    std::future<int> result = std::async(mythread); //创建一个线程并开始执行
    cout<<"continue!"<<endl;
    cout<<result.get()<<endl;//卡在这里等待mythread执行完拿到结果
//    cout<<result.get()<<endl;//只能调用一次，调用多次崩溃
//    result.wait() //仅等待线程返回，并不获取结果
    cout<<"done!"<<endl;
    return 0;
}
