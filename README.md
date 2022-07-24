# desig_pattern (设计模式)
---
- **`面向对象设计原则`**
  1.单一职责原则（SRP）
  2.开闭原则（OCP）
  3.里氏代换原则（LSP）
  4.依赖倒置原则（DIP）
  5.接口隔离原则（ISP）
  6.合成复用原则（CRP）
  7.迪米特法则（LoD）
- **`泛型编程`** 与 **`代码重构`**
  **推荐书籍** `重构与模式` `重构-改善既有代码的设计`
  **重构关键技法**
  - 静态->动态
  - 早绑定->晚绑定
  - 继承->组合
  - 编译时依赖->运行时依赖
  - 紧耦合->松耦合
---
### 典型模式
- **模板方法(Template Method)**
  模板方法模式是一种非常基础性的设计模式，在面向对象系统中有着大量的应用。它用最简单的机制（虚函数的多态）为程序应用框架提供了灵活的扩展点，是代码复用方面的基本实现机构。
  ```cpp
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
  ```
 - **策略模式(Strategy Pattern)**
    在软件构建过程中，某些对象使用的算法可能多种多样，经常改变，如果将这些算法都编码到对象中，将会使对象变得异常复杂；而且有时候支持不使用的算法也是一个性能负担。本模式是解决将算法与对象本身进行解耦，从而避免上述问题。(消除if判断问题)
    ```cpp
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

        ~Context(){
            delete strategy;
        }
    };

    int main()
    {
        Context* ctx = new Context(new OperationSub());
        double rlt = ctx->executeStrategy(6.1, 3.0);
        std::cout<<"rlt is :" << rlt << std::endl;

        return 0;
    }
    ```
- **观察者模式(Observer)**
  观察者模式使用三个类 Subject、Observer 和 Client。Subject 对象带有绑定观察者到 Client 对象和从 Client 对象解绑观察者的方法。我们创建 Subject 类、Observer 抽象类和扩展了抽象类 Observer 的实体类。
  ObserverPatternDemo，我们的演示类使用 Subject 和实体类对象来演示观察者模式。
  ```cpp
    #include <string>
    #include <list>
    #include <iostream>

    class Observer
    {
    public:
        virtual ~Observer(){std::cout << "delete Observer" << std::endl;}
        virtual void update(unsigned int value) = 0;
    };

    class ObserverList
    {
    private:
        std::list<Observer*> m_observerList;
    public:
        void add(Observer *observer) //添加观察者
        {
            m_observerList.push_back(observer);
        }
        void remove() //删除观察者
        {
            m_observerList.pop_back();
        }
        void notifyAllObservers(unsigned int value) //变化通知
        {
            for (auto observr:  m_observerList)
            {
                observr->update(value);
            }
        }
    };
    class FileSpilter
    {
    private:
        std::string m_filePath;
        unsigned int m_fileNumber;
        ObserverList* m_observerList;
    public:
        FileSpilter(std::string& path, unsigned int fileNumber, ObserverList* observer)
        :m_filePath(path),
        m_fileNumber(fileNumber),
        m_observerList(observer)
        {}
        ~FileSpilter(){}
        void spilt(){
            //处理业务
            //.....

            //状态通知
            int values = m_fileNumber;
            m_observerList->notifyAllObservers(values);
        }
    };

    class MyObserver:public Observer{
        public:
        void update(unsigned int value) override {
            std::cout << "update MyObserver values is :" << value << std::endl;
        }
        ~MyObserver(){ std::cout<< "delete MyObserver"<<std::endl;}
    };

    class MyObserver1:public Observer{
        public:
        void update(unsigned int value) override {
            std::cout << "update MyObserver1 values is :" << value << std::endl;
        }
        ~MyObserver1(){ std::cout<< "delete MyObserver1"<<std::endl;}
    };

    int main()
    {
        ObserverList* oblist = new ObserverList();
        oblist->add(new MyObserver()); //添加观察者
        oblist->add(new MyObserver1());

        std::string path = "/home/a.txt";
        FileSpilter* spilter = new FileSpilter(path, 23, oblist);
        spilter->spilt();

        //删除观察者
        oblist->remove();

        return 0;
    }
  ```
