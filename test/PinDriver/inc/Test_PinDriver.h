#ifndef Test_PinDriver_H_
#define Test_PinDriver_H_

class Test_PinDriver
{
  public:
    explicit Test_PinDriver();
    virtual ~Test_PinDriver();

  private:
    Test_PinDriver(const Test_PinDriver&);
    Test_PinDriver& operator=(const Test_PinDriver&);
};

#endif
