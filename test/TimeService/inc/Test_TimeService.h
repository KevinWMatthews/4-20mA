#ifndef Test_TimeService_H_
#define Test_TimeService_H_

class Test_TimeService
{
  public:
    explicit Test_TimeService();
    virtual ~Test_TimeService();

  private:
    Test_TimeService(const Test_TimeService&);
    Test_TimeService& operator=(const Test_TimeService&);
};

#endif
