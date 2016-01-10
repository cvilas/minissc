#======================================================================== 
# Package: MiniSSC
# Authors: Vilas Kumar Chitrakaran (cvilas@ces.clemson.edu)
# Start Date: Sat May 18 06:46:12 edt 2002
# ----------------------------------------------------------------------  
# File: makefile
#========================================================================  
#Name of the package
PKG = MiniSSC

# ----- Directories -----
INSTALLDIR = /usr/local
INSTALLHEADERPATH= $(INSTALLDIR)/include/$(PKG)
INSTALLLIBPATH= $(INSTALLDIR)/lib/
INSTALLBINPATH = $(INSTALLDIR)/bin/
INSTALLSRCPATH = $(INSTALLDIR)/src/

# ----- Doxygen documentation parameters -----
DOCNAME = Mini SSC II Motion Controller
DOCSOURCE = *.hpp
DOCTARGET = 

# Libraries, headers, and binaries that will be installed.
LIBS = lib$(PKG).so lib$(PKG).a
BINS = MiniSSC.t
HDRS = MiniSSC.hpp
#SRC = *.cpp

# ---- compiler options ----
CC = g++
LD = g++
CFLAGS = -Wall -fexceptions -O2 -fpic -c
LDFLAGS = -Wall -fexceptions -fno-builtin -D_REENTRANT -O2 -o
INCLUDEHEADERS =
INCLUDELIBS = -lMiniSSC
OBJ = MiniSSC.o
TARGET = $(LIBS) $(BINS)
CLEAN = rm -rf *.o $(TARGET) *.dat


# ========== Targets ==========
targets: $(TARGET)

lib$(PKG).a: $(OBJ)
	ar crv $@ $(OBJ)
	ranlib $@

lib$(PKG).so: $(OBJ)
	$(LD) -shared -o $@ $(OBJ)


# ----- MiniSSC -----
MiniSSC.o: MiniSSC.cpp MiniSSC.hpp
	$(CC) $(CFLAGS) $< $(INCLUDEHEADERS)

# ----- MiniSSC.t -----
MiniSSC.t : MiniSSC.t.cpp
	$(LD) $(LDFLAGS) $@ $? MiniSSC.o


# ---- make rules ----
clean:
	@echo
	@echo ----- Package $(PKG), Cleaning -----
	@echo
	$(CLEAN)
	if (test -d examples) ; then (cd examples; make clean);fi

install:
	@echo
	@echo ----- Package $(PKG), Installing to $(INSTALLDIR) -----
	@echo
	if !(test -d $(INSTALLLIBPATH)); then (mkdir $(INSTALLLIBPATH)); fi
	for i in ${LIBS}; do (cp $$i $(INSTALLLIBPATH)); done
	if !(test -d $(INSTALLHEADERPATH)); then (mkdir $(INSTALLHEADERPATH)); fi
	for i in ${HDRS}; do (cp $$i $(INSTALLHEADERPATH)); done
