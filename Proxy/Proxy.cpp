#include <iostream>

class ISubject{
    public:
    virtual void Run() = 0;
    virtual ~ISubject(){}
};

class RealSubject: public ISubject{
    public:
    void Run() override{
        std::cout << "System run" << std::endl;
    }
};

class RealProxy : public ISubject{
    public:
    RealProxy(std::string userName, std::string passWord)
    :m_passWord(passWord),
     m_userName(userName),
     m_real{new RealSubject()}
    {

    }
    void Run() override{
        std::cout << "System Proxy run" << std::endl;
        if(checkUserNameAndPassword()){
            m_real->Run();
        }else {
            std::cout << "System check error" << std::endl;
        }
    }
    ~RealProxy(){
        if(m_real != nullptr)
        {
            delete m_real;
        }
    }
    private:
    bool checkUserNameAndPassword()
    {
        return  true;
    }

    RealSubject* m_real;
    std::string m_userName;
    std::string m_passWord;
};

int main(){
    RealProxy proxy("user", "pwd");
    proxy.Run();
    return 0;
}