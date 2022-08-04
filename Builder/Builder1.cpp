#include <iostream>
#include <type_traits>

class House{
    public:
    void show(){
        std::cout << "House" << std::endl;
    }
};

class HouseBuilder{  // 变化的部分对象构建
    public:
    House* GetBuildResult(){
        return pHouse;
    }
    virtual ~HouseBuilder(){}
    protected:
    House* pHouse;
    public:
    virtual void BuildPart1() = 0;
    virtual bool BuildPart2() = 0;
    virtual void BuildPart3() = 0;
};

class StoneHouse : public House{
    public:
    void show(){
        std::cout << " stoneHouse" << std::endl;
    }
};

class StoneHouseBuilder: public HouseBuilder {
    public:
    void BuildPart1() override{
        std::cout << "BuildPart1 " << std::endl;
    }
    bool BuildPart2() override{
        std::cout << "BuildPart2 " << std::endl;
        return true;
    }
    void BuildPart3() override{
        std::cout << "BuildPart3 " << std::endl;
    }
};

class  HouseDirector{
public:
    HouseDirector(HouseBuilder* pHouseBuilder){
        this->pHouseBuilder = pHouseBuilder;
    }
    House* Construct(){
        pHouseBuilder->BuildPart1();
        bool flg = pHouseBuilder->BuildPart2();
        if(flg)
        {
            pHouseBuilder->BuildPart3();
        }
        return pHouseBuilder->GetBuildResult();
    }
private:
    HouseBuilder* pHouseBuilder;
};

int main(){
    HouseBuilder* pHouseBuilder = new StoneHouseBuilder();
    HouseDirector* pDirector = new HouseDirector(pHouseBuilder);
    pDirector->Construct()->show();

    delete pHouseBuilder;
    delete pDirector;

    return 0;
}