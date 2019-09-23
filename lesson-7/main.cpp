#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
using namespace std;
class A{
public:
    void infunc(){
        for(int i=0; i<1000; i++){
            std::unique_lock<mutex> my1(my_mutex);
            std::mutex *ptx = my1.release();
            list.push_back(i);
            ptx->unlock();
        }
    }
    
    bool out_proc(){
        
        std::lock_guard<mutex> my1(my_mutex); //已经lock过了，不会再次lock
//        std::chrono::milliseconds dura(20000);
//        cout<<"start sleep"<<list.front()<<endl;
//        std::this_thread::sleep_for(dura);
        if(!list.empty()){
            cout<<"outfunc front"<<list.front()<<endl;
            list.pop_front();
            return true;
        }
        return false;
    }
    
    
    void outfunc(){
        for(int i=0; i<1000; i++){
            bool result = out_proc();
            if(result){cout<<"rm front success!";}
        }
        cout<<"end"<<endl;
    }

private:
    list<int> list;
    mutex my_mutex;
};

int main(int argc, const char * argv[]) {
    A a;
    thread in_thread(&A::infunc, &a);
    thread out_thread(&A::outfunc,&a);
    in_thread.join();
    out_thread.join();
    return 0;
}
