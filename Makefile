PROG=mineproxy
OBJS= main.o Network.o
LIBS=-lz

.cpp.o:
	g++ -Wall -ggdb -O2 -c -o $@ $<

$(PROG): $(OBJS)
	g++ -Wall -ggdb -O2 $(LIBS) -o $@ $(OBJS)

