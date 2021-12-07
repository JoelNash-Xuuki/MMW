#MAGICK		= `Magick++-config --cppflags --cxxflags --ldflags --libs`
#DRAW		= Draw/Draw.cpp
#FRAMES		= Handle_Frames/frames.cpp
VIDEO		= src/PrintMediaInfo.cpp
LIBAV		= -lavcodec -lavformat -lavfilter -lavdevice -lswresample -lswscale -lavutil
#IMAGE		= prog.cpp
CC			= g++


#test_draw: $(DRAW) 
#	g++ -o test_draw $(DRAW) $(MAGICK)

#test_frame: $(FRAMES) 
#	g++ -o test_frame $(FRAMES) $(MAGICK)

#image: $(IMAGE) 
#	g++ -o image $(IMAGE) $(MAGICK)

PrintMediaInfo: $(VIDEO)
	$(CC) -o PrintMediaInfo $(LIBAV) $(VIDEO)

