#include <iostream>
#include <thread>

void function(){
    std::cout<<"hi in function"<<std::endl;
}


int main(int argc, const char * argv[]) {
    std::thread t1(function);//创建t1子线程，并执行
//    t1.join();//主线程等待t1子线程执行完毕
    t1.detach();//不等待， 一旦被detach 就不能被join了
    if(t1.joinable()){
        t1.join();
    }
    return 0;
}
