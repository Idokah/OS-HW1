
CFLAGS = -Wall
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex1_q1

all: $(PROG) test 

$(PROG).o: $(PROG).c $(PROG).h
	@$(ECHO)
	$(CC) $(CFLAGS) -c $(PROG).c -o $(PROG).o

$(PROG): $(PROG).o $(PROG).h
	$(CC) $(CFLAGS) $(PROG).o -o $(PROG)

test: $(PROG)
	./$(PROG) < in.txt > out.log

clean: 
	rm -rf $(PROG) *.log *.o
