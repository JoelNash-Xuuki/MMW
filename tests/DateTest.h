#ifndef DATETEST_H
#define DATETEST_H
#include "Date.h"
#include "Test.h"

class DateTest : public TestSuite::Test {
  Date mybday;
  Date today;
  Date myevebday;

  public:
    DateTest(): mybday(1951, 10, 1), myevebday("19510930") {}
    void run() {
      testOps();
      testFunctions();
      testDuration();
    }
    void testOps() {
      test_(mybday < today);
    }
  
    void testFunctions() {
      test_(mybday.getYear() == 1951);
    }
  
    void testDuration() {
      Date d2(2003, 7, 4);
      Date::Duration dur = duration(mybday, d2);
      test_(dur.years == 51);
    }
  
    void testException(){
      try{
        Date d(0,0,0);
     	  fail_("Invalid date undetected in Data in ctor");
  	}catch(Date::DateError&){
  	  succeed_();
      }
      try {
       Date d("");
  	 fail_("Invalid date undetected in Date string ctor");
  	} catch(Date::DateError&){
  	  succeed_();
      }
    }
};
#endif // DATETEST_H ///:~
