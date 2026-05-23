project('calc', 'cpp', 'c')

cmake = import('cmake')

SRCS = [
  'src/main.cpp',
  'src/Layout.cpp',
  'src/ViewFuncs.cpp',
  'src/Stats.cpp',
  'src/Calc.cpp',

  'src/util/String.cpp',

  'lib/stb/stb_sprintf.c',
]

raylib_sub = cmake.subproject('raylib')
raylib_dep = raylib_sub.dependency('raylib')

cocoa_dep = dependency('cocoa', required: true)
iokit_dep = dependency('iokit', required: true)

LIBS = [
  raylib_dep,
  cocoa_dep,
  iokit_dep,
]

# add_project_link_arguments('-framework Cocoa', language: ['c', 'cpp'])

executable('calc', SRCS, dependencies: LIBS)
