% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% timezone selection dialog.
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/timezone.getdefault {

  "timezone.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free
    dup dropwhite

    /timezone.default_val exch def

    0
    timezones {
      .tz.id get exec timezone.default_val eq { exit } if
      1 add
    } forall

    dup timezones length ge { pop 0 } if

  } { pop 0 } ifelse

} def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build menu list.
%
% ( ) ==> ( )
%
/timezone.init {
  /xmenu.timezone .xm_size array def

  /xmenu xmenu.timezone def

  xmenu .xm_list [
    timezones { .tz.name get } forall
  ] put

  xmenu .xm_title /txt_timezone put

  timezone.getdefault
    dup xmenu .xm_current rot put

    % Avoid "tz=" when "auto" is the default
    0 ne {
      timezones xmenu .xm_current get get .tz.id get settimezone
    } if

  % just once (see lang.init)
  /timezone.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update timezone selection menu.
%
% ( ) ==> ( )
%
/timezone.update {
  /xmenu xmenu.timezone def

  % avoid "tz=" here too if "auto" is selected
  xmenu .xm_current get 0 ne {
    timezones xmenu .xm_current get get .tz.id get settimezone
  }
  { /config.timezone.id .undef def }
  ifelse

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show timezone selection menu.
%
% ( ) => ( )
%
/panel.timezone {
  % "keymap" help.setcontext

  %timezone.setdefault

  window.xmenu
  dup .xmenu xmenu.timezone put
  dup .xmenu.update /timezone.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.timezone.width {
  /xmenu xmenu.timezone def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.timezone.update {
  /xmenu xmenu.timezone def

  pmenu.panel.update
} def


