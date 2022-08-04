#include <type_traits>
#include <iostream>

class ISpilt{
    public:
    virtual void spilt() = 0;
    virtual ~ISpilt(){}
};

class TxtSpilter : public ISpilt{
    public:
    void spilt() override{
        /// 具体实现
        std::cout << "TxtSpilter spilt txt" << std::endl;
    }
};

class PhotoSpilter: public ISpilt{
    public:
    void spilt() override{
        //具体实现   
        std::cout << "PhotoSpilter spilt " << std::endl;   
    }
};

class FatorySpilter{
    public:
    virtual ISpilt* CreateFatorySpilter() = 0;
    virtual ~FatorySpilter(){};
};

class TextFatorySpilter: public FatorySpilter{
    public:
    ISpilt * CreateFatorySpilter() override{
        return new TxtSpilter();
    }
};

class PhotoFatorySpilter: public FatorySpilter{
    public:
    ISpilt * CreateFatorySpilter() override{
        return new PhotoSpilter();
    }
};

auto main () -> int {
    FatorySpilter* fatory = new TextFatorySpilter(); // 通过外界传入具体的实体
    ISpilt* spilt= fatory->CreateFatorySpilter();
    spilt->spilt();

    delete fatory;
    delete spilt;
    
    return 0;
}