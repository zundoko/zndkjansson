#
# @file     Makefile
# @brief    Makefile for jansson test (json library)
#
# @note     https://github.com/zundoko/zndkjansson
#
# @date     2016-12-28
# @authr    zundoko
#

PRJNAME =   zndkjansson

TARGETS = $(PRJNAME)
SRCS    = $(TARGETS:%=%.c)
OBJS    = $(SRCS:%.c=%.o)
DEPEND  =   Makefile.depend

CC      = $(CROSS_COMPILE)gcc
INC     =  -I.
CFLAGS  = $(INC) -c -Wall -Werror
LDFLAGS = 
LIBS    = `pkg-config --cflags --libs jansson`

.PHONY: all
all: $(TARGETS)

.PHONY: $(TARGETS)
$(TARGETS): %:%.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	-rm -rf $(OBJS) $(TARGETS) *~

.PHONY: depend
depend:
	-rm -rf $(DEPEND)
	$(CC) -MM -MG $(CFLAGS) $(SRCS) > $(DEPEND)

-include  $(DEPEND)

# end
