% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Miscellaneous options menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/options_ax.setdefault {

  xmenu.options_ax .xm_current

  "options1.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /options_ax.default exch def
    0
    options_ax.data {
      .opt_ax.option get exec options_ax.default eq { exit } if
      1 add
    } forall

    dup options_ax.data length ge { pop 0 } if

  } { pop 0 } ifelse

  put

} def

/default.options_ax.data { 
  /options_ax.data [
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

/.opt_ax.label  0 def
/.opt_ax.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build options_ax list.
%
% ( ) ==> ( )
%
/options_ax.init {
  /xmenu.options_ax .xm_size array def
  /xmenu xmenu.options_ax def

  "options_ax.men" findfile dup .undef eq {
    default.options_ax.data
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

    /options_ax.len 0 def
    dup length 
    2 sub
    1 1 rot {
        over exch get "`" strstr 0 ne { /options_ax.len inc } if
    } for
    

    % Create array to hold the data
    dup length 1 sub dup
    /options_ax.data exch array def
    
    % Now have: Array, length in stack
    % The "1 add" is to skip past the title string

    1 sub
    0 1 rot {
      over over 1 add get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      options_ax.data 3 1 roll put
    } for


  } ifelse
 
  pop

  /labels.size options_ax.data length       def
  /labels.max  options_ax.data length 1 sub def

  /options_ax.labels  labels.size array def
  /options_ax.options labels.size array def


  0 1 labels.max {
    dup 
    options_ax.labels exch dup exch
    options_ax.data exch get .opt_ax.label get put
    
    options_ax.options exch dup exch
    options_ax.data exch get .opt_ax.option get put
  } for

  options_ax.setdefault
  xmenu .xm_list    options_ax.labels   put
  %xmenu .xm_title   /txt_options     put


  /options_ax.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update options_ax mode.
%
% ( ) ==> ( )
%
/options_ax.update {
  /xmenu xmenu.options_ax def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show options_ax menu.
%
% ( ) => ( )
%
/panel.options_ax {
  "main" help.setcontext
  window.xmenu
  dup .xmenu xmenu.options_ax put
  dup .xmenu.update /options_ax.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.options_ax.width {
  /xmenu xmenu.options_ax def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.options_ax.update {
  /xmenu xmenu.options_ax def

  pmenu.panel.update
} def


