ml /c /coff /Cp /Zi in.txt.asm
link /SUBSYSTEM:CONSOLE /ENTRY:main /DEBUG /LIBPATH:Debug in.txt.obj LIB.lib kernel32.lib libucrt.lib
