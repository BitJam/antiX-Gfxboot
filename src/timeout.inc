%
% include before common.inc
%

/timeout.firsttime true def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Boot timeout counter.
%
% ( timeout time ) ==> ( )
%
% timeout: total time in 18.2Hz steps, time: current value.
%
% The code below assumes we're showing seconds and some symbolic counter.
%
/Timeout {
  % first time

  timeout.disabled { pop pop return } if

  timeout.current .undef eq { over timeout.init } if

  %-ppp ptheme { over over p.timeout.animate } if

  % no counter
  timeout.steps .undef eq { return } if
  timeout.icons 1 lt     { return } if

  /timeout.s.last timeout.s.current def
  /timeout.s.current over 10 mul 150 add 182 div def

  /timeout.last timeout.current def
  over sub neg timeout.steps mul exch div
  /timeout.current exch def

  timeout.current timeout.steps ge {
    % last run
    timeout.s.done
    timeout.done
  } {
    % 0 270 moveto timeout.last print "<" print timeout.current print "<" print

    timeout.s.last timeout.s.current ne { timeout.s.current timeout.s.update } if

    timeout.last timeout.current ne {
      timeout.last 1 add 1 timeout.current { timeout.update } for
    } if

  } ifelse
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Initialize timeout indicator.
%
% ( time ) ==> ( )
%
/timeout.init {
  "timer_a.jpg" findfile /timeout.file over def dup .undef ne {
    currentimage exch setimage
    0 0 image.size unpackimage /timeout.image exch def
    setimage

    /timeout.width timeout.image imgsize exch pop def
    /timeout.tot_width timeout.image imgsize pop def

    config.rtl { /timeout.leftside timeout.leftside not def } if

    % reduce number of timer icons to fit in space provided
    % get width of area where icons go
    timeout.leftside {
      screen.size pop timeout.margin sub
      %menu.start.x menu.bar.width add sub
      menu.start.x sub
    } {
      screen.size pop timeout.margin sub
      menu.start.x menu.bar.width add sub
    } ifelse

    % number of timers that will fit
    timeout.width timeout.gap add div
    dup 10 gt { pop 10 } if           % 12+ causes freeze
    dup timeout.icons lt {
      /timeout.icons exch def
      pop
    } { pop pop } ifelse

    timeout.icons 1 lt { return } if

    /timeout.framesteps timeout.image imgsize div def
    /timeout.steps timeout.framesteps timeout.icons mul def

    % Start timer with a small gap away from menu bar
    % gap is 20% of icon width plus 2
    timeout.leftside {
      /timeout.x menu.start.x
        timeout.width 5 div sub
        timeout.width timeout.gap add timeout.icons mul sub def
    } {
      /timeout.x menu.start.x menu.bar.width add
        timeout.width 5 div add 2 add def
    } ifelse

    /timeout.y menu.start.y 2 sub menu.entry menu.item.height mul add
      timeout.width menu.item.height sub 2 div sub def

    /timeout.current 0 def

    % What follows is expensive so make sure we only do it once
    timeout.firsttime not { return } if
    /timeout.firsttime false def

    0
    /timeout.bg_imgs    timeout.icons array def
    /timeout.img_bufs   timeout.icons array def
    /timeout.alpha_bufs timeout.icons array def

    0 1 timeout.icons 1 sub {

      % Grab background image for each timer icon
      dup timeout.bg.moveto

      dup timeout.img_bufs   exch timeout.width dup savescreen put
      dup timeout.alpha_bufs exch timeout.width dup savescreen put
      dup timeout.bg_imgs    exch timeout.width dup savescreen put

      % Blend in first frame and display them
      0 timeout.frame.moveto
        timeout.blend

    } for

  } { pop } ifelse

  /timeout.s.buf 64 string def
  /timeout.s.x 100 def
  /timeout.s.y 250 def
  /timeout.s.current -1 def

  pop
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update timeout indicator.
%
% ( step ) ==> ( )
%
% step runs from 0 to timeout.steps - 1. It is guaranteed that index is
% 1 larger than the last index. Never a step twice and no step is left out.
%
/timeout.update {
  dup timeout.frame.moveto

  % Index which goes from 0 to timeout.icons - 1
  timeout.framesteps div

  timeout.blend

} def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
%  Use index to select position and bg image and then
%  Blend in icon image and display it
%
%  (index) ==> ()

/timeout.blend {
  dup timeout.alpha_bufs exch get
  timeout.image 255 rot blend

  dup dup timeout.img_bufs exch get
  timeout.bg_imgs rot get dup length memcpy

  0 0 moveto
  timeout.fg over
  dup timeout.alpha_bufs exch get
      timeout.img_bufs rot get blend

  dup timeout.bg.moveto
      timeout.img_bufs exch get restorescreen
} def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
%  Perform moveto to position of timer icon associated with this step
%
%  (step) ==> ()
%

/timeout.bg.moveto {
  config.rtl {
    1 add timeout.width timeout.gap add mul
    timeout.width timeout.gap add timeout.icons mul sub neg
    main.rtl.xoff add
  } {
    timeout.width timeout.gap add mul
  } ifelse

  timeout.x add timeout.y moveto
} def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Perform moveto to select icon animation frame for this step
%
%  (step) ==> ()
%
/timeout.frame.moveto {
  timeout.framesteps mod
  timeout.revframes { timeout.framesteps exch sub 1 sub } if
  timeout.framesteps mod
  timeout.width mul
  0 moveto
} def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Clear timeout indicator.
%
% ( ) ==> ( )
%
/timeout.done {

  timeout.icons 1 lt { return } if

  0 1 timeout.icons 1 sub {

    dup timeout.bg_imgs exch get
    timeout.test not {
      over timeout.bg.moveto
      dup restorescreen
    } if free

    dup timeout.img_bufs   exch get free
        timeout.alpha_bufs exch get free
  } for

  timeout.bg_imgs    free
  timeout.img_bufs   free
  timeout.alpha_bufs free
  /timeout.image timeout.image free .undef def
  /timeout.file timeout.file free .undef def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update seconds counter.
%
% ( time_in_s ) ==> ( )
%
/timeout.s.update {
%  white setcolor
%  timeout.s.x timeout.s.y moveto -30 0 rmoveto
%  currentpoint 30 fontheight image
%  "%ds" timeout.s.buf sprintf
%  timeout.s.x timeout.s.y moveto timeout.s.buf showright
  pop
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Clear seconds counter.
%
% ( ) ==> ( )
%
/timeout.s.done {
%  timeout.s.x timeout.s.y moveto -30 0 rmoveto
%  currentpoint 30 fontheight image
} def


