
TARGET=tmux-sys-stat

OBJS=main.o cpuloader.o cpuloader_osx.o memloader.o memloader_osx.o

CXXFLAGS=-g

ALL: $(OBJS)
	g++ -g -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
