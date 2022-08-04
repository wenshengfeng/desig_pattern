class ISpilter{
    public:
    virtual ISpilter* clone() = 0;
    virtual void spilt() = 0;
    virtual ~ISpilter(){}
};

// 
class TextSpilter:public ISpilter{
    public:
    ISpilter * clone() override{
        return new TextSpilter(*this); // 深克隆 以拷贝构造函数进行
    }
    void spilt() override{

    }
    TextSpilter(const TextSpilter& spilt){ // 拷贝构造函数
        // 进行处理
    }
    TextSpilter(){}
    
};

int main(){
    ISpilter* protoType = new TextSpilter(); //外界传入 protoType 

    ISpilter* spilt1 = protoType->clone();
    spilt1->spilt();

    delete protoType;
    delete spilt1;
    
    return 0;
}