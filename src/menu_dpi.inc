% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% X windows DPI (dots per inch)
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/dpi.setdefault {

  xmenu.dpi .xm_current

  "dpi.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

  } { pop "" } ifelse
  /dpi.default exch def

  0
  dpi.data {
    .vga.option get exec dpi.default eq { exit } if
    1 add
  } forall

  dup dpi.data length ge { pop 0 } if

  put

} def

/dpi.data [
    [ "110"  "dpi=110" ]
    [ "106"  "dpi=106" ]
    [ "102"  "dpi=102" ]
    [ "100"  "dpi=100" ]
    [  "98"  "dpi=98"  ]
    [  "97"  "dpi=97"  ]
    [  "96"  ""        ]
    [  "95"  "dpi=95"  ]
    [  "94"  "dpi=94"  ]
    [  "92"  "dpi=92"  ]
    [  "90"  "dpi=90"  ]
    [  "88"  "dpi=88"  ]
    [  "86"  "dpi=86"  ]
] def

/.vga.label  0 def
/.vga.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/dpi.init {
  /xmenu.dpi .xm_size array def
  /xmenu xmenu.dpi          def

  /labels.size dpi.data length       def
  /labels.max  dpi.data length 1 sub def

  /dpi.labels  labels.size array def
  /dpi.options labels.size array def

  0 1 labels.max {
    dup
    dpi.labels exch dup exch
    dpi.data exch get .vga.label get put

    dpi.options exch dup exch
    dpi.data exch get .vga.option get put
  } for

  dpi.setdefault
  %xmenu .xm_current dpi.default put
  xmenu .xm_list dpi.labels      put
  xmenu .xm_title "DPI"          put

  /dpi.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/dpi.update {
  /xmenu xmenu.dpi def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.dpi {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.dpi put
  dup .xmenu.update /dpi.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.dpi.width {
  /xmenu xmenu.dpi def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.dpi.update {
  /xmenu xmenu.dpi def

  pmenu.panel.update
} def


