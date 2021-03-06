# Makefile:
# $Id$

CXXFLAGS = -w2 -g -I.. -T1 -I/usr/local/include
OFLAGS   = -O
LDFLAGS  = -M $(CXXFLAGS) -l vf.lib -l vf_ftp.lib -lsocket++ -L.. -L/usr/local/lib

INC = 
SRC = $(wildcard *.cc *.c)
OBJ = ftpparse.o
EXE = cftp
LIB = vf_ftp.lib
DEP = depends.mak
ALL = $(LIB) $(EXE)

# default target
all: $(ALL)

# custom targets

# special targets
$(LIB): $(OBJ)
	wlib -n -q -b $@ $^

$(EXE): $(LIB)

$(OBJ): $(INC)

# standard targets

-include $(DEP)

deps: $(DEP)

$(DEP): $(SRC) $(INC)
	@makedeps -f - -- $(CXXFLAGS) -- $(SRC) > $@

clean:
	rm -f *.o *.err core *.dmp *.log

empty: clean
	rm -f $(ALL) *.dbg *.map *.map.sort

# development targets

run: stop vf_tar
	vf_tar -u -vvv -p dir dir.tar &

noisy: stop vf_tar
	vf_tar -u -vvvv &

debug: stop vf_tar
	wd vf_tar -u -vvvv -p dir dir.tar &

stop:
	-slay -f vf_tar || true

# rule forcing run of usemsg after linking
%: %.o
	$(LINK.o) -o $@ $^ $(LDLIBS)
	-usemsg -c $@ $@.c*
	chown root $@
	chmod u+s $@
	-sort $@.map > $@.map.sort

%: %.c
	$(LINK.c) -o $@ $< $(LDFLAGS)
	$(RM) $@.o
	-usemsg -c $@ $<
	chown root $@
	chmod u+s $@

%: %.cc
	$(LINK.cc) -o $@ $< $(LDFLAGS)
	$(RM) $@.o
	-usemsg -c $@ $<
	chown root $@
	chmod u+s $@

# $Log$
# Revision 1.3  2012/02/05 06:08:09  sam
# ftp file system
#
# Revision 1.2  1999/10/11 14:58:54  sam
# doesn't make deps automatically anymore    e
#
# Revision 1.1  1999/07/21 13:44:02  sam
# Initial revision
#
