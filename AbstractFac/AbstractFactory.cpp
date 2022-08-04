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

// 抽象工厂实例 MySqlFactory
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

    delete factoty;
    delete connection;
    delete cmd;
    delete reader;
    return 0;
}