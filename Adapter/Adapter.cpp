#include <iostream>

class ITarget{
    public:
    virtual void process() = 0;
    virtual ~ITarget(){}
};

// 遗留接口
class IAdaptee{
    public:
    virtual int bar() = 0;
    virtual void foo(int) = 0;
    virtual ~IAdaptee(){}
};

// 遗留类型
class OldClass: public IAdaptee{
    public:
    int bar() override{
        return 1024;
    }
    void foo(int data) override{
        std::cout << data << std::endl;
    }
};

// 对象适配器 
class Adapter : public ITarget{
    public:
    Adapter(IAdaptee * pAdaptee)
    :pAdaptee_(pAdaptee)
    {

    }
    void process() override{
        int data = pAdaptee_->bar();
        pAdaptee_->foo(data);
    }
    protected:
     IAdaptee* pAdaptee_ ;  
};

int main(){
    IAdaptee * adaptee = new OldClass();
    ITarget* pTarget = new Adapter(adaptee);
    pTarget->process();
    return 0;
}