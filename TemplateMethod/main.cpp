class Libray{
    public:
    void run(){ //稳定
        if(init())
        {
            go_run();
        }
    }
    virtual ~Libray(){};

    protected:
    void go_run(){} // 稳定
    virtual bool init() = 0 ; // 变化

};

class Appliation : public Libray{
    public:
    bool init(){
        return false;
    }
    ~Appliation(){}
};

int main()
{
    Libray *lib = new Appliation();
    lib->run();
    delete lib;
    return 0;
}