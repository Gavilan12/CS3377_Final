## environmental variables
CC := gcc
CFLAGS = -I$(HOME)/local/gsl-2.5/include
LDFLAGS = -L$(HOME)/local/gsl-2.5/lib -lgsl -lgslcblas
## rules
dealer : dealer.o
	$(CC) -o $@ $<
dealer.o : dealer.c
	$(CC) -c $<
hand: hand.o
	$(CC) $(LDFLAGS) -o $@ $<
hand.o: hand.c
	$(CC) -c $(CFLAGS) $<
pitboss : pitboss.o
	$(CC) -o $@ $<
pitboss.o : pitboss.c
	$(CC) -c $<
Signals: Signals.o
	$(CC) $(LDFLAGS) -o $@ $<
Signals.o: Signals.c
	$(CC) -c $(CFLAGS) $<
ForkExecPipes : ForkExecPipes.o
	$(CC) -o $@ $<
ForkExecPipes.o : ForkExecPipes.c
	$(CC) -c $<
Prob1: Prob1.o
	$(CC) $(LDFLAGS) -o $@ $<
Prob1.o: Prob1.c
	$(CC) -c $(CFLAGS) $<

## PHONY targets to clean
.PHONY : clobber clean neat echo
clobber : clean
	$(RM) $(EXEC)
clean : neat
	$(RM) $(OBJ)
neat : 
	$(RM) *~ .*~
echo : 
	@echo $(OBJ) 
