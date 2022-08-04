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
    CryptoStream * cryoto = new CryptoStream(fileStream); //文件流加密操作
    NetWorkStream * network = new NetWorkStream();
    CryptoStream * cryoto1 = new CryptoStream(network);
    return 0;
}