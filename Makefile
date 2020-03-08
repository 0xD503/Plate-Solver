##  Define compile mode (Debug/Release)
MODE = DEBUG

##  Define CXX compiler
CXX = g++

##  Define CXX flags
CXXFLAGS = -Wall -g -v

##  Define include dirs
INCLUDES = -I ./include -I /usr/include/opencv4

##  Define library paths, used for project
LFLAGS = -L /usr/lib

##  Define libraries used in project
#LIBS = -l libopencv_core -l libopencv_imgcodecs -l libopencv_highgui -l libopencv_imgproc
LIBS = -l opencv_core -l opencv_imgcodecs -l opencv_highgui -l opencv_imgproc

##  Define the source files
SRCS = ./src/main.cpp ./src/coor.cpp ./src/Star.cpp ./src/Star_Detection.cpp ./src/Unit_Tests.cpp

##  Define the object files dirs and names
OBJS = ./obj/Debug/src/main.o ./obj/Debug/src/coor.o ./obj/Debug/src/Star.o ./obj/Debug/src/Star_Detection.o ./obj/Debug/src/Unit_Tests.o

##  Define target
MAIN = ./bin/Debug/Plate-Solver


##  Generic part
##  Target
all: $(MAIN)
	@echo	All is done

##  Executable
$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

##  Objects generation
$(OBJS):
#	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRCS) -o $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./src/main.cpp -o ./obj/Debug/src/main.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./src/coor.cpp -o ./obj/Debug/src/coor.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./src/Star.cpp -o ./obj/Debug/src/Star.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./src/Star_Detection.cpp -o ./obj/Debug/src/Star_Detection.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c ./src/Unit_Tests.cpp -o ./obj/Debug/src/Unit_Tests.o

##  Another options
clean:
	$(RM) ./obj/Debug/src/*.o ./bin/Debug/*
