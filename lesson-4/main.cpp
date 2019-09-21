#include <iostream>
#include <thread>
using namespace std;
void myprint(const int &i, char * p){
    cout<<i<<endl; //**不是引用，是值传递**
    cout<<p<<endl;// 指针在detach绝对有问题，不建议传指针
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
