#Set the QTDIR path to point to your QT installation

QTDIR=/Users/calvarez/dev/QtSDK
QTDIR_DESKTOP=$(QTDIR)/Desktop/Qt/473/gcc
QTLIBDIR=$(QTDIR_DESKTOP)/lib/

#Compilation options
CXX=g++ -g
INCLUDEPATH := -I $(QTDIR_DESKTOP)/include/Qt -I $(QTDIR_DESKTOP)/include/

#Intermediate object files
ODIR=obj
_OBJECTS = Room.o RoomReader.o Snake.o SnakeDriver.o SnakeEvent.o SnakeListener.o
OBJECTS = $(patsubst %, $(ODIR)/%,$(_OBJECTS))

#QT libraries to which we link
_QTLIBS=QtCore QtGui
QTLIBS=$(join $(_QTLIBS:%=$(QTLIBDIR)/%.framework/Versions/Current/), $(_QTLIBS:%=%))
LDFLAGS = $(QTLIBS)

BINDIR=bin
TARGET=$(BINDIR)/snake

$(ODIR)/%.o: %.cpp
	mkdir -p $(ODIR)
	$(CXX) -c   $(INCLUDEPATH) -o $@ $< $(CCFLAGS)


$(TARGET): $(OBJECTS) 
	mkdir -p $(BINDIR)
	$(CXX) -o $@ $(LDFLAGS) $^

compile: $(OBJECTS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TARGET) && rmdir $(ODIR) $(BINDIR)
