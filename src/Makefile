GFXBOOT_COMPILE := gfxboot-compile

export PATH := $(PATH):../bin

BFLAGS          := -O -v -L ../..
PO_READY        := ../po/.ready

.PHONY: all clean distclean

test:
	echo $(PATH)

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

