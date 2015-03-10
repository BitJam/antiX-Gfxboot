% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
%
% Keyboard mappings.
%
% - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


% keymap layout (diff to us map):
%
% key_code, plain, shift, altgr
%

/.km.name   0 def
/.km.id     1 def
/.km.map    2 def

%% include ../keymaps/keymap.Pl02.inc
%% include ../keymaps/keymap.be-latin1.inc
%% include ../keymaps/keymap.br-abnt2.inc
%% include ../keymaps/keymap.cf.inc
%% include ../keymaps/keymap.cn-latin1.inc
%% include ../keymaps/keymap.croat.inc
%% include ../keymaps/keymap.cz-lat2-us.inc
%% include ../keymaps/keymap.cz-us-qwertz.inc
%% include ../keymaps/keymap.de-latin1-nodeadkeys.inc
%% include ../keymaps/keymap.dk.inc
%% include ../keymaps/keymap.dvorak.inc
%% include ../keymaps/keymap.es.inc
%% include ../keymaps/keymap.et.inc
%% include ../keymaps/keymap.fi-latin1.inc
%% include ../keymaps/keymap.fr-latin1.inc
%% include ../keymaps/keymap.fr_CH-latin1.inc
%% include ../keymaps/keymap.gr.inc
%% include ../keymaps/keymap.hu.inc
%% include ../keymaps/keymap.is-latin1.inc
%% include ../keymaps/keymap.it.inc
%% include ../keymaps/keymap.jp106.inc
%% include ../keymaps/keymap.la-latin1.inc
%% include ../keymaps/keymap.lt.baltic.inc
%% include ../keymaps/keymap.nl.inc
%% include ../keymaps/keymap.no-latin1.inc
%% include ../keymaps/keymap.pt-latin1.inc
%% include ../keymaps/keymap.ruwin_alt-UTF-8.inc
%% include ../keymaps/keymap.sg-latin1.inc
%% include ../keymaps/keymap.sk-qwerty.inc
%% include ../keymaps/keymap.sk-qwertz.inc
%% include ../keymaps/keymap.slovene.inc
%% include ../keymaps/keymap.sr-cy.inc
%% include ../keymaps/keymap.sv-latin1.inc
%% include ../keymaps/keymap.tj.inc
%% include ../keymaps/keymap.trq.inc
%% include ../keymaps/keymap.ua.inc
%% include ../keymaps/keymap.uk.inc

% array must not be empty
/keymaps [
 [ "Arabic"                  "arabic"               .undef                      ]
  [ "Belgian"                 "be"                   keymap.be-latin1            ]
  [ "Canadian (Multilingual)" "ca"                   keymap.cn-latin1            ]
  [ "Croatian"                "hr"                   keymap.croat                ]
  [ "Czech"                   "cz"                   keymap.cz-us-qwertz         ]
  [ "Danish"                  "dk"                   keymap.dk                   ]
  [ "Dutch"                   "nl"                   keymap.nl                   ]
  [ "Dvorak"                  "dvorak"               keymap.dvorak               ]
  [ "English (IE)"            "ie,gb"                keymap.uk                   ]
  [ "English (UK)"            "gb"                   keymap.uk                   ]
  [ "English (US)"            "us"                   .undef                      ]
  [ "Estonian"                "et"                   keymap.et                   ]
  [ "Finnish"                 "fi"                   keymap.fi-latin1            ]
  [ "French"                  "fr"                   keymap.fr-latin1            ]
  [ "French (Canada)"         "cf"                   keymap.cf                   ]
%  [ "French (Switzerland)"    "fr=ch"                keymap.fr_CH-latin1         ]
  [ "German"                  "de"                   keymap.de-latin1-nodeadkeys ]
%  [ "German (Switzerland)"    "de=ch"                keymap.sg-latin1            ]
  [ "Greek"                   "gr"                   keymap.gr                   ]
  [ "Hungarian"               "hu"                   keymap.hu                   ]
  [ "Icelandic"               "is"                   keymap.is-latin1            ]
  [ "Italian"                 "it"                   keymap.it                   ]
  [ "Japanese"                "jp"                   keymap.jp106                ]
%  [ "Khmer"                   "khmer"                .undef                      ]
  [ "Korean"                  "kr"                   .undef                      ]
  [ "Lithuanian"              "lt"                   keymap.lt.baltic            ]
  [ "Norwegian"               "no"                   keymap.no-latin1            ]
  [ "Polish"                  "pl"                   keymap.Pl02                 ]
  [ "Portuguese (PT)"         "pt"                   keymap.pt-latin1            ]
  [ "Portuguese (BR)"         "br"                   keymap.br-abnt2             ]
  [ "Russian"                 "ru"                   keymap.ruwin_alt-UTF-8      ]
  [ "Serbian"                 "sr"                   keymap.sr-cy                ]
  [ "Slovak"                  "sk"                   keymap.sk-qwertz            ]
%  [ "Slovak (qwerty)"         "sk=qwerty"            keymap.sk-qwerty            ]
  [ "Slovene"                 "si"                   keymap.slovene              ]
  [ "Spanish"                 "es"                   keymap.es                   ]
  [ "Spanish (Latin America)" "latem"                keymap.la-latin1            ]
  [ "Swedish"                 "se"                   keymap.sv-latin1            ]
  [ "Tajik"                   "tj"                   keymap.tj                   ]
  [ "Turkish"                 "tr"                   keymap.trq                  ]
  [ "Ukrainian"               "ua"                   keymap.ua                   ]
] def

