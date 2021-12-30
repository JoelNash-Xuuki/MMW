SRC		    = src/main.cpp src/DAW/Modularsynth.cpp src/DAW/Score.cpp src/DAW/Rack.cpp src/DAW/Translator.cpp
# TEST		= tests/ScoreSuite.cpp tests/Suite.cpp tests/ScoreTest.cpp tests/Test.cpp src/DAW/Score.cpp
#tests/Date.cpp  
CC			= g++

modularsynth: $(SRC) 
	$(CC)  $(SRC) -o bin/modularsynth

test: $(TEST)
	$(CC) $(TEST) -o bin/test
