
#compiler used
CC = gcc

#flags for individual object file compilation
CFLAGS = -Wall -std=c99 -O3
#RELEASE
# -Wall -std=c99 -O3
#DEVELOPMENT
# -Wall -std=c99 -g

#file extentions
#IEXT = cities
#OEXT = walks
#CEXT = check

#source .c files
SOURCE = $(wildcard *.c)
#object files created
OBJECTS = $(patsubst %.c,%.o,$(SOURCE))
#resources to test
#INPUTS = $(wildcard res/*.$(IEXT))
#output of tests
#OUTPUTS = $(wildcard res/*.$(OEXT))
#ORIGINALS = $(patsubst res/%.$(OEXT),org/%.$(CEXT),$(OUTPUTS))

#executable name
EXECUTABLE = campista

############################################################

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	@for file in $(INPUTS); do \
		echo $$file; \
		./$(EXECUTABLE) $$file; \
	done

#cmp: FORCE $(ORIGINALS)
	
#org/%.$(CEXT): res/%.$(OEXT) FORCE
#	@python3 script.py $< $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm bin/*.o $(EXECUTABLE)
	rm res/*.$(OEXT)

FORCE:
