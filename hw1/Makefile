
CC = g++
CFLAGS = -Wall
#INCS = -I$(TROOT)/arm-linux/include
#LIBS = -L$(TROOT)/lib/gcc/arm-linux/4.2.1
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

TARGET = q17

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c $<

clean:
	rm -f *.o
	rm -f $(TARGET)
