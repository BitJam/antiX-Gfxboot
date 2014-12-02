BINDIR          := $(shell [ -x ../bin/gfxboot-compile ] && echo ../bin/ )

GFXBOOT_COMPILE := $(BINDIR)gfxboot-compile
BFLAGS          := -O -v -L ../..
PO_READY        := ../po/.ready

.PHONY: all clean distclean

all: main.bin

main.bin: main.bc *.inc $(PO_READY)
	@echo $(GFXBOOT_COMPILE)
	$(GFXBOOT_COMPILE) $(BFLAGS) -l main.log -c $< $@

$(PO_READY):
	make --directory $(@D)

clean:
	rm -f main.bin main.log

distclean: clean
	rm -f *.log *~ .*.swp

