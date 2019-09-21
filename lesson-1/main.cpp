#include <iostream>
#include <thread>

class TA
{
public:
    int m_i;
    TA(int i):m_i(i){
        std::cout<<"构造函数"<<std::endl;
    }
    TA(const TA &ta):m_i(ta.m_i){
        std::cout<<"拷贝构造函数"<<std::endl;
    }
    ~TA(){
        std::cout<<"析构函数"<<std::endl;
    }
    void operator()()
    { 
        std::cout<<"operator"<<std::endl;
    }
};


int main(int argc, const char * argv[]) {
    
    TA ta(1);
    std::thread t1(ta);//调用拷贝构造函数
    //join加入汇合、阻塞
    t1.join();//主线程等待t1子线程执行完毕
//    t1.detach();//不等待， 一旦被detach 就不能被join了
//    if(t1.joinable()){
//        t1.join();
//    }
    std::cout<<"af operator in main"<<std::endl;
    return 0;
}
