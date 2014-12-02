% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Console Splash only dialog
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/splash.setdefault {

  xmenu.splash .xm_current

  "splash.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /splash.default exch def
    0
    splash.data {
      .vga.option get exec splash.default eq { exit } if
      1 add
    } forall

    dup splash.data length ge { pop 0 } if
    %pop 3
  } { pop 1 } ifelse

    put

} def

/splash.data [
    [ "none"        ""         ]
    [ "S:800×600"   "vga=788 splash=v" ]
    [ "S:1024×768"  "vga=792 splash=v" ]
    [ "S:1280×1024" "vga=795 splash=v" ]
    [ "S:1600×1200" "vga=839 splash=v" ]
] def

/.vga.label  0 def
/.vga.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/splash.init {
  /xmenu.splash .xm_size array def
  /xmenu xmenu.splash          def

  /labels.size splash.data length       def
  /labels.max  splash.data length 1 sub def

  /splash.labels  labels.size array def
  /splash.options labels.size array def

  0 1 labels.max {
    dup 
    splash.labels exch dup exch
    splash.data exch get .vga.label get put
    
    splash.options exch dup exch
    splash.data exch get .vga.option get put
  } for

  splash.setdefault
  %xmenu .xm_current splash.default put
  xmenu .xm_list splash.labels      put
  xmenu .xm_title "Splash"          put

  /splash.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/splash.update {
  /xmenu xmenu.splash def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.splash {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.splash put
  dup .xmenu.update /splash.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.splash.width {
  /xmenu xmenu.splash def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.splash.update {
  /xmenu xmenu.splash def

  pmenu.panel.update
} def


