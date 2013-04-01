OBJECTS = SimEntity.o Simulation.o Square.o RobotObject.o RockObject.o LavaObject.o WaterObject.o MudObject.o BallObject.o BlockObject.o HoleObject.o EnergyObject.o JamProperty.o FogProperty.o Sight.o NormalProbe.o EmptyProbe.o  SearchRobot.o
TARGETS = checkconf cs229sim create
HEADERS = Interfaces.h
CPPFLAGS = -Wall --pedantic 
CPP = g++

all: $(TARGETS)

checkconf: checkconf.cpp $(OBJECTS) $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ checkconf.cpp $(OBJECTS)

create: create.cpp $(OBJECTS) $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ create.cpp $(OBJECTS)

cs229sim: cs229sim.cpp $(OBJECTS) $(HEADERS)
	$(CPP) $(CPPFLAGS) -o $@ cs229sim.cpp $(OBJECTS)

clean:
	# I am not making the rm -f mistake again, nothing is deleted by mistake this time, heh heh
	rm $(OBJECTS)
	rm $(TARGETS)
