TARGET=myext2
C_FILES=$(shell ls *.c)
BASE=$(basename $(C_FILES))
OBJS=$(addprefix obj/, $(addsuffix .o , $(BASE)))

$(TARGET):$(OBJS)
	rm -f $(TARGET)
	gcc -fno-stack-protector -g  -o $(TARGET) $(OBJS)

obj/%.o:%.c
	@if test ! -e obj; then\
	    mkdir obj;\
	fi;
	gcc -fno-stack-protector -g -c -o $@ $<

clean:
	rm -f obj/*.o
	rm -f $(TARGET)

clext2:
	rm -f *.ext2
