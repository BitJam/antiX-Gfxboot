% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Miscellaneous options menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/mx-options.setdefault {

  xmenu.mx-options .xm_current

  "options.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /mx-options.default exch def
    0
    mx-options.data {
      .opt.option get exec options.default eq { exit } if
      1 add
    } forall

    dup mx-options.data length ge { pop 0 } if

  } { pop 0 } ifelse

  put

} def

/mx-options.data [
      [ /txt_none         ""                 ]
      [ "checkmd5"        "checkmd5"         ]
      [ "checkfs"         "checkfs"          ]
      [ "toram"           "toram"            ]
      [ "from=usb"        "from=usb"         ]
      [ "nousb2"          "nousb2"           ]
      [ "acpi=off"        "acpi=off"         ]
      [ "hwclock=utc"     "hwclock=utc"      ]
      [ "hwclock=local"   "hwclock=local"    ]
      [ "private"         "private"          ]
      [ "bootchart"       "bootchart initcall_debug printk.time=y" ]
      [ "savestate"       "savestate"        ]
      [ "nosavestate"     "nosavestate"      ]

  ] def

/.opt.label  0 def
/.opt.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build options list.
%
% ( ) ==> ( )
%
/mx-options.init {
  /xmenu.mx-options .xm_size array def
  /xmenu xmenu.mx-options def
  xmenu .xm_title  /txt_options put

  "options.men" findfile dup .undef ne {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % Create array to hold the data
    dup length dup
    /mx-options.data exch array def

    % Now have: Array, length in stack

    1 sub
    0 1 rot {
      over over get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      mx-options.data 3 1 roll put
    } for

  } if
  pop

  /labels.size mx-options.data length       def
  /labels.max  mx-options.data length 1 sub def

  /mx-options.labels  labels.size array def
  /mx-options.options labels.size array def


  0 1 labels.max {
    dup
    mx-options.labels exch dup exch
    mx-options.data exch get .opt.label get put

    mx-options.options exch dup exch
    mx-options.data exch get .opt.option get put
  } for

  mx-options.setdefault
  xmenu .xm_list    mx-options.labels   put
  %xmenu .xm_title   /txt_options     put

  /mx-options.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update options mode.
%
% ( ) ==> ( )
%
/mx-options.update {
  /xmenu xmenu.mx-options def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show options menu.
%
% ( ) => ( )
%
/panel.mx-options {
  "main" help.setcontext
  window.xmenu
  dup .xmenu xmenu.mx-options put
  dup .xmenu.update /mx-options.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.mx-options.width {
  /xmenu xmenu.mx-options def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.mx-options.update {
  /xmenu xmenu.mx-options def

  pmenu.panel.update
} def


