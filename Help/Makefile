BINDIR       := $(shell [ -x bin/gfxboot ] && echo bin/ )
GFXBOOT      := $(BINDIR)gfxboot
SPLIT        := bin/split-html

BLURB        := test/blurb.html

DISTROS      := antiX MX
HELP_FILES   := $(addsuffix /en.hlp, $(DISTROS))
MASTER_FILES := $(addsuffix /en.html, $(DISTROS))
SPLIT_DIRS   := $(addsuffix /en-split, $(DISTROS))
TEST_FILES   := $(addsuffix .html, $(addprefix test/, $(DISTROS)))
TEST_GROUPS  := $(addprefix test-, $(DISTROS))

# fkey_help=F1 fkey_lang=F2 fkey_timezone=F3 fkey_options=F4 fkey_desktop=F6

.PHONY: all help clean distclean $(DISTROS) $(TEST_GROUPS)

all: $(HELP_FILES)

help: $(HELP_FILES)

$(DISTROS): % : %/en.hlp

$(HELP_FILES): %.hlp: %-split %.html 
	rm -rf $</* $@
	$(SPLIT) --dir $< $(word 2, $^)
	$(GFXBOOT) --help-create $@ $</*.html || true
	@#sed -i 's/•/*/g' $@
	test -e $@

$(TEST_GROUPS): test-% : test/%.html

$(TEST_FILES): test/%.html : %/en.html $(BLURB)
	bin/make-doc $^ > $@

$(SPLIT_DIRS): 
	mkdir -p $@

clean:
	rm -rf $(SPLIT_DIRS) $(HELP_FILES) $(TEST_FILES)

distclean: clean

