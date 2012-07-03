
TARGET=tmux-sys-stat

OBJS=main.o cpuloader.o memloader.o loadaverageloader.o \
		 cpuloader_osx.o memloader_osx.o loadaverageloader_osx.o

CXXFLAGS=-D__MACOSX__

ALL: $(OBJS)
	g++ -g -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
