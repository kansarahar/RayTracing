EXENAME = main
OBJS = vec.o ray.o surface.o sphere.o plane.o triangle.o rectangle.o camera.o BVH.o main.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $< $(CXXFLAGS)

BVH.o: BVH.cpp BVH.h
	$(CXX) $< $(CXXFLAGS)

camera.o: camera.cpp camera.h
	$(CXX) $< $(CXXFLAGS)

vec.o: vec.cpp vec.h
	$(CXX) $< $(CXXFLAGS)

ray.o: ray.cpp ray.h
	$(CXX) $< $(CXXFLAGS)

surface.o: surface.cpp surface.h
	$(CXX) $< $(CXXFLAGS)

sphere.o: sphere.cpp sphere.h
	$(CXX) $< $(CXXFLAGS)

plane.o: plane.cpp plane.h
	$(CXX) $< $(CXXFLAGS)

triangle.o: triangle.cpp triangle.h
	$(CXX) $< $(CXXFLAGS)

rectangle.o: rectangle.cpp rectangle.h
		$(CXX) $< $(CXXFLAGS)

clean:
	rm *.o main
