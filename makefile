# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
OPTFLAGS = -O3

all     : bin/sc
        @echo -n ""

# optimized version
bin/sc  : SC_opt.o main_opt.o
                        $(CC) $(OPTFLAGS) SC_opt.o main_opt.o -o bin/sc
main_opt.o              : src/main.cpp inc/SC.h
                        $(CC) $(CFLAGS) $< -Ilib -o $@
SC_opt.o        : src/SC.cpp inc/SC.h
                        $(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
                rm -rf *.o lib/*.a lib/*.o bin/*


