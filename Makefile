all:
	gcc engine.c $(MRUBY_HOME)/build/host/lib/libmruby.a -I $(MRUBY_HOME)/include $(shell pkg-config --cflags --libs sdl2)

debug:
	gcc -g engine.c $(MRUBY_HOME)/build/host/lib/libmruby.a -I $(MRUBY_HOME)/include $(shell pkg-config --cflags --libs sdl2)
