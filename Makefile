CC=clang
CXX=clang++

CFLAGS = -std=c++20

LIBS =
ALL_LIBS = -Wl,-whole-archive $(patsubst %,-l%,$(LIBS)) -Wl,-no-whole-archive

LPATH = -I.


all: city city_node

city_node: city_node.cc
	@$(CXX) $(CFLAGS) -g -o $@  $<

city: city.cc
	@$(CXX) $(CFLAGS) -g -o $@  $<

# do not automatically delete *.o
.PRECIOUS: %.o


run: clean template
	./template


clean:
	rm -rf *.o city city_node
