#ifndef Test_MainLoop_H_
#define Test_MainLoop_H_

class Test_MainLoop
{
  public:
    explicit Test_MainLoop();
    virtual ~Test_MainLoop();

  private:
    Test_MainLoop(const Test_MainLoop&);
    Test_MainLoop& operator=(const Test_MainLoop&);
};

#endif
