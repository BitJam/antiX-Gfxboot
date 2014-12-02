% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Console (vga) resolution dialog
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%

/vga_res.setdefault {

  xmenu.vga_res .xm_current

  "vga_res.def" findfile dup .undef ne {
    % Copy raw file data into a string then free raw data
    dup dup length dup string dup cvp 4 2 roll memcpy exch free

    dup dropwhite

    /vga_res.default exch def
    0
    vga_res.data {
      .vga.option get exec vga_res.default eq { exit } if
      1 add
    } forall

    dup vga_res.data length ge { pop 0 } if
    %pop 3
  } { pop 0 } ifelse

    put

} def

/vga_res.data [
    [ /txt_default ""         ]
    [ "640×400"    "vga=803"  ]
    [ "640×480"    "vga=786"  ]
    [ "800×500"    "vga=882"  ]
    [ "800×600"    "vga=789"  ]
    [ "896×672"    "vga=818"  ]
    [ "1024×640"   "vga=877"  ]
    [ "1024×768"   "vga=792"  ]
    [ "1152×720"   "vga=872"  ]
    [ "1280×800"   "vga=864"  ]
    [ "1280×1024"  "vga=795"  ]
    [ "1400×1050"  "vga=834"  ]
    [ "1440×900"   "vga=867"  ]
    [ "1600×1200"  "vga=799"  ]
    [ "1600×1200*"  "vga=839" ]      % 839 works in VirtualBox
%    [ "8x 800x600"     "vga=893" ]
%    [ "8x 1024x768"    "vga=771" ]
%    [ "8x 1280x1024"   "vga=773" ]
%    [ "8x 1920×1200"   "vga=775" ]
] def

%   640×400    vga=803  
%   640×480    vga=786  
%   800×500    vga=882  
%   800×600    vga=789  
%   896×672    vga=818  
%   1024×640   vga=877  
%   1024×768   vga=792  
%   1152×720   vga=872  
%   1280×800   vga=864  
%   1280×1024  vga=795  
%   1400×1050  vga=834  
%   1440×900   vga=867  
%   1600×1200  vga=799  
%   1600×1200* vga=839


/.vga.label  0 def
/.vga.option 1 def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Build desktop list.
%
% ( ) ==> ( )
%
/vga_res.init {
  /xmenu.vga_res .xm_size array def
  /xmenu xmenu.vga_res          def

  /labels.size vga_res.data length       def
  /labels.max  vga_res.data length 1 sub def

  /vga_res.labels  labels.size array def
  /vga_res.options labels.size array def

  0 1 labels.max {
    dup 
    vga_res.labels exch dup exch
    vga_res.data exch get .vga.label get put
    
    vga_res.options exch dup exch
    vga_res.data exch get .vga.option get put
  } for

  vga_res.setdefault
  %xmenu .xm_current vga_res.default put
  xmenu .xm_list vga_res.labels      put
  xmenu .xm_title /txt_console       put

  /vga_res.init { } def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Update desktop mode.
%
% ( ) ==> ( )
%
/vga_res.update {
  /xmenu xmenu.vga_res def

  /window.action actRedrawPanel def
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show desktop menu.
%
% ( ) => ( )
%
/panel.vga_res {
  "main" help.setcontext

  window.xmenu
  dup .xmenu xmenu.vga_res put
  dup .xmenu.update /vga_res.update put
  dup window.init
      window.show
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Return width of panel entry.
%
% ( ) => ( width )
%
/panel.vga_res.width {
  /xmenu xmenu.vga_res def

  pmenu.width
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Redraw panel entry.
%
% ( panel ) => ( )
%
/panel.vga_res.update {
  /xmenu xmenu.vga_res def

  pmenu.panel.update
} def


