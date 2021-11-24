SRC		    = src/main.cpp src/Modularsynth.cpp src/Score.cpp
TEST		= tests/ScoreSuite.cpp tests/Suite.cpp tests/Date.cpp tests/Test.cpp src/Score.cpp tests/ScoreTest.cpp
CC			= g++

modularsynth: $(SRC) 
	$(CC)  $(SRC) -o bin/modularsynth

test: $(TEST)
	$(CC) $(TEST) -o bin/test
