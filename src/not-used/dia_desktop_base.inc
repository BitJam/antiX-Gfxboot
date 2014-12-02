% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Desktop options dialog for Base Flavour
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/desktop_base.data [
   [ "Rox-Fluxbox"   "desktop=fluxbox"        ]
   [ "Fluxbox"       "desktop=fluxbox noRox"  ]
   [ "Rox-Jwm"       "desktop=jwm"            ]
   [ "Jwm"           "desktop=jwm noRox"      ]
   [ "Dwm"           "desktop=dwm"            ]
   [ "Wmii"          "desktop=wmii"           ]
   [ /txt_cmd_line   "3 db+"                  ]
] def

  
/desktop_base.default 0 def
/.desk.label  0 def
/.desk.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/desktop_base.init {
  /xmenu.desktop_base .xm_size array def

  /xmenu xmenu.desktop_base def

  default.desktop "" eq {
    /start.index 0 def
    /bump.size   0 def
  } {
    /start.index 1 def
    /bump.size   1 def
  }
  ifelse

  /labels.max  desktop_base.data length 1 sub def

  % Don't increase size of output arrays if there is
  % a duplicate label to default.desktop
  0 1 labels.max {
      desktop_base.data exch get .desk.label get
      default.desktop eq { /bump.size 0 def } if
  } for

  /labels.size desktop_base.data length bump.size add def

  /desktop_base.labels  labels.size array def
  /desktop_base.options labels.size array def

  default.desktop "" ne {
    desktop_base.labels  0 default.desktop put
  } if

  % Copy data array into the arrays.  Offset dest by one
  % if there was a default.desktop in the gfxboot.cfg file

  0 1 labels.max {
    desktop_base.options desktop_base.labels rot
    dup start.index add dup 4 1 roll exch 
    desktop_base.data exch get dup 4 1 roll .desk.label get 
    dup default.desktop eq {
        pop pop pop pop pop
        /start.index 0 def
    } {
        put .desk.option get put
    } ifelse 

  } for

  % This clears the options for the default desktop
  desktop_base.options 0 "" put

  xmenu .xm_current desktop_base.default put
  xmenu .xm_list    desktop_base.labels  put
  xmenu .xm_title   /txt_desktop         put

  /desktop_base.init { } def

} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/desktop_base.update {
  /xmenu xmenu.desktop_base def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.desktop_base {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.desktop_base put
  dup .xmenu.update /desktop_base.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.desktop_base.width {
  /xmenu xmenu.desktop_base def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.desktop_base.update {
  /xmenu xmenu.desktop_base def

  pmenu.panel.update
} def


