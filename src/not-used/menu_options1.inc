% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Miscellaneous options menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/options1.setdefault {

  xmenu.options1 .xm_current

  "options1.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /options1.default exch def
    0
    options1.data {
      .opt1.option get exec options1.default eq { exit } if
      1 add
    } forall

    dup options1.data length ge { pop 0 } if

  } { pop 0 } ifelse

  put

} def

/default.options1.data { 
  /options1.data [
      [ /txt_none      ""               ]
      [ "checkmd5"     "checkmd5"       ]
      [ "checkfs"      "checkfs"        ]
      [ "toram"        "toram"          ]
      [ "from=usb"     "from=usb"       ]
      [ "automount"    "automount"      ]
      [ "mount=usb"    "mount=usb"      ]
      [ "mount=all"    "mount=all"      ]
      [ "nousb2"       "nousb2"         ]
      [ "acpi=off"     "acpi=off"       ]
      [ "HP Laptop"    "video.use_bios_initial_backlight=0 video.brightness_switch_enabled=1" ]
  ] def
} def

/.opt1.label  0 def
/.opt1.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build options1 list.
%
% ( ) ==> ( )
%
/options1.init {
  /xmenu.options1 .xm_size array def
  /xmenu xmenu.options1 def

  "options1.men" findfile dup .undef eq {
    default.options1.data
    xmenu .xm_title  /txt_options put
  } {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % First line in file is the title
    dup 0 get strdup xmenu .xm_title rot put

    /options1.len 0 def
    dup length 
    2 sub
    1 1 rot {
        over exch get "`" strstr 0 ne { /options1.len inc } if
    } for
    

    % Create array to hold the data
    dup length 1 sub dup
    /options1.data exch array def
    
    % Now have: Array, length in stack
    % The "1 add" is to skip past the title string

    1 sub
    0 1 rot {
      over over 1 add get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      options1.data 3 1 roll put
    } for


  } ifelse
 
  pop

  /labels.size options1.data length       def
  /labels.max  options1.data length 1 sub def

  /options1.labels  labels.size array def
  /options1.options labels.size array def


  0 1 labels.max {
    dup 
    options1.labels exch dup exch
    options1.data exch get .opt1.label get put
    
    options1.options exch dup exch
    options1.data exch get .opt1.option get put
  } for

  options1.setdefault
  xmenu .xm_list    options1.labels   put
  %xmenu .xm_title   /txt_options     put


  /options1.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update options1 mode.
%
% ( ) ==> ( )
%
/options1.update {
  /xmenu xmenu.options1 def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show options1 menu.
%
% ( ) => ( )
%
/panel.options1 {
  "main" help.setcontext
  window.xmenu
  dup .xmenu xmenu.options1 put
  dup .xmenu.update /options1.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.options1.width {
  /xmenu xmenu.options1 def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.options1.update {
  /xmenu xmenu.options1 def

  pmenu.panel.update
} def


