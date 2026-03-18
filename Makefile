
TOOL_CHAIN?=arm-mingw32ce

CC=$(TOOL_CHAIN)-gcc
CPP=$(TOOL_CHAIN)-g++
LD=$(TOOL_CHAIN)-g++
WINDRES=$(TOOL_CHAIN)-windres

CFLAGS=-march=armv5tej -mcpu=arm926ej-s -Wno-attributes -DWC_NO_BEST_FIT_CHARS -D_WIN32_WCE=0x0600 -D_MAX_PATH=260 -D_UNICODE -DUNICODE -D_WIN32_IE=0x0400 -fvisibility=hidden -fno-pic -Wall -Wno-unused-variable -I. -I./omnithreadce -I./res -D__T\(x\)=L\#\#x

LDFLAGS=$(CFLAGS) -fno-strict-aliasing -lcoredll -lcommctrl -lws2 -static
CPPFLAGS=$(CFLAGS) -fvisibility=hidden

COMPAT_SOURCES=compat.cpp

SOURCES=AboutBox.cpp \
	AuthDialog.cpp \
	ClientConnectionCopyRect.cpp \
	ClientConnectionCoRRE.cpp \
	ClientConnection.cpp \
	ClientConnectionHextile.cpp \
	ClientConnectionRaw.cpp \
	ClientConnectionRRE.cpp \
	d3des.c \
	KeyMap.cpp \
	Log.cpp \
	MRU.cpp \
	SessionDialog.cpp \
	stdhdrs.cpp \
	vncauth.c \
	VNCOptions.cpp \
	vncviewer.cpp \
	VNCviewerApp.cpp \
	VNCViewerAppCE.cpp \
	\
	omnithreadce/ce.cpp\
	\
	$(COMPAT_SOURCES)\
	\
	res/vncviewer.rc

OBJS=$(patsubst %.rc,%.o,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES))))

build: vncviewer.exe

clean:
	rm -f *.exe *.o */*.o

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

.cpp.o:
	$(CPP) -c $< -o $@ $(CPPFLAGS)

res/vncviewer.o: res/vncviewer.rc
	$(WINDRES) -i $< -o $@ -vvv

vncviewer.exe: $(OBJS)
	@echo $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

