include ../../variables.inc

CLTESTS_SRC = hello_world.cpp openCLUtilities.cpp hello_world_clutils.cpp \
              vecadd.cpp
CLTESTS_OBJ = $(subst .cpp,.o, $(CLTESTS_SRC))
CLTESTS_EXE = hello_world hello_world_clutils vecadd

ifeq ($(UNAME), Darwin)
	LDFLAGS = -framework OpenCL
endif

all: $(CLTESTS_EXE)

openCLUtilities.cpp: openCLUtilities.hpp

hello_world: hello_world.o openCLUtilities.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

hello_world_clutils: hello_world_clutils.o openCLUtilities.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

vecadd: vecadd.o openCLUtilities.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(CLTESTS_OBJ)

clobber: clean
	$(RM) -rf $(CLTESTS_EXE)