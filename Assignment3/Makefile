# The user needs to assign these for their project
CC = g++
CXXFLAGS = -c -Wall
SOURCES = Cache.cc Set.cc Block.cc Simulation.cc
OBJECTS = $(SOURCES: .cc = .o)
EXECUTABLE = Simulation

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

#.cc.o: 
#	$(CC) $< -o $@

clean:
	rm -f *~
	rm -f *.o
	rm -f $(EXECUTABLE)
	$(CC) $(SOURCES) -MM > $(EXECUTABLE).d

# Always include the dependency file unless we run the clean command,
# which will make it even if it does not exist
ifneq ($(MAKECMDGOALS), clean)
include $(EXECUTABLE).d
endif


