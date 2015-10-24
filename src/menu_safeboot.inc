% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Safe Video and Failsafe-mode popup menu
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/safeboot.setdefault {

  xmenu.safeboot .xm_current

  "safeboot.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

  } { pop "" } ifelse
  /safeboot.default exch def

  0
  safeboot.data {
    .safeboot.option get exec safeboot.default eq { exit } if
    1 add
  } forall

  dup safeboot.data length ge { pop 0 } if

  put

} def

/safeboot.data [
    [ "default"     ""                         ]
    [ "Safe Video"  "nomodeset xorg=safe"      ]
    [ "Failsafe"    "nomodeset failsafe"       ]
    [ "load=all"    "load=all"                 ]

] def

/.safeboot.label  0 def
/.safeboot.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/safeboot.init {
  /xmenu.safeboot .xm_size array def
  /xmenu xmenu.safeboot          def

  "safeboot.men" findfile dup .undef ne {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % Create array to hold the data
    dup length dup
    /safeboot.data exch array def

    % Now have: Array, length in stack

    1 sub
    0 1 rot {
      over over get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      safeboot.data 3 1 roll put
    } for

  } if
  pop

  /labels.size safeboot.data length       def
  /labels.max  safeboot.data length 1 sub def

  /safeboot.labels  labels.size array def
  /safeboot.options labels.size array def

  0 1 labels.max {
    dup
    safeboot.labels exch dup exch
    safeboot.data exch get .safeboot.label get put

    safeboot.options exch dup exch
    safeboot.data exch get .safeboot.option get put
  } for

  safeboot.setdefault
  %xmenu .xm_current safeboot.default put
  xmenu .xm_list safeboot.labels      put
  xmenu .xm_title "Failsafe"          put

  /safeboot.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/safeboot.update {
  /xmenu xmenu.safeboot def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.safeboot {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.safeboot put
  dup .xmenu.update /safeboot.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.safeboot.width {
  /xmenu xmenu.safeboot def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.safeboot.update {
  /xmenu xmenu.safeboot def

  pmenu.panel.update
} def


