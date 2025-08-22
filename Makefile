WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
# This is a comment (starting with #)
SRCS = assign.c

# object files are created by converting .c to .o
OBJS = $(SRCS:%.c=%.o)

assign: $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o assign -lm

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 


clean: # remove all machine generated files
	rm -f assign *.o *.out *gcda *gcno *gcov *~
