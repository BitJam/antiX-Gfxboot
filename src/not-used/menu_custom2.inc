% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Kernel options dialog.
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%
/custom2.default 0 def

/default.custom2.data { 
  /custom2.data [
    [ "empty"            "" ]
    [ "No custom2.men!" "" ]
  ] def
} def

/.opt1.label  0 def
/.opt1.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build custom2 list.
%
% ( ) ==> ( )
%
/custom2.init {
  /xmenu.custom2 .xm_size array def
  /xmenu xmenu.custom2 def

  "custom2.men" findfile dup .undef eq {
    default.custom2.data
    xmenu .xm_title  "Custom 2" put
  } {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % First line in file is the title
    dup 0 get strdup xmenu .xm_title rot put

    /custom2.len 0 def
    dup length 
    2 sub
    1 1 rot {
        over exch get "`" strstr 0 ne { /custom2.len inc } if
    } for
    

    % Create array to hold the data
    dup length 1 sub dup
    /custom2.data exch array def
    
    % Now have: Array, length in stack
    % The "1 add" is to skip past the title string

    1 sub
    0 1 rot {
      over over 1 add get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      custom2.data 3 1 roll put
    } for


  } ifelse
 
  pop

  /labels.size custom2.data length       def
  /labels.max  custom2.data length 1 sub def

  /custom2.labels  labels.size array def
  /custom2.options labels.size array def


  0 1 labels.max {
    dup 
    custom2.labels exch dup exch
    custom2.data exch get .opt1.label get put
    
    custom2.options exch dup exch
    custom2.data exch get .opt1.option get put
  } for


  xmenu .xm_current custom2.default put
  xmenu .xm_list    custom2.labels  put
  %xmenu .xm_title   /txt_options     put


  /custom2.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update custom2 mode.
%
% ( ) ==> ( )
%
/custom2.update {
  /xmenu xmenu.custom2 def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show custom2 menu.
%
% ( ) => ( )
%
/panel.custom2 {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.custom2 put
  dup .xmenu.update /custom2.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.custom2.width {
  /xmenu xmenu.custom2 def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.custom2.update {
  /xmenu xmenu.custom2 def

  pmenu.panel.update
} def


