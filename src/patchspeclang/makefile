SRC		    = main.cpp modularsynth.cpp score.cpp
TEST		= tests/StringSuite.cpp tests/Suite.cpp tests/Date.cpp tests/Test.cpp score.cpp
CC			= g++

modularsynth: $(SRC) 
	$(CC)  $(SRC) -o modularsynth

test: $(TEST)
	$(CC) $(TEST) -o test
