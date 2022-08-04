#include <iostream>
#include <ostream>

class Singletion{
    public:
    static Singletion& getInstanse(){
        static Singletion instanse;
        return instanse;
    };
    private:
    Singletion(){};
    Singletion(const Singletion&) = delete;
    Singletion& operator=(const Singletion&) = delete;

};


int main(){
    Singletion& instanse = Singletion::getInstanse();
    Singletion& instanse1 = Singletion::getInstanse();

    std::cout << "instanse ptr is :" << &instanse << std::endl;
    std::cout << "instanse1 ptr is ：" << &instanse1 << std::endl;

    return 0;
}