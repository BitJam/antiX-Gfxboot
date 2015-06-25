% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Persistence options popup menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/persist.setdefault {

  xmenu.persist .xm_current

  "persist.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

  } { pop "" } ifelse
  /persist.default exch def

  0
  persist.data {
    .persist.option get exec persist.default eq { exit } if
    1 add
  } forall

  dup persist.data length ge { pop 0 } if

  put

} def

/persist.data [
    [ "off"          ""                          ]    
    [ "frugal"       "frugal=root,home"          ]
    [ "root persist" "persist=root!,home"        ]
    [ "only root"    "persist=root!"             ]
    [ "static root"  "persist=root!,home,static" ]
    [ "home persist" "persist=home!"             ]
] def

/.persist.label  0 def
/.persist.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/persist.init {
  /xmenu.persist .xm_size array def
  /xmenu xmenu.persist          def

  "persist.men" findfile dup .undef ne {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % Create array to hold the data
    dup length dup
    /persist.data exch array def

    % Now have: Array, length in stack

    1 sub
    0 1 rot {
      over over get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      persist.data 3 1 roll put
    } for

  } if
  pop

  /labels.size persist.data length       def
  /labels.max  persist.data length 1 sub def

  /persist.labels  labels.size array def
  /persist.options labels.size array def

  0 1 labels.max {
    dup
    persist.labels exch dup exch
    persist.data exch get .persist.label get put

    persist.options exch dup exch
    persist.data exch get .persist.option get put
  } for

  persist.setdefault
  %xmenu .xm_current persist.default put
  xmenu .xm_list persist.labels      put
  xmenu .xm_title "Persist"          put

  /persist.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/persist.update {
  /xmenu xmenu.persist def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.persist {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.persist put
  dup .xmenu.update /persist.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.persist.width {
  /xmenu xmenu.persist def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.persist.update {
  /xmenu xmenu.persist def

  pmenu.panel.update
} def


