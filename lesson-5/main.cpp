#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
using namespace std;
class A{
public:
    void infunc(){
        for(int i=0; i<100; i++){
            my_mutex.lock();
            my_mute2.lock();
            list.push_back(i);
            my_mutex.unlock();
            my_mute2.unlock();
            cout<<"infunc push back"<<i<<endl;
        }
    }
    
    bool out_proc(){
        my_mutex.lock();
        my_mute2.lock();
        if(!list.empty()){
            cout<<"outfunc front"<<list.front()<<endl;
            list.pop_front();
            my_mutex.unlock();
            my_mute2.unlock();
            return true;
        }
        my_mutex.unlock();
        my_mute2.unlock();
        return false;
    }
    
    
    void outfunc(){
        for(int i=0; i<100; i++){
            bool result = out_proc();
            if(result){cout<<"rm front success!";}
        }
        cout<<"end"<<endl;
    }

private:
    list<int> list;
    mutex my_mutex;
    mutex my_mute2;
};

int main(int argc, const char * argv[]) {
    A a;
    thread in_thread(&A::infunc, &a);
    thread out_thread(&A::outfunc,&a);
    in_thread.join();
    out_thread.join();
    return 0;
}