### "单一职责模式"
在软件组件的设计中，如果责任划分不清晰，使用继承得到的结果往往是随着需求的变化，子类急剧膨胀，同时充斥着重复代码，这个时候的关键是划分责任。
- **装饰器模式（Decorator）**
  装饰器模式（Decorator Pattern）允许向一个现有的对象添加新的功能，同时又不改变其结构。这种类型的设计模式属于结构型模式，它是作为现有的类的一个包装。
  这种模式创建了一个装饰类，用来包装原有的类，并在保持类方法签名完整性的前提下，提供了额外的功能。(**组合与继承一起使用**)
  ```cpp
    class Stream{
        public:
        virtual char Read(unsigned int number) = 0;
        virtual void Seek(unsigned int pos) = 0;
        virtual void Write(char data) = 0;
        virtual ~Stream(){}
    };

    class FileStream:public Stream{
    public:
        char Read(unsigned int number) override{
            // 文件具体操作
            return 'a';
        }
        void Seek(unsigned int pos) override{

        }
        void Write(char data) override{

        }
    };

    class NetWorkStream:public Stream{
    public:
        char Read(unsigned int number) override{
            //网络流操作
            return 'a';
        }
        void Seek(unsigned int pos) override{

        }
        void Write(char data) override{

        }
    };


    //加密流操作
    class CryptoStream:public Stream{
        Stream * stream; //多态对象 可以是文件流 网络流
    public:
        CryptoStream(Stream *stm):stream(stm){}
        char Read(unsigned int number) override{
            //额外加密操作
            
        return stream->Read(number);
        }
        void Seek(unsigned int pos) override{
            //额外加密操作

            stream->Seek(pos);
        }
        void Write(char data) override{
            //额外加密操作

            stream->Write(data);
        }
    };


    int main()
    {
        FileStream * fileStream = new FileStream();
        CryptoStream * cryoto = new CryptoStream(fileStream);
        return 0;
    }
  ```
  **完整版**
  ```cpp
    class Stream{
        public:
        virtual char Read(unsigned int number) = 0;
        virtual void Seek(unsigned int pos) = 0;
        virtual void Write(char data) = 0;
        virtual ~Stream(){}
    };

    class FileStream:public Stream{
    public:
        char Read(unsigned int number) override{
            // 文件具体操作
            return 'a';
        }
        void Seek(unsigned int pos) override{

        }
        void Write(char data) override{

        }
    };

    class NetWorkStream:public Stream{
    public:
        char Read(unsigned int number) override{
            //网络流操作
            return 'a';
        }
        void Seek(unsigned int pos) override{

        }
        void Write(char data) override{

        }
    };

    class DecoatorStream:public Stream{
    protected:
        Stream * stream;
    public:
        DecoatorStream(Stream *stm):stream(stm){}
        char Read(unsigned int number) override{
            return stream->Read(number);
        }
        void Seek(unsigned int pos) override{
            stream->Seek(pos);
        }
        void Write(char data) override{
            stream->Write(data);
        }
    };

    //加密流操作
    class CryptoStream:public Stream{
        DecoatorStream * stream; //多态对象 可以是文件流 网络流
    public:
        CryptoStream(DecoatorStream *stm):stream(stm){}
        char Read(unsigned int number) override{
            //额外加密操作
            
        return stream->Read(number);
        }
        void Seek(unsigned int pos) override{
            //额外加密操作

            stream->Seek(pos);
        }
        void Write(char data) override{
            //额外加密操作

            stream->Write(data);
        }
    };


    int main()
    {
        FileStream * fileStream = new FileStream();
        DecoatorStream *decorator = new DecoatorStream(fileStream);
        CryptoStream * cryoto = new CryptoStream(decorator);
        return 0;
    }
  ```
