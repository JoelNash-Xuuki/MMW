SRC		    = src/main.cpp src/DAW/Modularsynth.cpp src/DAW/Score.cpp
TEST		= tests/ScoreSuite.cpp tests/Suite.cpp tests/Date.cpp tests/Test.cpp src/Score.cpp tests/ScoreTest.cpp
CC			= g++

modularsynth: $(SRC) 
	$(CC)  $(SRC) -o bin/modularsynth

test: $(TEST)
	$(CC) $(TEST) -o bin/test
