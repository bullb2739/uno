{
'target_defaults': {
  'cflags': [
    '-std=c++11',
    '-Wall',
    '-Werror',
    '-Wshadow',
    '-Wno-comment',
    '-g',
    '-rdynamic',
  ]
},
'targets': [
  {
    'target_name': 'uno',
    'type': 'executable',
    'sources': [
      'uno.cc',
      'card.cc',
      'player.cc',
    ],
  },
]
}
