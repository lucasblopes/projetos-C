TARGET  = beale

SRCDIRS = ./source
INCDIRS = ./include/

CC		= gcc
CFILES		= $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.c))
CFLAGS		= -Wall -std=c99
LDFLAGS		= $(foreach D, $(INCDIRS), -I$(D))
OBJFILES	= $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) -o $@ $^ $(LBFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	-rm -f source/*.o

purge: clean
	-rm -f *.txt beale
