add_library(mnlibrary
  mntest.h
  mntest.c
  types.h
  types.c
  cstring.h
  cstring.c
  mnarray.h
  mnarray.c
  mnstring.h
  mnstring.c
  mnvariant.h
  mnvariant.c
  mnfield.h
  mnfield.c
  mnfieldList.h
  mnfieldList.c
  mnlist.h
  mnlist.c
  mntree.h
  mntree.c
  )
target_include_directories(mnlibrary PUBLIC ./)
