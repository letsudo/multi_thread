#include <iostream>
#include <thread>
using namespace std;
class TA
{
public:
    int m_i;
    TA(int i):m_i(i){
        std::cout<<"构造函数"<<"thread_id: "<<std::this_thread::get_id()<<std::endl;
    }
    TA(const TA &ta):m_i(ta.m_i){
        std::cout<<"拷贝构造函数"<<"thread_id: "<<std::this_thread::get_id()<<std::endl;
    }
    ~TA(){
        std::cout<<"析构函数"<<"thread_id: "<<std::this_thread::get_id()<<std::endl;
    }
};

void myprint(const int i, const TA &p){//改晨string 隐式转换
    cout<<i<<endl; //**不是引用，是值传递**
    std::cout<<"myprint"<<"thread_id: "<<std::this_thread::get_id()<<std::endl;
}
int main(int argc, const char * argv[]) {
    // 传递临时变量作为线程参数
    int var =1;
    std::cout<<"主线程id: "<<"thread_id: "<<std::this_thread::get_id()<<std::endl;
    thread t(myprint, 1, TA(var));// 采用临时构造传递参数是可行的，这个转换到stirng的过程先于main函数的结束，会先完成转换，避免临时变量失效，视频中采用字写类测试，此处会调用构造函数和拷贝构造函数
    t.join();
//    t.detach();
    cout<<"Hi in main"<<endl;
    return 0;
}
