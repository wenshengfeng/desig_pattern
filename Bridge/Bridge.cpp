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
