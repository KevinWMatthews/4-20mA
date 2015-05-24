#ifndef Test_LedNumber_H_
#define Test_LedNumber_H_

class Test_LedNumber
{
  public:
    explicit Test_LedNumber();
    virtual ~Test_LedNumber();

  private:
    Test_LedNumber(const Test_LedNumber&);
    Test_LedNumber& operator=(const Test_LedNumber&);
};

#endif
