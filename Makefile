CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = hotel

# Lista de objetos a serem compilados
OBJECTS = main.o cliente.o funcionario.o quarto.o estadia.o util.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)