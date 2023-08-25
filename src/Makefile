FLAGS=-Wall -Wextra -Werror -std=c++17 -pedantic
GTEST=-lgtest -lgtest_main -pthread
COVER=-fprofile-arcs -ftest-coverage
ASAN=#-fsanitize=address -fanalyzer

all: install start

install:
	cmake -S . -B ./Build && cd ./Build && make

start:
	./Build/SmartCalc

uninstall:
	rm -rf build

clean:
	rm -rf build
	rm -f SmartCalc
	rm -rf SmartCalc_manual
	rm -f SmartCalc_v2.0.tar.gz
	rm -rf ./Tests/CMakeFiles
	rm -f ./*.info ./*.gcda ./*.gcno ./*.gcov
	rm -rf ./coverage
	rm -f ./test

dvi: 
	makeinfo --html smartcalc.texi
	open SmartCalc_manual/index.html 

dist:
	tar czvf SmartCalc_v2.0.tar.gz ./Model ./View ./Controller \
	CMakeLists.txt main.cc Makefile smartcalc.texi

tests:
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./Testing/tests.cc ./Model/Model.cc -o test
	./test

gcov_report:
	geninfo . -b . -o ./coverage.info --no-external
	genhtml coverage.info -o ./coverage
	open coverage/index.html

lint:
	clang-format -n ./Model/*.cc ./Model/*.h
	clang-format -n ./View/*.cc ./View/*.h
	clang-format -n ./Controller/*.cc ./Controller/*.h
	clang-format -n ./Testing/*.cc
	clang-format -n ./main.cc

leaks:
	leaks -atExit -- ./test