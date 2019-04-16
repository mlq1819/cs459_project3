P=program3_1
Q=program3_2
CFLAGS= -g -Wall

all: $(P) $(Q) $(S)

$(P): $(P).o
	g++ $(CFLAGS) $(P).o -o $(P)
	
$(P).o: $(P).cpp
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o
	
$(Q): $(Q).o
	g++ $(CFLAGS) $(Q).o -o $(Q)
	
$(Q).o: $(Q).cpp
	g++ $(CFLAGS) -c $(Q).cpp -o $(Q).o
	
clean:
	rm -rf $(P)
	rm -rf $(P).o
	rm -rf $(Q)
	rm -rf $(Q).o