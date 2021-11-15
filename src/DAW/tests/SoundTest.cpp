#include "SoundTest.hpp"
#include "Sound.h"
#include "Tool.hpp"
#include "Mix.hpp"
#include "Rec.hpp"
#include <iostream>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SoundTest );

void SoundTest::setUp(){}
void SoundTest::tearDown(){}

void SoundTest::testMainRec(){

    const char* argv[]={ 
      "sound","-r", "arg 3",nullptr 
    };

    int argc = sizeof(argv)/sizeof(char*);

    Tool* tool;
    Rec r;
    int m = 3;

    while(argc > 1) {
	if(argv[1][0] == '-'){
	    if(argv[1][1] == 'm'){
                m =8;
            }
            if(argv[1][1] == 'r'){
                tool = &r;
            }
	}
	argc--;
    }

    CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE("orc", r.getOrc());
    CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE("sco", r.getSco());
    CPPUNIT_ASSERT_EQUAL( 1, argc );
    CPPUNIT_ASSERT_EQUAL( 3, m );
    CPPUNIT_ASSERT_EQUAL( '-', argv[1][0] );
    CPPUNIT_ASSERT_EQUAL( 'r', argv[1][1] );
}

void SoundTest::testMainMix(){

    const char* argv[]={ 
      "sound","-m", "arg 3",nullptr 
    };

    int argc = sizeof(argv)/sizeof(char*);

    Tool* tool;
    Mix m;

    while(argc > 1) {
	if(argv[1][0] == '-'){
	    if(argv[1][1] == 'm'){
                tool = &m;
            }
	}
	argc--;
    }

    CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE("orc", m.getOrc());
    CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE("sco", m.getSco());
    CPPUNIT_ASSERT_EQUAL( 1, argc );
    CPPUNIT_ASSERT_EQUAL( '-', argv[1][0] );
    CPPUNIT_ASSERT_EQUAL( 'm', argv[1][1] );
}

void SoundTest::testMainMixAudio(){
    const char* argv[]={ 
      "sound","-m", "-a", "audio.wav",nullptr 
    };
    int argc = sizeof(argv)/sizeof(char*);

    Tool* t;
    Mix m;
    int tm = 7;

    while(argc > 1) {
	if(argv[1][0] == '-'){
	    if(argv[1][1] == 'm'){
		t = &m;
            }
	}
	argc--;
    }
    cout << "TEST: " << m.getOrc() << endl;

//    CPPUNIT_ASSERT_EQUAL("orc", m.getOrc());
    CPPUNIT_ASSERT_EQUAL(7, tm);
    CPPUNIT_ASSERT_EQUAL( 1, argc );
    CPPUNIT_ASSERT_EQUAL( '-', argv[2][0] );
    CPPUNIT_ASSERT_EQUAL( 'a', argv[2][1] );
}

void SoundTest::testConstructor(){
  // Set up
  const std::string currencyFF( "FF" );
  const double longNumber = 12345678.90123;

  // Process
  Sound sound( longNumber, currencyFF );

  // Check
  CPPUNIT_ASSERT_EQUAL( longNumber, sound.getAmount() );
  CPPUNIT_ASSERT_EQUAL( currencyFF, sound.getCurrency() );
}
