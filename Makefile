SHELL           := /bin/bash

DEFAULT_LANG    :=
NO_1024         :=
ADD_TEXT_OPTS   := --position 280,490 --text "press F1 for help"

DISTROS         := antiX MX
COMMON_FILES    := Input/common/* fonts/*.fnt po/tr/*.tr
GFXBOOT_BIN     := gfxtheme

ADD_TEXT        := bin/add-image-text
TEST_TARGETS    := $(addprefix test-,   $(DISTROS))
OUT_ISO_DIRS    := $(addprefix Output/, $(addsuffix /isolinux, $(DISTROS)))
OUT_SYS_DIRS    := $(addprefix Output/, $(addsuffix /syslinux, $(DISTROS)))
OUT_DIRS        := $(OUT_SYS_DIRS) $(OUT_ISO_DIRS)
IMAGE_GROUPS    := $(addsuffix -images, $(DISTROS))
HELP_DIRS       := $(addprefix Help/,   $(DISTROS))
HELP_FILES      := $(addsuffix /en.hlp, $(HELP_DIRS))

THEME_FILE      := src/main.bin
SRC_FILES       := $(wildcard src/*.inc) src/main.bc

SUB_DIRS        := Help src po

TEST_DIR      	:= iso-dir/isolinux

ISO_FILE     	:= test-gfxboot.iso
ISO_SYMLINK  	:= /data/ISO/test-antiX.iso

-include Makefile.local

.PHONY: all clean distclean antiX MX $(ANTIX_DIR) $(IMAGE_GROUPS)

help:
	@echo "Targets:"
	@echo ""
	@echo "    all          : both MX and antiX"
	@echo "    MX           : create gfxboot for MX distro"
	@echo "    antiX        : create gfxboot for antiX distro"
	@echo ""
	@echo "    clean        : delete output files but not intermediate files"
	@echo "    disclean     : delete all created files"
	@echo "    help         : show this help"
	@echo ""
	@echo "    test-antiX   : create iso file to test antiX bootloader"
	@echo "    test-MX      : create iso file to test MX bootloader"
	@echo "    iso-only     : rebuild the iso file"
	@echo ""
	@echo "    antiX-images : Create bg images with text in Input/antiX"
	@echo "    MX-images    : Create bg images with text in Input/MX"
	@echo ""
	@echo "Create Makefile.local to modify the variables above"
	@echo ""


all: $(DISTROS)

$(DISTROS): % : Output/%/isolinux Output/%/syslinux Help/%/en.hlp $(THEME_FILE)
	cp -a $(COMMON_FILES) Input/$@/* $(word 3,$^) $</
	cp $(THEME_FILE) $</$(GFXBOOT_BIN)
ifdef DEFAULT_LANG
	@echo $(DEFAULT_LANG) > $</lang.def
endif
ifdef NO_1024
	rm -f $</back1024.jpg
endif
	rm -rf $(word 2,$^)
	cp -a $< $(word 2,$^)
	mv $(word 2,$^)/isolinux.bin $(word 2,$^)/syslinux.bin
	mv $(word 2,$^)/isolinux.cfg $(word 2,$^)/syslinux.cfg
	echo 1 > $(word 2,$^)/gfxsave.on
	sed -i 's/APPEND hd0/APPEND hd1/' $(word 2,$^)/syslinux.cfg

$(HELP_FILES): %/en.hlp : % %/en.html
	make --directory Help $(<F) 

$(THEME_FILE): $(SRC_FILES)
	make --directory $(@D)

$(OUT_DIRS):
	mkdir -p $@

clean:
	rm -rf Output $(ISO_FILE) $(dir $(TEST_DIR))

distclean: clean
	@for i in $(SUB_DIRS) ; do [ ! -f $$i/Makefile ] || make -C $$i distclean || break ; done

$(TEST_TARGETS): test-% : %
	rm -rf $(TEST_DIR)
	mkdir -p $(TEST_DIR)
	cp -a Output/$</isolinux/* $(TEST_DIR)
	echo 1 > $(TEST_DIR)/REBOOT
	sed -i -e "s=%RELEASE_DATE%=$$(date +'%x %X')=g" \
		   -e "s/%CODE_NAME%/Killah P/g" \
           -e "s/%FULL_DISTRO_NAME%/Test gfxboot/g" $(TEST_DIR)/isolinux.cfg
	make -B $(ISO_FILE)

$(ISO_FILE):
	[ -L $(ISO_SYMLINK) -o ! -e $(ISO_SYMLINK) ] && ln -sf $$(readlink -f $(ISO_FILE)) $(ISO_SYMLINK) || true
	mkisofs -l -V gfxboot-test -R -J -pad -no-emul-boot -boot-load-size 4 \
    	-boot-info-table -gid 0 -uid 0 -b isolinux/isolinux.bin \
        -c isolinux/isolinux.cat -o $@ iso-dir

iso-only:
	make -B $(ISO_FILE)

# FIXME: a bit backward
$(IMAGE_GROUPS): %-images : images/%-back.jpg Input/%
	$(ADD_TEXT) $(ADD_TEXT_OPTS) $< $(word 2,$^)/back800.jpg
	$(ADD_TEXT) $(ADD_TEXT_OPTS) $< $(word 2,$^)/back640.jpg
ifndef NO_1024
	$(ADD_TEXT) $(ADD_TEXT_OPTS) $< $(word 2,$^)/back1024.jpg
endif

