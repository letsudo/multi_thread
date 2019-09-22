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
            std::lock(my_mutex,my_mute2);
            std::lock_guard<mutex> my1(my_mutex, adopt_lock); //已经lock过了，不会再次lock
            std::lock_guard<mutex> my2(my_mute2, adopt_lock); //已经lock过了，不会再次lock
            list.push_back(i);
            cout<<"infunc push back"<<i<<endl;
        }
    }
    
    bool out_proc(){
        std::lock(my_mutex,my_mute2);
        std::lock_guard<mutex> my1(my_mutex, adopt_lock); //已经lock过了，不会再次lock
        std::lock_guard<mutex> my2(my_mute2, adopt_lock); //已经lock过了，不会再次lock
        if(!list.empty()){
            cout<<"outfunc front"<<list.front()<<endl;
            list.pop_front();
            return true;
        }
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
