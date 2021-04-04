CC= gcc
EXEC= tail wordcount wordcount-dynamic
CFLAGS= -std=c99  -pedantic -Wall -Wextra -g

OBJECT= htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_move.o htab_size.o
LIBS= htab.h htab_structs.h

LD_LIBRARY_PATH="."

all: $(EXEC) libhtab.so libhtab.a

tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

wordcount.cc:
	g++ -std=c++17 -pedantic -Wall wordcount.cc

############ todo
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) $^ -o $@

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) $^ -o $@
wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $<
io.o: io.c io.h
	$(CC) $(CFLAGS) -c $<
############ todo

# object files
htab_bucket_count.o: htab_bucket_count.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_clear.o: htab_clear.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_erase.o: htab_erase.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_find.o: htab_find.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_for_each.o: htab_for_each.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_free.o: htab_free.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_hash_function.o: htab_hash_function.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_init.o: htab_init.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_lookup_add.o: htab_lookup_add.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_move.o: htab_move.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

htab_size.o: htab_size.c $(LIBS)
	$(CC) $(CFLAGS) -fPIC -c $<

# create static library
libhtab.a: $(OBJECT)
	ar rcs $@ $^

#link dynamically
libhtab.so: $(OBJECT)
	$(CC) $(CFLAGS) -fPIC -shared  $^ -o $@
# $(CC) $(CFLAGS) -fPIC -shared -L "." $^ -o $@
# gcc wordcount.o  -L "." -l htab -o .statically-linked
# can be now executed in shell like ./statically-linked (TODO - change the name)


#create the shared library


clean:
	rm $(EXEC) *.o libhtab.so libhtab.a

run: tail
	./tail

add_git:
	git add *.h *.c *.cc Makefile