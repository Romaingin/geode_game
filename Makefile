all: main
clean:
	rm -f out *.o
.PHONY: all clean

CPPFLAGS =
CXXFLAGS = -std=c++11 -Wall -Wextra -g -Iheaders
LIBS = -lGL -lGLEW -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXcursor -lXinerama
SOURCES = sources/*.cpp

main:
	g++ $(CXXFLAGS) -o main $(SOURCES) $(LIBS)
