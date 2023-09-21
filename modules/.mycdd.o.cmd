savedcmd_/home/shubham/DD/cdd_01_new_mathod/mycdd.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o /home/shubham/DD/cdd_01_new_mathod/mycdd.o @/home/shubham/DD/cdd_01_new_mathod/mycdd.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --sls --static-call --uaccess --prefix=16  --link  --module /home/shubham/DD/cdd_01_new_mathod/mycdd.o

/home/shubham/DD/cdd_01_new_mathod/mycdd.o: $(wildcard ./tools/objtool/objtool)
