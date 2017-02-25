
struct ICallBack
{
  int (*func1)(void);
  int (*func2)(void);
};

struct ICallBack
{
  ICallBack(void){};
  virtual ~ICallBack(){};
  virtual int func1(void){ return 0; };
  virtual int func2(void){ return 0; };
};

struct ICallBack
{
  ICallBack(void){};
  virtual ~ICallBack(void){};
  virtual int func1(void) = 0;
  virtual int func2(void) = 0;
};

class ICallBack
{
  public:
    ICallBack(void){};
    virtual ~ICallBack(void){};
    virtual int func1(void){ return 0; };
    virtual int func2(void){ return 0; };
};

class ICallBack
{
  public:
    ICallBack(void){};
    virtual ~ICallBack(void){};
    virtual int func1(void) = 0;
    virtual int func2(void) = 0;
};
