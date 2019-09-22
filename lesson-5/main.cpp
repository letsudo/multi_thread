#include <iostream>
#include <thread>
#include <vector>
#include <list>
using namespace std;
class A{
public:
    void infunc(){
        for(int i=0; i<1000; i++){
            list.push_back(i);
            cout<<"infunc push back"<<i<<endl;
        }
    }
    
    void outfunc(){
        for(int i=0; i<1000; i++){
            if(!list.empty()){
                cout<<"outfunc front"<<list.front()<<endl;
                list.pop_front();
            }else{
                cout<<"list empty"<<endl;
            }
        }
        cout<<"end"<<endl;
    }

private:
    list<int> list;
};

int main(int argc, const char * argv[]) {
    A a;
    thread in_thread(&A::infunc, &a);
    thread out_thread(&A::outfunc,&a);
    in_thread.join();
    out_thread.join();
    return 0;
}
