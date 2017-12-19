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

all: main #game

EXECUTABLES = main #game

MAIN_INCLUDES  = main.o board.o
#GAME_INCLUDES  = game.o board.o

main: $(MAIN_INCLUDES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(RM_OBJS) 
main_test: $(patsubst %,%.test,$(MAIN_INCLUDES))
	$(CC) $(LDFLAGS) -o $@ $(MAIN_INCLUDES) $(LDLIBS) $(RM_OBJS)

game: $(GAME_INCLUDES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(RM_OBJS) 
game_test: $(patsubst %,%.test,$(GAME_INCLUDES))
	$(CC) $(LDFLAGS) -o $@ $(GAME_INCLUDES) $(LDLIBS) $(RM_OBJS)

clean: 
	rm *~ *.swp *.o $(EXECUTABLES) 2> /dev/null; true
