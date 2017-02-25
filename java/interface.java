
/****** Abstract Class ******/
public abstract class ICallBack
{
  public abstract void func1();
  public abstract void func2();
};

public MyClass1 extends ICallBack
{
  public abstract void func3();
};

public MyClass3 extends MyClass1
{
  public void func1(){};
  public void func2(){};
  public void func3(){};
};

/****** Interface ******/
public interface ICallBack
{
  public abstract void test1();
  public abstract void test2();
};

public interface MyCallBack1 extends ICallBack
{
  public abstract void test3();
};

public interface MyCallBack2 extends ICallBack
{
  public abstract void test4();
};

public class MyClass2 extends MyClass1  implements MyCallBack1, MyCallBack2
{
  public void func1(){};
  public void func2(){};
  public void func3(){};
  public void test1(){};
  public void test2(){};
  public void test3(){};
  public void test4(){};
};
