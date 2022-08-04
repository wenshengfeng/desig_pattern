#include <iostream>
#include <atomic>
#include <mutex>

class Singletion{
    public:
    static Singletion* getInstanse();
    private:
    static std::atomic<Singletion*> m_instanse;
    static std::mutex m_mutex;

    Singletion(){};
    Singletion(const Singletion&) = delete;
    Singletion& operator=(const Singletion&) = delete;

};
std::atomic<Singletion*> Singletion::m_instanse;
std::mutex  Singletion::m_mutex;

Singletion* Singletion::getInstanse(){
    Singletion* tmp = m_instanse.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock{m_mutex};
        tmp = m_instanse.load(std::memory_order_relaxed);
        if(tmp == nullptr)
        {
            tmp = new Singletion();
            std::atomic_thread_fence(std::memory_order_release); //释放内存
            m_instanse.store(tmp, std::memory_order_relaxed);
        }
        
    }

    return tmp;
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