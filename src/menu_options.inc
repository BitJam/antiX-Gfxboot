% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Miscellaneous options menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/options.setdefault {

  xmenu.options .xm_current

  "options.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /options.default exch def
    0
    options.data {
      .opt.option get exec options.default eq { exit } if
      1 add
    } forall

    dup options.data length ge { pop 0 } if

  } { pop 0 } ifelse

  put

} def

/options.data [
      [ /txt_none       ""               ]
      [ "checkmd5"      "checkmd5"       ]
      [ "checkfs"       "checkfs"        ]
      [ "toram"         "toram"          ]
      [ "from=usb"      "from=usb"       ]
      [ "automount"     "automount"      ]
      [ "mount=usb"     "mount=usb"      ]
      [ "mount=all"     "mount=all"      ]
      [ "nousb2"        "nousb2"         ]
      [ "acpi=off"      "acpi=off"       ]
      [ "hwclock=utc"   "hwclock=utc"    ]
      [ "hwclock=local" "hwclock=local"  ]
  ] def

/.opt.label  0 def
/.opt.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build options list.
%
% ( ) ==> ( )
%
/options.init {
  /xmenu.options .xm_size array def
  /xmenu xmenu.options def
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
    /options.data exch array def

    % Now have: Array, length in stack

    1 sub
    0 1 rot {
      over over get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      options.data 3 1 roll put
    } for

  } if
  pop

  /labels.size options.data length       def
  /labels.max  options.data length 1 sub def

  /options.labels  labels.size array def
  /options.options labels.size array def


  0 1 labels.max {
    dup
    options.labels exch dup exch
    options.data exch get .opt.label get put

    options.options exch dup exch
    options.data exch get .opt.option get put
  } for

  options.setdefault
  xmenu .xm_list    options.labels   put
  %xmenu .xm_title   /txt_options     put

  /options.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update options mode.
%
% ( ) ==> ( )
%
/options.update {
  /xmenu xmenu.options def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show options menu.
%
% ( ) => ( )
%
/panel.options {
  "main" help.setcontext
  window.xmenu
  dup .xmenu xmenu.options put
  dup .xmenu.update /options.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.options.width {
  /xmenu xmenu.options def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.options.update {
  /xmenu xmenu.options def

  pmenu.panel.update
} def


