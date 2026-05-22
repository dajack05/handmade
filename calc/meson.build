project('calc', 'cpp', 'c')

SRCS = [
  'src/main.cpp',
  'src/Layout.cpp',
  'src/ViewFuncs.cpp',
  'src/Stats.cpp',
  'src/Calc.cpp',

  'src/util/String.cpp',

  'src/lib/stb_sprintf.c',
]

LIBS = [
  dependency('raylib'),
]

executable('calc', SRCS, dependencies: LIBS)
