% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Save Default settings options
% (needs a fancy helper app in Linux to work)
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/gfx_save.setdefault {

  xmenu.gfx_save .xm_current

  "gfxsave.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

  } { pop "" } ifelse
  /gfx_save.default exch def

  0
  gfx_save.data {
    .gfx_save.option get exec gfx_save.default eq { exit } if
    1 add
  } forall

  dup gfx_save.data length ge { pop 0 } if

  put

} def

/gfx_save.data [
    [ /txt_off      ""               ]
    %[ /txt_menus   "gfxsave=menus"  ]
    %[ /txt_custom  "gfxsave=custom" ]
    %[ /txt_both    "gfxsave=both"   ]
    [ "save"        "gfxsave=both"   ]
    [ /txt_reset    "gfxsave=reset"  ]
] def

/.gfx_save.label  0 def
/.gfx_save.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/gfx_save.init {
  /xmenu.gfx_save .xm_size array def
  /xmenu xmenu.gfx_save def

  /labels.size gfx_save.data length       def
  /labels.max  gfx_save.data length 1 sub def

  /gfx_save.labels  labels.size array def
  /gfx_save.options labels.size array def

  0 1 labels.max {
    dup
    gfx_save.labels exch dup exch
    gfx_save.data exch get .gfx_save.label get put

    gfx_save.options exch dup exch
    gfx_save.data exch get .gfx_save.option get put
  } for

  xmenu .xm_current            0     put
  gfx_save.setdefault
  xmenu .xm_list gfx_save.labels     put
  xmenu .xm_title /txt_save          put

  /gfx_save.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/gfx_save.update {
  /xmenu xmenu.gfx_save def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.gfx_save {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.gfx_save put
  dup .xmenu.update /gfx_save.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.gfx_save.width {
  /xmenu xmenu.gfx_save def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.gfx_save.update {
  /xmenu xmenu.gfx_save def

  pmenu.panel.update
} def


