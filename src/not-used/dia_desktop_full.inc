% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Desktop options dialog for Full Flavour
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/desktop_full.data [
    [ "Rox-IceWM"    "desktop=icewm"          ]
    [ "IceWM"        "desktop=icewm noRox"    ]
    [ "Rox-Fluxbox"  "desktop=fluxbox"        ]
    [ "Fluxbox"      "desktop=fluxbox noRox"  ]
    [ "Rox-Jwm"      "desktop=jwm"            ]
    [ "Jwm"          "desktop=jwm noRox"      ]
    [ "Dwm"          "desktop=dwm"            ]
    [ "Wmii"         "desktop=wmii"           ]
    [ /txt_cmd_line  "3 db+"                  ]
] def

  
/desktop_full.default 0 def
/.desk.label  0 def
/.desk.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/desktop_full.init {
  /xmenu.desktop_full .xm_size array def
  /xmenu xmenu.desktop_full def

  default.desktop "" eq {
    /start.index 0 def
    /bump.size   0 def
  } {
    /start.index 1 def
    /bump.size   1 def
  }
  ifelse

  /labels.max  desktop_full.data length 1 sub def

  % Don't increase size of output arrays if there is
  % a duplicate label to default.desktop
  0 1 labels.max {
      desktop_full.data exch get .desk.label get
      default.desktop eq { /bump.size 0 def } if
  } for

  /labels.size desktop_full.data length bump.size add def

  /desktop_full.labels  labels.size array def
  /desktop_full.options labels.size array def

  default.desktop "" ne {
    desktop_full.labels  0 default.desktop put
  } if

  % Copy data array into the arrays.  Offset dest by one
  % if there was a default.desktop in the gfxboot.cfg file

  0 1 labels.max {
    desktop_full.options desktop_full.labels rot
    dup start.index add dup 4 1 roll exch 
    desktop_full.data exch get dup 4 1 roll .desk.label get 
    dup default.desktop eq {
        pop pop pop pop pop
        /start.index 0 def
    } {
        put .desk.option get put
    } ifelse 

  } for

  % This clears the options for the default desktop
  desktop_full.options 0 "" put

  xmenu .xm_current desktop_full.default put
  xmenu .xm_list    desktop_full.labels  put
  xmenu .xm_title   /txt_desktop         put

  /desktop_full.init { } def

} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/desktop_full.update {
  /xmenu xmenu.desktop_full def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.desktop_full {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.desktop_full put
  dup .xmenu.update /desktop_full.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.desktop_full.width {
  /xmenu xmenu.desktop_full def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.desktop_full.update {
  /xmenu xmenu.desktop_full def

  pmenu.panel.update
} def


