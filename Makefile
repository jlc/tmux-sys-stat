
TARGET=tmux-sys-stat

OBJS=main.o status.o cpureader.o memreader.o loadaveragereader.o \
		 cpureader_osx.o memreader_osx.o loadaveragereader_osx.o

CXXFLAGS=-D__MACOSX__

ALL: $(OBJS)
	g++ -g -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
