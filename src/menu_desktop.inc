% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Desktop options dialog for Base Flavour
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%
/desktop.getdefault {

  xmenu.desktop .xm_current

  "desktop.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /desktop.default_val exch def

    0
    desktop.data {
      .desktop.option get exec desktop.default_val eq { exit } if
      1 add
    } forall

    dup desktop.data length ge { pop 0 } if

  } { pop 0 } ifelse

} def

/desktop.data [
   [ "default"          ""                      ]
   [ "Rox-Fluxbox"      "desktop=rox-fluxbox"   ]
   [ "Space-Fluxbox"    "desktop=space-fluxbox" ]
   [ "Fluxbox"          "desktop=fluxbox"       ]
   [ "Rox-Jwm"          "desktop=rox-jwm"       ]
   [ "Space-Jwm"        "desktop=space-jwm"     ]
   [ "Jwm"              "desktop=jwm"           ]
   [ "min-Fluxbox"      "desktop=min-fluxbox"   ]
   [ "min-Jwm"          "desktop=min-jwm"       ]
   [ "Dark theme"       "desktheme=dark"        ]
   [ "Light theme"      "desktheme=light"       ]
] def

/desktop.default 0 def
/.desktop.label  0 def
/.desktop.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/desktop.init {
  /xmenu.desktop .xm_size array def
  /xmenu xmenu.desktop def

  "desktop.men" findfile dup .undef ne {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % Create array to hold the data
    dup length dup
    /desktop.data exch array def

    % Now have: Array, length in stack

    1 sub
    0 1 rot {
      over over get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      desktop.data 3 1 roll put
    } for

  } if
  pop

  "desktop.top" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    /default.desktop exch def
  } if

  default.desktop .undef eq {
    /start.index 0 def
    /bump.size   0 def
  } {
    /start.index 1 def
    /bump.size   1 def
  }
  ifelse

  /labels.max  desktop.data length 1 sub def

  % Don't increase size of output arrays if there is
  % a duplicate label to default.desktop
  0 1 labels.max {
      desktop.data exch get .desktop.label get
      default.desktop eq { /bump.size 0 def } if
  } for

  /labels.size desktop.data length bump.size add def

  /desktop.labels  labels.size array def
  /desktop.options labels.size array def

  default.desktop .undef ne {
    desktop.labels  0 default.desktop put
  } if

  % Copy data array into the arrays.  Offset dest by one
  % if there was a default.desktop in the gfxboot.cfg file

  0 1 labels.max {
    desktop.options desktop.labels rot
    dup start.index add dup 4 1 roll exch
    desktop.data exch get dup 4 1 roll .desktop.label get
    dup default.desktop eq {
        pop pop pop pop pop
        /start.index 0 def
    } {
        put .desktop.option get put
    } ifelse

  } for

  % This clears the options for the default desktop
  desktop.options 0 "" put

  desktop.getdefault
  %xmenu .xm_current desktop.default put
  xmenu .xm_current rot put
  xmenu .xm_list    desktop.labels  put
  xmenu .xm_title   /txt_desktop    put

  /desktop.init { } def

} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/desktop.update {
  /xmenu xmenu.desktop def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.desktop {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.desktop put
  dup .xmenu.update /desktop.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.desktop.width {
  /xmenu xmenu.desktop def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.desktop.update {
  /xmenu xmenu.desktop def

  pmenu.panel.update
} def


