#include <iostream>
#include <map>
#include <string>

class Font{
    public:
    Font(std::string k);
    private:
    std::string key;

};

class FontFactory{
    public:
    Font* GetFont(const std::string &k){
        std::map<std::string, Font*>::iterator itr = fontPool.find(k);
        if(itr != fontPool.end())
        {
            return fontPool[k];
        }
        else {
            Font *font = new Font(k);
            fontPool[k] = font;
            return font;
        }
    }
    void clear()
    {

    }

    private:
    std::map<std::string, Font *> fontPool;
};