#ifndef Test_Fake_TimeService_H_
#define Test_Fake_TimeService_H_

class Test_Fake_TimeService
{
  public:
    explicit Test_Fake_TimeService();
    virtual ~Test_Fake_TimeService();

  private:
    Test_Fake_TimeService(const Test_Fake_TimeService&);
    Test_Fake_TimeService& operator=(const Test_Fake_TimeService&);
};

#endif
