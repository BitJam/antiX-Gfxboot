#!/bin/bash

for file; do
    grep -q memtest86 $file && continue
    echo $file
    trans=$(grep -A 1 "Memory Test" $file | tail -n 1 | sed 's/\s*"\s*$//')
    echo ""                                    >> $file
    echo "#. txt_memtest_full"                 >> $file
    echo "msgid \"Memory test (memtest86+)\""  >> $file
    echo "$trans (memtest86+)\""               >> $file
done
