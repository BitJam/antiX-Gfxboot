% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Console (vga) resolution dialog
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/console.setdefault {

  xmenu.console .xm_current

  "console.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

  } { pop "" } ifelse
  /console.default exch def

  0
  console.data {
    .console.option get exec console.default eq { exit } if
    1 add
  } forall

  dup console.data length ge { pop 0 } if

  put

} def

/console.data [
    [ /txt_default       ""                ]
    [ "800×600"     "vga=788"         ]
    [ "1024×768"    "vga=791"         ]
    [ "1280×1024"   "vga=794"         ]
    [ "1366x768"    "vga=895"         ]
    [ "1600×900"    "vga=980"         ]
    [ "1600×1200"   "vga=798"         ]
    [ "1600×1200*"  "vga=839"         ]   % 839 works in VirtualBox
%    [ "new: 1024x768"    "video=1024x768"  ]
%    [ "new: 1280x1024"   "video=1280x1024" ]
%    [ "new: 1366x768"    "video=1366x768"  ]
%    [ "new: 1600x1200"   "video=1600x1200" ]
%    [ "new: 1600x900"    "video=1600x900"  ]
%    [ "new: 1440x900"    "video=1440x900"  ]
%    [ "new: 1920x1080"   "video=1920x1080" ]
] def

/.console.label  0 def
/.console.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/console.init {
  /xmenu.console .xm_size array def
  /xmenu xmenu.console          def

  /labels.size console.data length       def
  /labels.max  console.data length 1 sub def

  /console.labels  labels.size array def
  /console.options labels.size array def

  0 1 labels.max {
    dup
    console.labels exch dup exch
    console.data exch get .console.label get put

    console.options exch dup exch
    console.data exch get .console.option get put
  } for

  console.setdefault
  %xmenu .xm_current console.default put
  xmenu .xm_list console.labels     put
  xmenu .xm_title /txt_console      put

  /console.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/console.update {
  /xmenu xmenu.console def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.console {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.console put
  dup .xmenu.update /console.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.console.width {
  /xmenu xmenu.console def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.console.update {
  /xmenu xmenu.console def

  pmenu.panel.update
} def


