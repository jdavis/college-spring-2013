CPP = g++
CPPFLAGS = -Wall --pedantic
TARGETS = solution
OBJECTS = solution.o

default: $(TARGETS)

%.o: %.cpp
	@$(CPP) -c -o $@ $< $(CPPFLAGS)

solution: $(OBJECTS)
	@$(CPP) -o a.out $^ $(CPPFLAGS)

sample: $(TARGETS)
	@./a.out sample.in

small: $(TARGETS)
	@./a.out small-practice.in

large: $(TARGETS)
	@./a.out large-practice.in

clean:
	rm $(OBJECTS)
	rm a.out
