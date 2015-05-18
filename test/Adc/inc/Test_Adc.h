#ifndef Test_Adc_H_
#define Test_Adc_H_

class Test_Adc
{
  public:
    explicit Test_Adc();
    virtual ~Test_Adc();

  private:
    Test_Adc(const Test_Adc&);
    Test_Adc& operator=(const Test_Adc&);
};

#endif
