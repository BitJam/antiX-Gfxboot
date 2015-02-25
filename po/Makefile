
PO_DIR   := po
TR_DIR   := tr
PO_FILES := $(wildcard $(PO_DIR)/*.po)
LANGS    := $(notdir $(basename $(PO_FILES)))
TR_FILES := $(addprefix $(TR_DIR)/, $(addsuffix .tr,$(LANGS)))

.PHONY: all clean

all: text.inc $(TR_FILES)
	touch .ready

$(TR_FILES): $(TR_DIR)/%.tr : $(PO_DIR)/%.po text.inc  | $(TR_DIR)
	bin/po2txt $< >$@

# en.tr uses msgids from bootloader.pot
$(TR_DIR)/en.tr text.inc: bootloader.pot | $(TR_DIR)
	bin/po2txt $< >$(TR_DIR)/en.tr

$(TR_DIR):
	mkdir -p $@

clean:
	rm -rf .ready text.inc $(TR_DIR)/*.tr

distclean:
	rm -rf .ready text.inc $(TR_DIR)

