CXXFLAGS=-ggdb -std=c++20
GTEST_LIBS=-lgtest -lgtest_main -pthread -fsanitize=address,undefined

gtests: gtest/gtestmain.cpp student_gtests.o ladder.o dijkstras.o
	g++ $(CXXFLAGS) gtest/gtestmain.cpp student_gtests.o ladder.o dijkstras.o -o gtests $(GTEST_LIBS)

student_gtests.o: gtest/student_gtests.cpp src/ladder.h src/dijkstras.h
	g++ $(CXXFLAGS) -c gtest/student_gtests.cpp -o student_gtests.o

ladder.o: src/ladder.h
	g++ $(CXXFLAGS) -c src/ladder.cpp -o ladder.o

dijkstras.o: src/dijkstras.h
	g++ $(CXXFLAGS) -c src/dijkstras.cpp -o dijkstras.o

clean:
	/bin/rm -f gtests *.o