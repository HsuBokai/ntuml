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
TARGET5 = logistic
OBJ5 = data.o sorted_data.o gradient_descent.o utils.o tester.o
TARGETS = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

newton: newton.o
	$(CC) $(CFLAGS) $< -o $@
$(TARGET5): $(OBJ5)
	$(CC) $(CFLAGS) $^ -o $@ $@.cpp
$(TARGET4): $(OBJ4)
	$(CC) $(CFLAGS) $^ -o $@ $@.cpp
$(TARGET3): $(OBJ3)
	$(CC) $(CFLAGS) $^ -o $@ $@.cpp
$(TARGET2): $(OBJ2)
	$(CC) $(CFLAGS) $^ -o $@ $@.cpp
$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS) $^ -o $@ $@.cpp

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c $<

clean:
	rm -f *.o
	rm -f $(TARGETS)