- **桥模式(Bridge)**
  桥接（Bridge）是用于把抽象化与实现化解耦，使得二者可以独立变化。这种类型的设计模式属于结构型模式，它通过提供抽象化和实现化之间的桥接结构，来实现二者的解耦。这种模式涉及到一个作为桥接的接口，使得实体类的功能独立于接口实现类。这两种类型的类可被结构化改变而互不影响。我们通过下面的实例来演示桥接模式（Bridge Pattern）的用法。其中，可以使用相同的抽象类方法但是不同的桥接实现类，来画出不同颜色的圆。
  ```cpp
    #include <iostream>
    #include <stdexcept>

    class DrawAPI{
    public:
        virtual void drawCircle(int radius, int x, int y) = 0 ;
        virtual ~DrawAPI(){}
    };

    class RedCircle : public DrawAPI{
    public:
        void drawCircle(int radius, int x, int y) override {
            std::cout << "Drawing Circle [ color : red, radius : " << radius << " x:" << x << " y: " << y << std::endl;
        }
        ~RedCircle(){std::cout << "destructor RedCircle" << std::endl;}
        
    };


    class GreenCircle : public DrawAPI{
    public:
        void drawCircle(int radius, int x, int y) override {
            std::cout << "Drawing Circle [ color : green, radius : " << radius << " x:" << x << " y: " << y << std::endl;
        }
        ~GreenCircle(){std::cout << "destructor GreenCircle" << std::endl;}
    };

    class Shape {
    protected:
        DrawAPI* drawApi;
    public:
        virtual void draw() = 0;
        virtual ~Shape(){delete drawApi; std::cout << "destructor Shape:drawApi" << std::endl;}
    };

    class Cirecle :public Shape{
        public:
        Cirecle(int x, int y, int radius, DrawAPI* api)
        {
            drawApi= api;
            this->radius = radius;
            this->x = x;
            this->y = y;
        }
        ~Cirecle(){}
        void draw() override {
            drawApi->drawCircle(radius, x, y);
        }
        private:
        int x, y ,radius;
    };

    auto main () -> int {
        Shape*  redCircle = new Cirecle(100,100, 10, new RedCircle());
        redCircle->draw();
        delete redCircle;

        Shape* greenCircle = new Cirecle(101,101, 11, new GreenCircle());
        greenCircle->draw();
        delete greenCircle;

        return  0;
    }

  ```
- **工厂方法模式(Factory)**
  工厂模式（Factory Pattern）是 `C++` 中最常用的设计模式之一。这种类型的设计模式属于创建型模式，它提供了一种创建对象的最佳方式。在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。(*作为一种创建类模式，在任何需要生成复杂对象的地方，都可以使用工厂方法模式。有一点需要注意的地方就是复杂对象适合使用工厂模式，而简单对象，特别是只需要通过 new 就可以完成创建的对象，无需使用工厂模式。如果使用工厂模式，就需要引入一个工厂类，会增加系统的复杂度。*)**对象构造方法 必须一致，不然不能使用工厂方法**
  ```cpp
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
  ```
