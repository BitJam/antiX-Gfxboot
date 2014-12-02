% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Miscellaneous options menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/options_mx.setdefault {

  xmenu.options_mx .xm_current

  "options1.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /options_mx.default exch def
    0
    options_mx.data {
      .opt_mx.option get exec options_mx.default eq { exit } if
      1 add
    } forall

    dup options_mx.data length ge { pop 0 } if

  } { pop 0 } ifelse

  put

} def

/default.options_mx.data { 
  /options_mx.data [
      [ /txt_none       ""               ]
      [ "checkmd5"      "checkmd5"       ]
      [ "checkfs"       "checkfs"        ]
      [ "toram"         "toram"          ]
      [ "from=usb"      "from=usb"       ]
      [ "acpi=off"       "acpi=off"       ]
      [ "HP Laptop"     "video.use_bios_initial_backlight=0 video.brightness_switch_enabled=1" ]
  ] def
} def

/.opt_mx.label  0 def
/.opt_mx.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build options_mx list.
%
% ( ) ==> ( )
%
/options_mx.init {
  /xmenu.options_mx .xm_size array def
  /xmenu xmenu.options_mx def

  "options_mx.men" findfile dup .undef eq {
    default.options_mx.data
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

    /options_mx.len 0 def
    dup length 
    2 sub
    1 1 rot {
        over exch get "`" strstr 0 ne { /options_mx.len inc } if
    } for
    

    % Create array to hold the data
    dup length 1 sub dup
    /options_mx.data exch array def
    
    % Now have: Array, length in stack
    % The "1 add" is to skip past the title string

    1 sub
    0 1 rot {
      over over 1 add get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      options_mx.data 3 1 roll put
    } for


  } ifelse
 
  pop

  /labels.size options_mx.data length       def
  /labels.max  options_mx.data length 1 sub def

  /options_mx.labels  labels.size array def
  /options_mx.options labels.size array def


  0 1 labels.max {
    dup 
    options_mx.labels exch dup exch
    options_mx.data exch get .opt_mx.label get put
    
    options_mx.options exch dup exch
    options_mx.data exch get .opt_mx.option get put
  } for

  options_mx.setdefault
  xmenu .xm_list    options_mx.labels   put
  %xmenu .xm_title   /txt_options     put


  /options_mx.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update options_mx mode.
%
% ( ) ==> ( )
%
/options_mx.update {
  /xmenu xmenu.options_mx def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show options_mx menu.
%
% ( ) => ( )
%
/panel.options_mx {
  "main" help.setcontext
  window.xmenu
  dup .xmenu xmenu.options_mx put
  dup .xmenu.update /options_mx.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.options_mx.width {
  /xmenu xmenu.options_mx def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.options_mx.update {
  /xmenu xmenu.options_mx def

  pmenu.panel.update
} def


