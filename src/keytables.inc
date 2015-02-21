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

%jbb %% include ../keymaps/keymap.Pl02.inc
%jbb %% include ../keymaps/keymap.be-latin1.inc
%jbb %% include ../keymaps/keymap.br-abnt2.inc
%jbb %% include ../keymaps/keymap.cf.inc
%jbb %% include ../keymaps/keymap.cn-latin1.inc
%jbb %% include ../keymaps/keymap.croat.inc
%jbb %% include ../keymaps/keymap.cz-lat2-us.inc
%jbb %% include ../keymaps/keymap.cz-us-qwertz.inc
%jbb %% include ../keymaps/keymap.de-latin1-nodeadkeys.inc
%jbb %% include ../keymaps/keymap.dk.inc
%jbb %% include ../keymaps/keymap.dvorak.inc
%jbb %% include ../keymaps/keymap.es.inc
%jbb %% include ../keymaps/keymap.et.inc
%jbb %% include ../keymaps/keymap.fi-latin1.inc
%jbb %% include ../keymaps/keymap.fr-latin1.inc
%jbb %% include ../keymaps/keymap.fr_CH-latin1.inc
%jbb %% include ../keymaps/keymap.gr.inc
%jbb %% include ../keymaps/keymap.hu.inc
%jbb %% include ../keymaps/keymap.is-latin1.inc
%jbb %% include ../keymaps/keymap.it.inc
%jbb %% include ../keymaps/keymap.jp106.inc
%jbb %% include ../keymaps/keymap.la-latin1.inc
%jbb %% include ../keymaps/keymap.lt.baltic.inc
%jbb %% include ../keymaps/keymap.nl.inc
%jbb %% include ../keymaps/keymap.no-latin1.inc
%jbb %% include ../keymaps/keymap.pt-latin1.inc
%jbb %% include ../keymaps/keymap.ruwin_alt-UTF-8.inc
%jbb %% include ../keymaps/keymap.sg-latin1.inc
%jbb %% include ../keymaps/keymap.sk-qwerty.inc
%jbb %% include ../keymaps/keymap.sk-qwertz.inc
%jbb %% include ../keymaps/keymap.slovene.inc
%jbb %% include ../keymaps/keymap.sr-cy.inc
%jbb %% include ../keymaps/keymap.sv-latin1.inc
%jbb %% include ../keymaps/keymap.tj.inc
%jbb %% include ../keymaps/keymap.trq.inc
%jbb %% include ../keymaps/keymap.ua.inc
%jbb %% include ../keymaps/keymap.uk.inc

% array must not be empty
/keymaps [
%jbb  [ "Arabic"                  "arabic"               .undef                      ]
%jbb   [ "Belgian"                 "be"                   keymap.be-latin1            ]
%jbb   [ "Canadian (Multilingual)" "ca"                   keymap.cn-latin1            ]
%jbb   [ "Croatian"                "hr"                   keymap.croat                ]
%jbb   [ "Czech"                   "cz"                   keymap.cz-us-qwertz         ]
%jbb   [ "Danish"                  "dk"                   keymap.dk                   ]
%jbb   [ "Dutch"                   "nl"                   keymap.nl                   ]
%jbb   [ "Dvorak"                  "dvorak"               keymap.dvorak               ]
%jbb   [ "English (IE)"            "ie,gb"                keymap.uk                   ]
%jbb   [ "English (UK)"            "gb"                   keymap.uk                   ]
      [ "English (US)"            "us"                   .undef                      ]
%jbb   [ "Estonian"                "et"                   keymap.et                   ]
%jbb   [ "Finnish"                 "fi"                   keymap.fi-latin1            ]
%jbb   [ "French"                  "fr"                   keymap.fr-latin1            ]
%jbb   [ "French (Canada)"         "cf"                   keymap.cf                   ]
%jbb %  [ "French (Switzerland)"    "fr=ch"                keymap.fr_CH-latin1         ]
%jbb   [ "German"                  "de"                   keymap.de-latin1-nodeadkeys ]
%jbb %  [ "German (Switzerland)"    "de=ch"                keymap.sg-latin1            ]
%jbb   [ "Greek"                   "gr"                   keymap.gr                   ]
%jbb   [ "Hungarian"               "hu"                   keymap.hu                   ]
%jbb   [ "Icelandic"               "is"                   keymap.is-latin1            ]
%jbb   [ "Italian"                 "it"                   keymap.it                   ]
%jbb   [ "Japanese"                "jp"                   keymap.jp106                ]
%jbb %  [ "Khmer"                   "khmer"                .undef                      ]
%jbb   [ "Korean"                  "kr"                   .undef                      ]
%jbb   [ "Lithuanian"              "lt"                   keymap.lt.baltic            ]
%jbb   [ "Norwegian"               "no"                   keymap.no-latin1            ]
%jbb   [ "Polish"                  "pl"                   keymap.Pl02                 ]
%jbb   [ "Portuguese (PT)"         "pt"                   keymap.pt-latin1            ]
%jbb   [ "Portuguese (BR)"         "br"                   keymap.br-abnt2             ]
%jbb   [ "Russian"                 "ru"                   keymap.ruwin_alt-UTF-8      ]
%jbb   [ "Serbian"                 "sr"                   keymap.sr-cy                ]
%jbb   [ "Slovak"                  "sk"                   keymap.sk-qwertz            ]
%jbb %  [ "Slovak (qwerty)"         "sk=qwerty"            keymap.sk-qwerty            ]
%jbb   [ "Slovene"                 "si"                   keymap.slovene              ]
%jbb   [ "Spanish"                 "es"                   keymap.es                   ]
%jbb   [ "Spanish (Latin America)" "latem"                keymap.la-latin1            ]
%jbb   [ "Swedish"                 "se"                   keymap.sv-latin1            ]
%jbb   [ "Tajik"                   "tj"                   keymap.tj                   ]
%jbb   [ "Turkish"                 "tr"                   keymap.trq                  ]
%jbb   [ "Ukrainian"               "ua"                   keymap.ua                   ]
] def

