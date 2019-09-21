#include <iostream>
#include <thread>

class TA
{
public:
//    int m_i;
//    TA(int i):m_i(i){
//        std::cout<<"构造函数"<<std::endl;
//    }
    void operator()()
    {
        std::cout<<"operator"<<std::endl;
    }
};


int main(int argc, const char * argv[]) {
    
    TA ta;
    std::thread t1(ta);
    //join加入汇合、阻塞
//    t1.join();//主线程等待t1子线程执行完毕
//    t1.detach();//不等待， 一旦被detach 就不能被join了
    if(t1.joinable()){
        t1.join();
    }
    std::cout<<"af operator in main"<<std::endl;
    return 0;
}
