% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Panel handling.
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/panel.clear false def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Some global vars.
%
/panel.size     { clip.size pop 48 } def
% /panel.y        { clip.size exch pop panel.size exch pop sub 12 sub } def  % offset Fn keys here
/panel.y        { clip.size exch pop panel.size exch pop sub 12 sub panel.yoffset sub } def  % offset Fn keys here
/panel.text.y	{ panel.y 5 add } def
/panel.text.Fy	0 def
/panel.font	font.normal def

/panel.expert   false def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Init panel.
%
% ( ) ==> ( )
%
/panel.init {

  /panel.back 0 panel.y moveto panel.size savescreen def

  %/config.key.F1 about.msg { "about" } { "help" } ifelse def

     
  "gfxsave.on" filesize .undef ne {
    clip.size pop 1024 eq {
        /config.key.F8 "gfx_save" def 
    } {
        clip.size pop 800 eq {
          /config.key.F7 "gfx_save" def 
        } if
    } ifelse
  } if

  % define panel layout
  /panel [

    % [ key x label show_func width_func update_func init_func ]

    config.key.F1  panel.entry dup { [ keyF1  0 "F1"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F2  panel.entry dup { [ keyF2  0 "F2"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F3  panel.entry dup { [ keyF3  0 "F3"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F4  panel.entry dup { [ keyF4  0 "F4"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F5  panel.entry dup { [ keyF5  0 "F5"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F6  panel.entry dup { [ keyF6  0 "F6"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F7  panel.entry dup { [ keyF7  0 "F7"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F8  panel.entry dup { [ keyF8  0 "F8"  5 -1 roll { } forall ] } { pop } ifelse
    config.key.F11 panel.entry dup { [ keyF11 0 "F11" 5 -1 roll { } forall ] } { pop } ifelse
    config.key.F12 panel.entry dup { [ keyF12 0 "F12" 5 -1 roll { } forall ] } { pop } ifelse

  ] def

  % initialize all
  panel { 6 get dup .undef ne { exec } { pop } ifelse } forall

  panel.show
} def

/panel.reset {
    panel.init
    /panel.clear true def
    panel.show
} def

% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Show panel.
%
% ( ) ==> ( )
%
/panel.show {
  panel.font setfont

%  panel.bg setcolor
  0 panel.y moveto

%  currentpoint
  panel.back restorescreen
%  currenttransparency
%  50 settransparency
%  panel.size fillrect
%  settransparency
%  moveto

  %-- jbb: to add select boxes around selected items at bottom of screen
  sbox.enabled panel.clear or {
    %0 15 rmoveto
    %currentpoint panel.size image
    %0 -20 neg rmoveto
    %0 15 rmoveto
    currentpoint panel.size 20 add image
    0 -5 neg rmoveto
  } if
  /panel.clear false def

%  panel.border.color setcolor
%  0 -1 rmoveto
%  0 1 clip.size pop 3 div { pop putpixel 3 0 rmoveto } for

  % don't change xmenu
  /xmenu xmenu

  /panel.x config.rtl { clip.size pop panel.xoffset sub } { panel.xoffset } ifelse def  % offset Fn keys here
  panel { dup {
    dup 1 panel.x put
    %-jbb dup 4 get exec over 2 get strsize pop add 20 add panel.x exch
    dup 4 get exec over 2 get strsize pop add panel.gap add panel.x exch
    config.rtl { sub } { add } ifelse
    /panel.x exch def
    dup 5 get exec
  } { pop } ifelse } forall

  def

} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Handle keyboard input.
%
% ( key_in ) ==> ( key_out )
%
/panel.input {
  panel { dup {
    dup 0 get 2 index eq { over panel.extra pop 3 get exec pop 0 exit } { pop } ifelse
  } { pop } ifelse } forall
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Draw panel entry label and move to text field.
%
% ( panel ) => ( )
%
/panel.text.moveto {
  /panel.tmp.x over 1 get 10 config.rtl { sub } { add } ifelse def
  /panel.tmp.F exch 2 get def

  panel.tmp.x panel.text.y panel.text.Fy add moveto
  panel.f-key.fg setcolor panel.tmp.F show.rtl
  panel.normal.fg setcolor

  6 config.rtl { neg } if panel.text.Fy neg rmoveto
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Do some extra things.
%
% ( key ) => ( key )
%
/panel.extra {
  % move down one menu entry; but only once
  % see keyDown in menu::main.input

  % only for install CDs
  config.autodown not { return } if

  % not for F1
  dup keyF1 eq { return } if

  panel.extra.fkey .undef eq
  menu.entry 0 eq
  menu.entry menu.texts length 1 sub lt
  and and {
    /panel.extra.fkey 1 def
    menu.entry false MenuSelect
    menu.visible.entries menu.entry menu.shift sub sub 1 eq {
      /menu.shift menu.shift 1 add def main.drawmenu
    } if
    /menu.entry menu.entry 1 add def
    menu.entry true MenuSelect
  } if
} def


% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
% Get panel entry definition.
%
% ( label -- array )
%
/panel.entry {
  % [ show_func width_func update_func init_func ]

  dup "help"       eq { pop [ /panel.help       /panel.help.width       /panel.help.update       .undef           ] return } if
  dup "about"      eq { pop [ /panel.about      /panel.about.width      /panel.about.update      .undef           ] return } if

  dup "lang"       eq { pop [ /panel.lang       /panel.lang.width       /panel.lang.update       /lang.init       ] return } if
  dup "video"      eq { pop [ /panel.video      /panel.video.width      /panel.video.update      /video.init      ] return } if
  dup "install"    eq { pop [ /panel.install    /panel.install.width    /panel.install.update    /install.init    ] return } if
  dup "options"    eq { pop [ /panel.options    /panel.options.width    /panel.options.update    /options.init    ] return } if
  dup "desktop"    eq { pop [ /panel.desktop    /panel.desktop.width    /panel.desktop.update    /desktop.init    ] return } if
  dup "video_mode" eq { pop [ /panel.video_mode /panel.video_mode.width /panel.video_mode.update /video_mode.init ] return } if
  dup "gfx_save"   eq { pop [ /panel.gfx_save   /panel.gfx_save.width   /panel.gfx_save.update   /gfx_save.init   ] return } if
% dup "dpi"        eq { pop [ /panel.dpi        /panel.dpi.width        /panel.dpi.update        /dpi.init        ] return } if
% dup "vga_res"    eq { pop [ /panel.vga_res    /panel.vga_res.width    /panel.vga_res.update    /vga_res.init    ] return } if
% dup "splash_vga" eq { pop [ /panel.splash_vga /panel.splash_vga.width /panel.splash_vga.update /splash_vga.init ] return } if
% dup "splash"     eq { pop [ /panel.splash     /panel.splash.width     /panel.splash.update     /splash.init     ] return } if
  dup "console"    eq { pop [ /panel.console    /panel.console.width    /panel.console.update    /console.init    ] return } if
  dup "keymap"     eq { pop [ /panel.keymap     /panel.keymap.width     /panel.keymap.update     /keymap.init     ] return } if
  dup "timezone"   eq { pop [ /panel.timezone   /panel.timezone.width   /panel.timezone.update   /timezone.init   ] return } if

  dup "bits"       eq { pop
    .undef
    32+64bit_source {
      64bit {
        32bit_boot_dir .undef ne
        64bit_boot_dir .undef ne
        32bit_boot_dir 64bit_boot_dir ne
        and and {
          pop [ /panel.bits /panel.bits.width /panel.bits.update /bits.init ]
        } if
      } if
    } if

    return
  } if

  dup "restore"    eq { pop
    .undef
    config.restore.id .undef ne {
      pop [ /panel.restore /panel.restore.width /panel.restore.update .undef ]
    } if

    return
  } if

  pop .undef
} def


