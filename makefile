CFLAGS = -ggdb3

http: src/http.c src/http.h
	cc $? -o http

clean:
	rm http

x := hey dude
dude:
	printf "${x}"

	