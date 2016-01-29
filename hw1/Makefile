CC = g++
CFLAGS = -Wall
#INCS = -I$(TROOT)/arm-linux/include
#LIBS = -L$(TROOT)/lib/gcc/arm-linux/4.2.1
#OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
LIB_SRCS =  data.cpp pla.cpp pocket_pla.cpp
OBJS = $(LIB_SRCS:.cpp=.o)

TARGET1 = q17
TARGET2 = q18
TARGETS = $(TARGET1) $(TARGET2)


$(TARGET1): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(TARGET1).cpp

$(TARGET2): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(TARGET2).cpp

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c $<

clean:
	rm -f *.o
	rm -f $(TARGETS)
