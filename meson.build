project('pandora', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

executable('pandora',
		   #'src/core/backend/OpenGL.cpp',
		   #'src/core/backend/SDL.cpp',
		   #'src/core/engine/Pandora.cpp',
		   #'src/main.cpp',
		   'src/OpenGL.cpp',
		   'src/Pandora.cpp',
		   link_args : ['-lGL', '-lGLEW', '-I/usr/include/SDL2', '-D_REENTRANT', '-L/usr/lib64', '-lSDL2', '-pthread'],
           install : true)
