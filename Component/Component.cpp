#include<list>
#include<string>
#include<memory>
#include<algorithm>
#include<iostream>
class Component
{
protected:
    std::string name;
public:
    Component(std::string str) :name(str) {}
    virtual void display() = 0;
    virtual void add(Component*) = 0;
    virtual void remove(Component*) = 0;
    virtual ~Component() {}
};

class Composite:public Component
{
private:
    std::list<std::shared_ptr<Component>>elements;
public:
    Composite(std::string str) :Component(str) {}
    void add(Component* element)
    {
        auto it = std::find_if(elements.begin(), elements.end(), 
        [element](std::shared_ptr<Component> ptr) {return element == ptr.get(); });
        if (it == elements.end())
        {
            elements.push_back(std::shared_ptr<Component>(element));
        }
    }
    void remove(Component* element)
    {
        auto it = std::find_if(elements.begin(), elements.end(),
            [element](std::shared_ptr<Component>ptr) {return element == ptr.get(); });
        if (it == elements.end())
        {
            return;
        }
        elements.erase(it);
    }
    void display()
    {
        for (auto it = elements.cbegin(); it != elements.cend(); ++it)
        {
            (*it)->display();   //多态调用
        }
    }
};

class Leaf : public Component 
{
public:
    Leaf(std::string str) :Component(str) {}
    void display()
    {
        std::cout << name << std::endl;
    }
    void add(Component* element)
    {
        std::cout << "Leaf cannot add" << std::endl;
    }
    void remove(Component* element)
    {
        std::cout << "Leaf cannot remove" << std::endl;
    }
};


int main()
{
    Component* p = new Composite("北京");
    p->add(new Leaf("紫荆城"));
    p->add(new Leaf("朝阳区"));
    Component* p1 = new Composite("郑州");
    p1->add(new Leaf("郑大"));
    p1->add(new Leaf("。。。"));
    p->add(p1);
    p->display();
    return 0;
}
