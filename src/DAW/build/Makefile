CSOUND		= -lcsound64 -lcsnd6
UNIT            = -lcppunit
INCLUDES        = -I/usr/include/csound/
SRC		= ../src/Daw.cpp ../src/Tool.cpp ../src/Rec.cpp ../src/Mix.cpp
TEST		= ../tests/Sound.cpp ../tests/SoundTest.cpp ../tests/RunTests.cpp ../tests/Interface.cpp ../tests/Tool.cpp ../tests/Rec.cpp ../tests/Mix.cpp
CC		= g++

sound: $(TEST) 
	$(CC) $(INCLUDES) $(SRC) $(CSOUND) -o ../bin/sound

#testsound: $(TEST) 
#	$(CC) $(TEST) $(UNIT) -o ../bin/testsound


