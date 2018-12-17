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
