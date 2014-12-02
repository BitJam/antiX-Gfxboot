#!/usr/bin/perl

use strict;

use warnings;

my $out_file     = "gfxboot-indexed.html";
my $menu_file    =    "gfxboot-menu.html";
my $inframe_file = "gfxboot-inframe.html";

open my $input, "-|", "tidy -q -i -w 120 < gfxboot.html" 
    or die "Could not open tidy pipe.  $!";

my ($buffer, @head, @pre, @post, @index);
$buffer = \@head;


while (<$input>) {

    m{</head>}          and $buffer = \@pre;
    /div class="sect1"/ and $buffer = \@post;

    s{<li.*?>}{}i;
    s{</li>}{}i;
    s{<ul.*?>}{}i;
    s{</ul>}{}i;
    s{style="[^"]*"}{}i;
    m{<h[23]} and s{<a[^>]+></a>}{};


    /name="(f_\d+)"/ and do {
        my $label = $1;
        if (s{>([^<]+)<}{><a href="#index">$1</a><} ) {
            my $code = $1;
            #warn "$label $code\n";
            push @index, [ $code, $label ];
            s/<p>/<p class="function">/;
        }
        else {
            warn "Funny line: $_"
        }
    };

    push @$buffer, $_;
}

open my $out_fh, ">", $out_file or die "Could not open($out_file) $!";
print $out_fh @head;
print $out_fh style_header();
print $out_fh @pre;
print $out_fh make_index(\@index);
print $out_fh @post;
close $out_fh;


open my $inframe_fh, ">", $inframe_file or die "Could not open($menu_file) $!";
print $inframe_fh @head;
print $inframe_fh style_header();
print $inframe_fh @pre;
print $inframe_fh @post;
close $inframe_fh;

open my $menu_fh, ">", $menu_file or die "Could not open($menu_file) $!";
print $menu_fh menu_header();
print $menu_fh menu_list(\@index);
print $menu_fh menu_footer();
close $menu_fh;

exit;

#=========================================================================
sub style_header {
    
    return <<Style_Header;}
<style type="text/css">

  body {
    background-color:          #100020;
    color:                     #c0c0c0;
    margin:                        0px;
    padding:         0px 0px 0px 0.5em;
    font-family:
    'DejaVu Sans', Arial,Helvetica,sans-serif;
  }
  a { 
    color:                     #ffffff;
  }

  a:visited {
      color:                   #a0a0a0;
  }

  a:hover {
    color:                     #ffffff;
    background-color:          #4d7cbd;
  }

  code.function > a:visited {
    color:                     #ffffff;
  }

  p.function {
    border-top:      1px solid #a0a0a0;
    border-bottom:   1px solid #a0a0a0;
    padding:          3px 0px 3px .5em;
    background-color:          #1d3f6f;
  }

  .menu-item:hover {
    background-color:          #1d3f6f;
    border-top:      1px solid #a0a0a0;
    border-bottom:   1px solid #a0a0a0;

  h3.title {
    color:                     #ffffff;
    margin-top:                    1em;
    margin-bottom:                 0em;
    font-size:                   1.0em;
    border-top:      1px solid #a0a0a0;
    border-bottom:   1px solid #a0a0a0;
    background:                #1d3f6f;
    padding:         3px 3px 3px 0.5em;

  }
</style>
Style_Header

sub menu_header {
    return <<Menu_Header;}
<html>
<head>
<title>gfxboot index</title>
<style type="text/css">
  body {
    background-color:          #000000;
    color:                     #a0a0a0;
    font-family:
    'DejaVu Sans', Arial,Helvetica,sans-serif;
  }
  a { 
    color:                     #ffffff;
  }
  a:visited {
      color :                  #a0a0a0;
  }

  a:hover {
    color:                     #ffffff;
    background-color:          #4d7cbd;
  }
  div {
    border-top:      1px solid #000000;
    border-bottom:   1px solid #000000;
    padding:          0px .5em 0px 0px;
    text-align:                  right;
  }
  .menu-item:hover {
    background-color:          #1d3f6f;
    border-top:      1px solid #a0a0a0;
    border-bottom:   1px solid #a0a0a0;

    /* background-color: #4d7cbd; */
  }
</style>
</head>
<body>

Menu_Header

sub menu_footer {
    return <<Menu_Footer;}
</body>
</html>
Menu_Footer


sub make_index {
    my $index = shift;
    my @out;
    push @out, <<Header;
<div id="index">
<h2>Index</h2>
Header

    for (@$index) {
        push @out, qq{<a href="#$_->[1]">$_->[0]</a>\n};
    }
    push @out, qq{</div>\n\n};
    return @out;
}

sub menu_list {
    my $index = shift;
    my @out;
    for (@$index) {
        push @out, qq{<a href="$inframe_file#$_->[1]" target="content">},
            qq{<div class="menu-item">$_->[0]</div></a>\n};
    }
    return @out;
}

