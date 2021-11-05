#ifndef SOUNDTEST_H
#define SOUNDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class SoundTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( SoundTest );
    CPPUNIT_TEST( testMainMix );
    CPPUNIT_TEST( testMainMixAudio );
    CPPUNIT_TEST( testMainRec );
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testMainMix();
    void testMainMixAudio();
    void testMainRec();
    void testConstructor();

};

#endif  // SOUNDTEST_H
