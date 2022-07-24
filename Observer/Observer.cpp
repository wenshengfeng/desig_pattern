#include <string>
#include <list>

class Observer
{
public:
    virtual ~Observer(){};
    virtual void update(unsigned int value) = 0;
};

class ObserverList
{
private:
    std::list<Observer*> m_observerList;
public:
    void add(Observer *observer) //添加观察者
    {
        m_observerList.
    }
    void remove(){} //删除观察者
    void notifyAllObservers(unsigned int value) //变化通知
    {
        for (auto observr:  m_observerList)
        {
            observr->update(value);
        }
    }

class FileSpilter
{
private:
    std::string m_filePath;
    unsigned int m_fileNumber;
    Observer* m_observerList;
public:
    FileSpilter(std::string& path, unsigned int fileNumber, Observer* observer)
    :m_fileNumber(path),
    m_fileNumber(fileNumber),
    observer(observer)
    {}
    ~FileSpilter(){}
    void spilt(){
        //处理业务
        //.....

        //状态通知
        int values = m_fileNumber;
        m_observer->notifyAllObservers(values);
    }
};




