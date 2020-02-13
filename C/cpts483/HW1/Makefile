tensor:	  tensor.l tensor.y tensor.h tensorfuncs.c
	bison --debug -d tensor.y && \
	flex -o tensor.lex.c tensor.l && \
	cc -g -o $@ tensor.tab.c tensor.lex.c tensorfuncs.c -lm

clean:
	rm -f tensor tensor.tab.c tensor.tab.h tensor.lex.c
