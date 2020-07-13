TARGET := led

OBJ += touch.c
CC := gcc

$(TARGET):$(OBJ)
	$(CC) $^ -o $@

clean:
	rm $(TARGET)
go:
	./$(TARGET)
