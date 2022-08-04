 #include <iostream>

 class Strategy{
    public:
    virtual double doOperation(double num1, double num2) = 0;
    virtual ~Strategy(){}
 };

class OperationAdd:public Strategy{
    public:
    double doOperation(double num1, double num2) override{
        return num1 + num2;
    }
    ~OperationAdd(){}
};

class OperationSub: public Strategy{
    public:
    double doOperation(double num1, double num2) override{
        return num1 - num2;
    }
    ~OperationSub(){}
};

class Context{
    private:
    Strategy* strategy;
    public:
    Context( Strategy* strategy){
        this->strategy = strategy;
    }

    double executeStrategy(double num1 , double num2){
        return strategy->doOperation(num1,num2);
    }

    bool setStrategy(Strategy *strategy){
        if(this->strategy != nullptr) delete  this->strategy;
        this->strategy = strategy;
        return true;
    }
    ~Context(){
        delete strategy;
    }
};

int main()
{
    Context* ctx = new Context(new OperationSub());
    double rlt = ctx->executeStrategy(6.1, 3.0);
    std::cout<<"rlt is :" << rlt << std::endl;
    ctx->setStrategy(new OperationAdd());
    rlt = ctx->executeStrategy(9.9, 1.1);
    std::cout<<"rlt is :" << rlt << std::endl;

    return 0;
}