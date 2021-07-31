CC = g++
CFLAGS = -Wall -c
LFLAGS = -lpthread -lrt
TARGET = mizzo

all: $(TARGET)

$(TARGET): main.o belt.o producer.o consumer.o
	$(CC) main.o belt.o producer.o consumer.o -o $(TARGET) $(LFLAGS)

main.o: main.C
	$(CC) $(CFLAGS) main.C

belt.o: belt.C belt.h
	$(CC) $(CFLAGS) belt.C

producer.o: producer.C producer.h
	$(CC) $(CFLAGS) producer.C

consumer.o: consumer.C consumer.h
	$(CC) $(CFLAGS) consumer.C

clean:
	rm -f core *.o $(TARGET)
