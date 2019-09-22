#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
using namespace std;
class A{
public:
    void infunc(){
        for(int i=0; i<5; i++){
            my_mutex.lock();
            list.push_back(i);
            my_mutex.unlock();
            cout<<"infunc push back"<<i<<endl;
        }
    }
    
    bool out_proc(){
        my_mutex.lock();
        if(!list.empty()){
            cout<<"outfunc front"<<list.front()<<endl;
            list.pop_front();
            my_mutex.unlock();
            return true;
        }
        my_mutex.unlock();
        return false;
    }
    
    
    void outfunc(){
        for(int i=0; i<5; i++){
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
