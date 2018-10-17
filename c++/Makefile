gpio: ServoSpeed.o GPIO.o
	g++ -std=c++0x -pthread ServoSpeed.o GPIO.o -o gpio

ServoSpeed.o: GPIO.cpp GPIO.h
	g++ -std=c++0x -g -Wall -c ServoSpeed.cpp

GPIO.o: GPIO.cpp GPIO.h
	g++ -g -Wall -c GPIO.cpp

clean:
	rm ServoSpeed.o GPIO.o gpio