- **抽象工厂方法(Abstract Factory)**
  抽象工厂模式（Abstract Factory Pattern）是围绕一个超级工厂创建其他工厂。该超级工厂又称为其他工厂的工厂。这种类型的设计模式属于创建型模式，它提供了一种创建对象的最佳方式。
  在抽象工厂模式中，接口是负责创建一个相关对象的工厂，不需要显式指定它们的类。每个生成的工厂都能按照工厂模式提供对象。
  ```cpp
    #include <iostream>
    #include <string_view>

    //DB连接
    class IDBConnection{
        public:
        virtual bool connect_db(std::string_view db_msg) = 0;
        virtual ~IDBConnection(){}
    };

    // DB SQL 执行
    class IDBCommand{
        public:
        virtual bool command_exector(std::string_view cmd) = 0;
        virtual ~IDBCommand(){}
    };

    //DB结果获取
    class IDBReader{
        public:
        virtual bool db_read() = 0;
        virtual ~IDBReader(){}
    };

    // MySQL的db conection 实例
    class MySQLDBConnection: public IDBConnection{
        public:
        bool connect_db(std::string_view db_msg) override{
            //连接MySQL 数据库
            // .....
            return true;
        }
    };
    // Oarcle 的 db 实例
    class OarcleDBConnection: public IDBConnection{
        public:
        bool connect_db(std::string_view db_msg) override{
            //连接Oarcle 数据库
            // .....
            return true;
        }
    };

    // MySQL 的 Command 实例
    class MySqlDBCommand:public IDBCommand{
        public:
        bool command_exector(std::string_view cmd) override{
            // 执行 Mysql SQL 
            // ...
            return true;
        }
    };
    // Oarcle  的 Command 实例
    class OarcleDBCommand:public IDBCommand{
        public:
        bool command_exector(std::string_view cmd) override{
            // 执行 Oarcle SQL 
            // ...
            return true;
        }
    };

    // Mysql 的 db Reader 实例
    class MySqlDBReader: public IDBReader{
        public: 
        bool db_read() override{
            // 执行 mysql 读取操作
            // ...
            return true;
        }
    };
    // Oarcle 的 db Reader 实例
    class OarcleDBReader: public IDBReader{
        public: 
        bool db_read() override{
            // 执行 Oarcle 读取操作
            // ...
            return true;
        }
    };

    // IDBConnection IDBCommand IDBReader 有关联性 必须为同种数据库的操作类型
    // 所以 将提供生成这三个关联抽象的工厂
    class IDBAbstractFactory{
        public:
        virtual IDBConnection* CreateDBConnection() = 0;
        virtual IDBCommand* CreateDBCommand() = 0;
        virtual IDBReader* CreateDBReader() = 0;
        virtual ~IDBAbstractFactory(){}
    };

    // 抽象工厂实例 MySqlFactory
    class MySqlDBFactory: public IDBAbstractFactory{
        public:
        IDBConnection * CreateDBConnection() override{
            return new MySQLDBConnection();
        }
        IDBCommand * CreateDBCommand() override{
            return new MySqlDBCommand();
        }
        IDBReader * CreateDBReader() override{
            return new MySqlDBReader();
        }
    };

    // 抽象工厂实例 OarcleFactory
    class OarcleDBFactory: public IDBAbstractFactory{
        public:
        IDBConnection * CreateDBConnection() override{
            return new OarcleDBConnection();
        }
        IDBCommand * CreateDBCommand() override{
            return new OarcleDBCommand();
        }
        IDBReader * CreateDBReader() override{
            return new OarcleDBReader();
        }
    };


    int main()
    {
        IDBAbstractFactory* factoty = new MySqlDBFactory(); //具体是Mysql 还是 Oracle 从外界传入
        
        IDBConnection* connection =factoty->CreateDBConnection();
        connection->connect_db("db ip prot ");
        IDBCommand* cmd = factoty->CreateDBCommand();
        cmd->command_exector("select * from a");
        IDBReader* reader = factoty->CreateDBReader();
        reader->db_read();

        return 0;
    }
  ```
- **原型模式(Prototype)**
  原型模式（Prototype Pattern）是用于创建重复的对象，同时又能保证性能。这种类型的设计模式属于创建型模式，它提供了一种创建对象的最佳方式。
  这种模式是实现了一个原型接口，该接口用于创建当前对象的克隆。当直接创建对象的代价比较大时，则采用这种模式。例如，一个对象需要在一个高代价的数据库操作之后被创建。我们可以缓存该对象，在下一个请求时返回它的克隆，在需要的时候更新数据库，以此来减少数据库调用。
  ```cpp
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
  ```
  
  