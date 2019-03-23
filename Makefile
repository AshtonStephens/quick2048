# Makefile
#
# Repurposed from compiling an autonomous drone to compiling
# a game of 2048 with absurd bells and whistles.
#
# by: Ashton Stephens
# date : 08-10-17
# documented : 03-23-19
#

IDIRS	  = ./

# # # # # # # # # # # # # # # # 
# This is where you keep your .h files

CC = clang++
IFLAGS  = $(patsubst %,-I%,$(IDIRS))
CFLAGS  = -Wall -Wextra -Werror -Wfatal-errors $(IFLAGS)
LDFLAGS = 
DBFLAGS = -g -DDEBUG
LDLIBS  = -lrt -lpthread -ldl
RM_OBJS = && rm *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o.test: %.c
	$(CC) $(DBFLAGS) $(CFLAGS) -c -o $*.o $<

%.o.shared: %.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $<

# # # # # # # # # # # # # # # # 
# stuff you might have to change 
# 	|	|	|
# 	V	V	V

all: 2048 #main

EXECUTABLES = 2048 main

MAIN_INCLUDES  = main.o score.o board.o  game.o
2048_INCLUDES  = main.o score.o board.o  game.o

main: $(MAIN_INCLUDES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(RM_OBJS) 
main_test: $(patsubst %,%.test,$(MAIN_INCLUDES))
	$(CC) $(LDFLAGS) -o $@ $(MAIN_INCLUDES) $(LDLIBS) $(RM_OBJS)

2048: $(2048_INCLUDES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(RM_OBJS) 
2048_test: $(patsubst %,%.test,$(2048_INCLUDES))
	$(CC) $(LDFLAGS) -o $@ $(2048_INCLUDES) $(LDLIBS) $(RM_OBJS)

clean: 
	rm *~ *.swp *.o $(EXECUTABLES) 2> /dev/null; true
