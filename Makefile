# Makefile for Wordle game application

# Compiler and flags
CXX=g++
WT_BASE=/usr/local
CXXFLAGS=--std=c++14 -I$(WT_BASE)/include 
LDFLAGS=-L$(WT_BASE)/lib -Wl,-rpath,$(WT_BASE)/lib -lwthttp -lwt -lboost_thread -lboost_atomic -lboost_filesystem

# Header and object files
DEPS = WordleApplication.h
OBJS = main.o WordleApplication.o

# Build object files from source files
%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build the executable
wordle: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

# Clean up generated files
clean:
	rm -f wordle $(OBJS)
