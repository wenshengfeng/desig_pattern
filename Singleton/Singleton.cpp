#include <iostream>
#include <atomic>
#include <mutex>

class Singletion{
    public:
    static Singletion* getInstanse();
    private:
    static Singletion* m_instanse;
    static std::mutex m_mutex;

    Singletion(){};
    Singletion(const Singletion&) = delete;
    Singletion& operator=(const Singletion&) = delete;

};
Singletion* Singletion::m_instanse = nullptr;
std::mutex  Singletion::m_mutex;

Singletion* Singletion::getInstanse(){
    std::lock_guard<std::mutex> lk{m_mutex};
    if (m_instanse == nullptr) {
        if (m_instanse == nullptr) {
            m_instanse = new Singletion();
        }
        
    }

    return m_instanse;
}

int main(){
    Singletion* instanse = Singletion::getInstanse();
    Singletion* instanse1 = Singletion::getInstanse();
    std::cout << "instanse" << instanse << std::endl;
    std::cout << "instanse1" << instanse1 << std::endl;

    std::cout << " instanse == instanse1 \n" << (bool)(instanse1 == instanse) << std::endl;
    delete instanse1;

    return 0;
}