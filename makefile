CC        =g++
CFLAGS    =-c -std=gnu++11 -Wall -O3
LDFLAGS   =-lstdc++
INCLUDE   =-I./include/
OBJDIR    =obj/
OBJLIST   = qTree.o main.o
OBJECTS   = $(addprefix $(OBJDIR), $(OBJLIST) )

all:a

a: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): ./$(OBJDIR)%.o: src/%.cpp
	$(CC) $(CFLAGS) $? -o $@ $(INCLUDE)

clean:
	del obj\*.o