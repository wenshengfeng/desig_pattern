#include<iostream>

class Memento
{
private:
	std::string state_;
	//...
public:
	Memento(std::string& state) :state_(state) {}
	std::string getState()const { return state_; }
	void setState(std::string& state) { state_ = state; }
};

class Originator
{
private:
	std::string state_;
	//...
public:
	Originator() {}
	Memento createMomento()
	{
		Memento m(state_);
		return m;
	}
	void setMomento(const Memento& m)
	{
		state_ = m.getState();
	}
};


int main()
{
	Originator orginator;
	//捕获对象状态，存储到备忘录
	Memento m = orginator.createMomento();
	//... 改变orginator状态

	//从备忘录中恢复
	orginator.setMomento(m);	

	return 0;
}
