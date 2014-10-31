all: build

build:
	cc -o engine engine.c `simple2d-config` -lmruby
