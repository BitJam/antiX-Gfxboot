% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Kernel options dialog.
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%
/custom1.default 0 def

/default.custom1.data { 
  /custom1.data [
    [ "empty"           "" ]
    [ "No custom1.men!" "" ]
  ] def
} def

/.opt1.label  0 def
/.opt1.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build custom1 list.
%
% ( ) ==> ( )
%
/custom1.init {
  /xmenu.custom1 .xm_size array def
  /xmenu xmenu.custom1 def

  "custom1.men" findfile dup .undef eq {
    default.custom1.data
    xmenu .xm_title  "Custom 1" put
  } {

    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    % remove trailing spaces and newlines
    dup dropwhite

    % Convert to an array of strings
    '\n' split

    % First line in file is the title
    dup 0 get strdup xmenu .xm_title rot put

    /custom1.len 0 def
    dup length 
    2 sub
    1 1 rot {
        over exch get "`" strstr 0 ne { /custom1.len inc } if
    } for
    

    % Create array to hold the data
    dup length 1 sub dup
    /custom1.data exch array def
    
    % Now have: Array, length in stack
    % The "1 add" is to skip past the title string

    1 sub
    0 1 rot {
      over over 1 add get strdup '`' split
      dup 0 get dropspaces
      dup 1 get dropspaces
      custom1.data 3 1 roll put
    } for


  } ifelse
 
  pop

  /labels.size custom1.data length       def
  /labels.max  custom1.data length 1 sub def

  /custom1.labels  labels.size array def
  /custom1.options labels.size array def


  0 1 labels.max {
    dup 
    custom1.labels exch dup exch
    custom1.data exch get .opt1.label get put
    
    custom1.options exch dup exch
    custom1.data exch get .opt1.option get put
  } for


  xmenu .xm_current custom1.default put
  xmenu .xm_list    custom1.labels  put
  %xmenu .xm_title   /txt_options     put


  /custom1.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update custom1 mode.
%
% ( ) ==> ( )
%
/custom1.update {
  /xmenu xmenu.custom1 def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show custom1 menu.
%
% ( ) => ( )
%
/panel.custom1 {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.custom1 put
  dup .xmenu.update /custom1.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.custom1.width {
  /xmenu xmenu.custom1 def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.custom1.update {
  /xmenu xmenu.custom1 def

  pmenu.panel.update
} def


