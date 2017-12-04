all: hello-cpp-world hello-c-world

%: %.cc
	g++ -std=gnu++11 $< -o $@

%: %.c
	gcc $< -o $@

