#ifndef Test_AtoD_H_
#define Test_AtoD_H_

class Test_AtoD
{
  public:
    explicit Test_AtoD();
    virtual ~Test_AtoD();

  private:
    Test_AtoD(const Test_AtoD&);
    Test_AtoD& operator=(const Test_AtoD&);
};

#endif
