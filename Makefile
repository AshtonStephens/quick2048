 #Makefile
#
# Purpose: to compile autonomous flight program
# By: Ashton Stephens
# Date : 08/10/17
#

IDIRS	  = ./
SERIAL_RX = FRSKY_TELEM
SERIAL_TX = SEND7 


# # # # # # # # # # # # # # # # 
# This is where you keep your .h files

CC = clang++
IFLAGS  = $(patsubst %,-I%,$(IDIRS))
CFLAGS  = -Wall -Wextra -Werror -Wfatal-errors $(IFLAGS)
LDFLAGS = 
DBFLAGS = -g -DDEBUG
LDLIBS  = -lrt -lpthread -ldl
RM_OBJS = && rm *.o

PROTOCALLS = $(SERIAL_RX) $(SERIAL_TX)
DEF_FLAGS = $(patsubst %,-D%,$(PROTOCALLS))

%.o: %.c
	$(CC) $(DEF_FLAGS) $(CFLAGS) -c -o $@ $<

%.o.test: %.c
	$(CC) $(DEF_FLAGS) $(DBFLAGS) $(CFLAGS) -c -o $*.o $<

%.o.shared: %.c
	$(CC) $(DEF_FLAGS) $(CFLAGS) -c -fPIC -o $@ $<
	
%.so: %.o.shared
	$(CC) $< -shared -o $@ -ldl

# # # # # # # # # # # # # # # # 
# stuff you might have to change 
# 	|	|	|
# 	V	V	V

all: 2048

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
