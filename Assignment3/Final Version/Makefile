# The user needs to assign these for their project
# CXXFLAGS sets the defaults for the compiler flags
CC = g++
CXXFLAGS = -c -Wall
SOURCES = Cache.cc Set.cc Block.cc Simulation.cc
OBJECTS = $(SOURCES: .cc = .o)
EXECUTABLE = Simulation

all: $(SOURCES) $(EXECUTABLE)

#Links all of the .o files
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

#Clean up unnecessary files and remake dependency file
clean:
	rm -f *~
	rm -f *.o
	rm -f *.swp
	rm -f $(EXECUTABLE)
	$(CC) $(SOURCES) -MM > $(EXECUTABLE).d

# Always include the dependency file unless we run the clean command,
# which will make it even if it does not exist
ifneq ($(MAKECMDGOALS), clean)
include $(EXECUTABLE).d
endif


