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