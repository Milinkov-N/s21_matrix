CC=gcc
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=
SRC=s21_matrix.c
OBJ=$(SRC:.c=.o)
OS = $(shell uname)

ifeq ($(OS), Linux)
	CKFLAGS=-lcheck -lm -lpthread -lrt
else
	CKFLAGS=-lcheck -lm -lpthread
endif

all: s21_matrix.a gcov_report

s21_matrix.a: $(OBJ)
	ar -crs s21_matrix.a $(OBJ)

playground: s21_matrix.a
	$(CC) $(CFLAGS) $(LDFLAGS) main.c s21_matrix.a -o pg

test: clean tests.c s21_matrix.a
	$(CC) $(CFLAGS) tests.c $(SRC) -o run $(CKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

valgrind:
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBSOURCES) tests_valgrind.c -o vtests_run
	sh valgrind.sh ./vtests_run

docker_test:
	sh ./run.sh

mini_verter:
	cd ../materials/build && sh run.sh && cd ../../src

rebuild: clean all

clean:
	rm -rf *.o \
		*.a \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
		pg \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		report.info
