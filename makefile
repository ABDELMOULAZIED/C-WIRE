EXEC = Main

SRC = main.c avl.c smartrobustesse.c

CC = gcc 


all: $(EXEC)
   
$(EXEC):$(SRC)
	$(CC) -o $@ $^

clean:
	rm -f $(EXEC)
