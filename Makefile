# Makefile

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -g

# External libraries: none in this case
LIBS = 

# Pre-defined macros for conditional compilation
DEFS = -DEBUG_FLAG -DEXPERIMETAL=0

# The final executable program file
BIN = test

# Object files from which $BIN depends 
OBJS = bit.string.o

# This default rule compiles the executable program
$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(LIBS) $(OBJS) $(BIN).c -o $(BIN)

# This rule compiles each modules into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean: 
	rm -f *~ *.o *.swp $(BIN)


