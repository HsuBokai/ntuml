CC = g++
CFLAGS = -Wall
#INCS = -I$(TROOT)/arm-linux/include
#LIBS = -L$(TROOT)/lib/gcc/arm-linux/4.2.1

#OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
#LIB_SRCS =  data.cpp pla.cpp pocket_pla.cpp
#OBJS = $(LIB_SRCS:.cpp=.o)

TARGET1 = hw1q17
OBJ1 = data.o sorted_data.o pla.o utils.o
TARGET2 = hw1q20
OBJ2 = $(OBJ1) pocket_pla.o
TARGET3 = decision_stump
OBJ3 = data.o utils.o sorted_data.o
TARGET4 = multi_dim_DS
OBJ4 = $(OBJ3)
TARGETS = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)


$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $@ $(TARGET1).cpp

$(TARGET2): $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o $@ $(TARGET2).cpp

$(TARGET3): $(OBJ3)
	$(CC) $(CFLAGS) $(OBJ3) -o $@ $(TARGET3).cpp

$(TARGET4): $(OBJ4)
	$(CC) $(CFLAGS) $(OBJ4) -o $@ $(TARGET4).cpp

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c $<

clean:
	rm -f *.o
	rm -f $(TARGETS)
