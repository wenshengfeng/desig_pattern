class House{
    public:
    void Init(){
        this->BuildPart1();
        bool flg = this->BuildPart2();
        if(flg)
        {
            this->BuildPart3();
        }
    }
     virtual ~House(){}

    protected:
    virtual void BuildPart1() = 0;
    virtual bool BuildPart2() = 0;
    virtual void BuildPart3() = 0;
};  

class StoneHouse:public House{
    protected:
    void BuildPart1() override{}
    bool BuildPart2() override{
        return true;
    }
    void BuildPart3() override{}
};

int main(){
    House* house = new StoneHouse();
    house->Init();

    delete house;

    return 0;
}