% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Console Splash plus vga resolution dialog
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/splash_vga.setdefault {

  xmenu.splash_vga .xm_current

  "splash_vga.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /splash_vga.default exch def
    0
    splash_vga.data {
      .vga.option get exec splash_vga.default eq { exit } if
      1 add
    } forall

    dup splash_vga.data length ge { pop 0 } if
    %pop 3
  } { pop 1 } ifelse

    put

} def

/splash_vga.data [
    [ "safe"        ""                   ]
    [ "default"     "splash=v"           ]
    [ "800×600"     "splash=v vga=788 "  ]
    [ "1024×768"    "splash=v vga=792"   ]
    [ "1366x768"    "splash=v vga=895"   ]
    [ "1280×1024"   "splash=v vga=795"   ]
    [ "1600×1200"   "splash=v vga=799"   ]
    [ "1600×1200*"  "splash=v vga=839"   ]      % 839 works in VirtualBox

%    [ "800×600"     "vga=788 "                ]
%    [ "1024×640"    "vga=877 video=1024x640"  ]
%    [ "1024×768"    "vga=792 video=1024x768"  ]
%    [ "1152×720"    "vga=872 video=1152x720"  ]
%    [ "1280x800"    "vga=864 video=1280x800"  ]
%    [ "1280×1024"   "vga=795 video=1280x1024" ]
%    [ "1366x768"    "vga=866 video=1366x768"  ]
%    [ "8x 800x600"     "vga=893" ]
%    [ "8x 1024x768"    "vga=771" ]
%    [ "8x 1280x1024"   "vga=773" ]
%    [ "8x 1920×1200"   "vga=775" ]
] def


%               16-bit    24-bit     32-bit
%   640×400               803
%   640×480               786
%   800×500               882
%   800×600      788      789
%   896×672               818
%   1024×640     876      877
%   1024×768     791      792        793
%   1152×720     871      872
%   1152x864    0x163?                0x164?
%   1152x864    355?                  356?
%   1280x720     891?
%   1280×800              864
%   1280×1024    794      795
%   1366x768              872??  866?
%   1400×1050    837      834?
%   1440×900     865      867
%   1600×1200    798      799
%   1600×1200*   802?        803?    vga=839


% http://ubuntuforums.org/showthread.php?t=834606
% Mode 0x0300: 640x400 (+640), 8 bits
% Mode 0x0301: 640x480 (+640), 8 bits
% Mode 0x0303: 800x600 (+800), 8 bits
% Mode 0x0305: 1024x768 (+1024), 8 bits
% Mode 0x0307: 1280x1024 (+1280), 8 bits
% Mode 0x030e: 320x200 (+640), 16 bits
% Mode 0x030f: 320x200 (+1280), 24 bits
% Mode 0x0311: 640x480 (+1280), 16 bits
% Mode 0x0312: 640x480 (+2560), 24 bits
% Mode 0x0314: 800x600 (+1600), 16 bits
% Mode 0x0315: 800x600 (+3200), 24 bits
% Mode 0x0317: 1024x768 (+2048, 16 bits
% Mode 0x0318: 1024x768 (+4096), 24 bits
% Mode 0x031a: 1280x1024 (+2560), 16 bits
% Mode 0x031b: 1280x1024 (+5120), 24 bits
% Mode 0x0330: 320x200 (+320), 8 bits
% Mode 0x0331: 320x400 (+320), 8 bits
% Mode 0x0332: 320x400 (+640), 16 bits
% Mode 0x0333: 320x400 (+1280), 24 bits
% Mode 0x0334: 320x240 (+320), 8 bits
% Mode 0x0335: 320x240 (+640), 16 bits
% Mode 0x0336: 320x240 (+1280), 24 bits
% Mode 0x033d: 640x400 (+1280), 16 bits
% Mode 0x033e: 640x400 (+2560), 24 bits
% Mode 0x0345: 1600x1200 (+1600), 8 bits
% Mode 0x0346: 1600x1200 (+3200), 16 bits
% Mode 0x0347: 1400x1050 (+1400), 8 bits
% Mode 0x0348: 1400x1050 (+2800), 16 bits
% Mode 0x0349: 1400x1050 (+5600), 24 bits
% Mode 0x034a: 1600x1200 (+6400), 24 bits
% Mode 0x0352: 2048x1536 (+8192), 24 bits
% Mode 0x0360: 1280x800 (+1280), 8 bits
% Mode 0x0361: 1280x800 (+5120), 24 bits
% Mode 0x0362: 768x480 (+768), 8 bits
% Mode 0x0364: 1440x900 (+1440), 8 bits
% Mode 0x0365: 1440x900 (+5760), 24 bits
% Mode 0x0368: 1680x1050 (+1680), 8 bits
% Mode 0x0369: 1680x1050 (+6720), 24 bits
% Mode 0x037c: 1920x1200 (+1920), 8 bits
% Mode 0x037d: 1920x1200 (+7680), 24 bits

/.vga.label  0 def
/.vga.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/splash_vga.init {
  /xmenu.splash_vga .xm_size array def
  /xmenu xmenu.splash_vga          def

  /labels.size splash_vga.data length       def
  /labels.max  splash_vga.data length 1 sub def

  /splash_vga.labels  labels.size array def
  /splash_vga.options labels.size array def

  0 1 labels.max {
    dup
    splash_vga.labels exch dup exch
    splash_vga.data exch get .vga.label get put

    splash_vga.options exch dup exch
    splash_vga.data exch get .vga.option get put
  } for

  splash_vga.setdefault
  %xmenu .xm_current splash_vga.default put
  xmenu .xm_list splash_vga.labels      put
  xmenu .xm_title /txt_console          put

  /splash_vga.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/splash_vga.update {
  /xmenu xmenu.splash_vga def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.splash_vga {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.splash_vga put
  dup .xmenu.update /splash_vga.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.splash_vga.width {
  /xmenu xmenu.splash_vga def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.splash_vga.update {
  /xmenu xmenu.splash_vga def

  pmenu.panel.update
} def


