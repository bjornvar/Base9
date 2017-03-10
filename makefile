default: all

all: b9 $(b9_programs)

programs = b9 b9test
b9_objects = main.o b9jit.o b9.o b9hash.o b9ras.o
b9test_objects = b9.o b9jit.o b9test.o b9hash.o
b9_programs = program.so bench.so test.so

omr_srcdir := ./omr
IJIT = $(omr_srcdir)/jitbuilder/release/include
IJIT1 = $(IJIT)/compiler
LIB=$(omr_srcdir)/jitbuilder/release/libjitbuilder.a
LINK=-ldl -lm $(LIB)

cflags = -std=c++11 -fPIC -fno-rtti -rdynamic
b9: cflags+=-I./omr/compiler/ 
b9jit.o: cflags+=-I$(IJIT) -I$(IJIT1)

$(foreach program,$(programs),$(eval $(program): $($(program)_objects)))

%.cpp: %.src
	node b9.js $^ > $@

%.o : %.cpp
	$(CXX) -o $@ -c $< $(cflags) $(CFLAGS)

%.so: %.o
	$(CXX) -std=c++11 -shared -o $@ $^ $(CFLAGS)

$(programs): $(LIB)
	$(CXX) -o $@ -lm $^ -ldl $(cflags) $(CFLAGS) $(LINK)

$(LIB): $(omr_srcdir)
	(cd $(omr_srcdir)/; ./configure)
	(cd $(omr_srcdir)/jitbuilder; make)

program: b9
	node b9.js program.src > program.cpp
	cat program.cpp
	$(CXX) -std=c++11 -shared -o program.so program.cpp
	./b9 -debug program.so

bench: b9 bench.so
	./b9

test: b9 test.so b9test $(b9_programs)
	./b9 test.so
	./b9test  

clean:
	$(RM) b9
	$(RM) $(b9_objects)
	$(RM) $(b9_programs)

$(omr_srcdir):
	if [ -d ../omr ]; then ln -s ../omr ./omr; else git clone https://github.com/jduimovich/omr.git; fi

.PHONY: program bench test clean
