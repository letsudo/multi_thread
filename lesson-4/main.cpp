#include <iostream>
#include <thread>
using namespace std;
void myprint(const int &i, const string &p){//改晨string 隐式转换
    cout<<i<<endl; //**不是引用，是值传递**
    cout<<p.c_str()<<endl;// 指针在detach绝对有问题，不建议传指针
}
int main(int argc, const char * argv[]) {
    // 传递临时变量作为线程参数
    int var =1;
    int &vary = var;
    char buf[] = "this is a text";
    thread t(myprint, var, buf);
//    t.join();
    t.detach();
    cout<<"Hi in main"<<endl;
    return 0;
}
