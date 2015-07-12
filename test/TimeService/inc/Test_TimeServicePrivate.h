#ifndef Test_TimeServicePrivate_H_
#define Test_TimeServicePrivate_H_

class Test_TimeServicePrivate
{
  public:
    explicit Test_TimeServicePrivate();
    virtual ~Test_TimeServicePrivate();

  private:
    Test_TimeServicePrivate(const Test_TimeServicePrivate&);
    Test_TimeServicePrivate& operator=(const Test_TimeServicePrivate&);
};

#endif
