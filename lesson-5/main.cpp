#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void myprint(const int i){//改晨string 隐式转换
    std::cout<<"myprint: "<<i<<" thread_id: "<<std::this_thread::get_id()<<std::endl;
    return;
}

int main(int argc, const char * argv[]) {
    std::vector<std::thread> myth;
    for(int i=0; i<10; i++){
        myth.push_back(thread(myprint, i));//创建并开始执行线程
    }
    for(auto iter = myth.begin(); iter != myth.end(); ++iter){
        iter->join();//等待10个线程都返回
    }
    cout<<"in main"<<endl;
    return 0;
}
