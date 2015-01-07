% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% X resolution dialog
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/video_mode.setdefault {

  xmenu.video_mode .xm_current

  "vid_mode.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /video_mode.default exch def
    0
    video_mode.data {
      .xvid.option get exec video_mode.default eq { exit } if
      1 add
    } forall

    dup video_mode.data length ge { pop 0 } if

  } { pop 0 } ifelse

    put

} def

/video_mode.data [
  [ /txt_default   ""                                     ]
  [ "vesa"       "nomodeset nouveau.modeset=0 xdrvr=vesa" ]
  [ "safe"       "nomodeset nouveau.modeset=0"            ]
%  [ "auto res."    "xres=auto"                           ]
] def

% /video_mode.data [
%   [ /txt_default   ""                          ]
%   [ "safe"         "nomodeset xorgconf"        ]
%   [ "auto res."    "xres=auto"                 ]
%   [ "very safe"    "nomodeset"                 ]
% ] def


% /video_mode.data [
%   [ /txt_default   "nomodeset"                 ]
%   [ "auto res 1"   "nomodeset xorgconf"        ]
%   [ "auto res 2"   "nomodeset xres=auto"       ]
%   [ "modeset 0"    "dummy"                     ]
%   [ "modeset 1"    "xorgconf"                  ]
%   [ "modeset 2"    "xres=auto"                 ]
% ] def


%  /video_mode.data [
%      [ /txt_default   ""                       ]
%      [ "auto res 1"   "xorgconf"               ]
%      [ "auto res 2"   "xres=auto"              ]
%      [ "800x600"      "xres=800x600"           ]
%      [ "800x600*"     "xres=800x600 vga=989"   ]
%      [ "1024x600"     "xres=1024x600"          ]
%      [ "1024x768"     "xres=1024x768"          ]
%      [ "1024x768*"    "xres=1024x768 vga=792"  ]
%      [ "1152x864"     "xres=1152x864"          ]
%      [ "1200x900"     "xres=1200x900"          ]
%      [ "1280x800"     "xres=1280x800"          ]
%      [ "1280x1024"    "xres=1280x1024"         ]
%      [ "1280x1024*"   "xres=1280x1024 vga=795" ]
%      [ "1360x768"     "xres=1360x768"          ]
%      [ "1366x768"     "xres=1366x768"          ]
%      [ "1440x900"     "xres=1440x900"          ]
%      [ "1440x900*"    "xres=1440x900 vga=867"  ]
%  %   [ "1600x758"     "xres=1600x758"          ]
%  %   [ "1600x900"     "xres=1600x900"          ]
%      [ "1600x1200"    "xres=1600x1200"         ]
%      [ "1600x1200*"   "xres=1600x1200 vga=839" ]  % wikipedia says 834
%  %   [ "1680x1050"    "xres=1680x1050"         ]
%      [ "1920x1080"    "xres=1920x1080"         ]
%  ] def

/.xvid.label  0 def
/.xvid.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/video_mode.init {
  /xmenu.video_mode .xm_size array def
  /xmenu xmenu.video_mode def

  /labels.size video_mode.data length       def
  /labels.max  video_mode.data length 1 sub def

  /video_mode.labels  labels.size array def
  /video_mode.options labels.size array def

  0 1 labels.max {
    dup
    video_mode.labels exch dup exch
    video_mode.data exch get .xvid.label get put

    video_mode.options exch dup exch
    video_mode.data exch get .xvid.option get put
  } for

  video_mode.setdefault
  %xmenu .xm_current            0     put

  xmenu .xm_list video_mode.labels     put
  xmenu .xm_title /txt_video_mode    put

  /video_mode.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/video_mode.update {
  /xmenu xmenu.video_mode def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.video_mode {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.video_mode put
  dup .xmenu.update /video_mode.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.video_mode.width {
  /xmenu xmenu.video_mode def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.video_mode.update {
  /xmenu xmenu.video_mode def

  pmenu.panel.update
} def


