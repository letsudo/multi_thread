#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
using namespace std;
class A{
public:
    //转移所有权
    std::unique_lock<mutex> rtn_unique_lock(){
        std::unique_lock<mutex> mu1(my_mutex);
        return mu1;
    }
    void infunc(){
        for(int i=0; i<1000; i++){
            std::unique_lock<mutex> my1(my_mutex);
            std::mutex *ptx = my1.release();
            list.push_back(i);
            my_condition.notify_one();//尝试把wait（）线程唤醒
            cout<<"push_back"<<endl;
            ptx->unlock();
        }
    }
    
    
    void outfunc(){
        int command =0;
        while(true){
            std::unique_lock<mutex> my1(my_mutex);
            //wait 用来等一个东西
            //如果第二个参数返回时true，wait直接返回
            //如果第二个参数的lambda返回值是false，那么wiat将解锁互斥量，并阻塞到本行
            //堵到其他摸个线程滴哦啊用notify_one 成员函数为止
            //如果wait没有第二个参数，那就跟第二个参数返回false一样
            
            //其他线程通过notif_one（）将wait唤醒后，开始回恢复
            //a. wait尝试重新获取互斥锁,如果获取不到就卡在这个，如果获取到就继续执行b
            //b. 获取到锁后
            //b.1 如果wait的有第二个参数， 如果表达式为fasle，又对互斥量解锁，继续阻塞等待notify
            //b.2 如果表达式为true，继续往下执行，
            //b.3  如果wait没有第二个参数，直接往下执行
            my_condition.wait(my1, [this]{
                if(!list.empty())
                    return true;
                return false;
            });
            //这里已经上锁
            command = list.front();
            list.pop_front();
             cout<<list.size()<<endl;
             cout<<"pop_front"<<endl;
            my1.unlock();//因为unique比较灵活，此处可以直接先解锁
        }
        
    }

private:
    list<int> list;
    mutex my_mutex;
    std::condition_variable my_condition;
};

int main(int argc, const char * argv[]) {
    
    //#### 条件变量std::condition_variable, wait() notify_one()
    //线程A：等待一个条件满足
    //线程B：专门往消息队列中r放消息
    //condition_variable 是一个类，
    A a;
    thread in_thread(&A::infunc, &a);
    thread out_thread(&A::outfunc,&a);
    in_thread.join();
    out_thread.join();
    return 0;
}
