^C==7388== 
==7388== Process terminating with default action of signal 2 (SIGINT)
==7388==    at 0x4995572: write (write.c:26)
==7388==    by 0x490C964: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1181)
==7388==    by 0x490B560: new_do_write (fileops.c:449)
==7388==    by 0x490B560: _IO_do_write@@GLIBC_2.2.5 (fileops.c:426)
==7388==    by 0x490CA9E: _IO_new_file_xsputn (fileops.c:1244)
==7388==    by 0x490CA9E: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
==7388==    by 0x48D9CB8: __printf_buffer_flush_to_file (printf_buffer_to_file.c:59)
==7388==    by 0x48D9CB8: __printf_buffer_to_file_done (printf_buffer_to_file.c:120)
==7388==    by 0x48E4732: __vfprintf_internal (vfprintf-internal.c:1545)
==7388==    by 0x48D91A2: printf (printf.c:33)
==7388==    by 0x1092BA: main (in /home/bakalem/Documents/info_systeme/Tp1/exercice2/exemple2)
==7388== 
==7388== HEAP SUMMARY:
==7388==     in use at exit: 3,660,224 bytes in 4,575 blocks
==7388==   total heap usage: 4,575 allocs, 0 frees, 3,660,224 bytes allocated
==7388== 
==7388== LEAK SUMMARY:
==7388==    definitely lost: 3,658,400 bytes in 4,573 blocks
==7388==    indirectly lost: 0 bytes in 0 blocks
==7388==      possibly lost: 0 bytes in 0 blocks
==7388==    still reachable: 1,824 bytes in 2 blocks
==7388==         suppressed: 0 bytes in 0 blocks
==7388== Rerun with --leak-check=full to see details of leaked memory
==7388== 
==7388== For lists of detected and suppressed errors, rerun with: -s
==7388== ERROR SUMMARY: 9147 errors from 2 contexts (suppressed: 0 from 0)

'''
--------------------------------------------------------------------------------
Command:            ./exemple2
Massif arguments:   (none)
ms_print arguments: massif.out.7570
--------------------------------------------------------------------------------


    MB
18.69^                                                                       :
     |                                                                    ::@:
     |                                                                ::::::@:
     |                                                             :::@:::::@:
     |                                                         :@:::::@:::::@:
     |                                                      ::::@:::::@:::::@:
     |                                                  ::@:::::@:::::@:::::@:
     |                                               :::: @:::::@:::::@:::::@:
     |                                           @::::::: @:::::@:::::@:::::@:
     |                                        :::@: ::::: @:::::@:::::@:::::@:
     |                                    :::@:::@: ::::: @:::::@:::::@:::::@:
     |                                :::::::@:::@: ::::: @:::::@:::::@:::::@:
     |                             :@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |                         ::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |                     @:::::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |                  :::@: :::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |              :@@::::@: :::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |           ::::@ ::::@: :::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |       @:::::::@ ::::@: :::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
     |    :::@: :::::@ ::::@: :::@::@::::::::@:::@: ::::: @:::::@:::::@:::::@:
   0 +----------------------------------------------------------------------->Gi
     0                                                                   5.053

Number of snapshots: 83
 Detailed snapshots: [2, 7, 14, 19, 24, 27, 36, 41, 49, 59, 69, 79]

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
  0              0                0                0             0            0
  1     65,829,836          238,584          236,224         2,360            0
  2    178,535,828          645,816          639,424         6,392            0
99.01% (639,424B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->98.85% (638,400B) 0x109201: gen_n_doubles (in /home/bakalem/Documents/info_systeme/Tp1/exercice2/exemple2)
| ->98.85% (638,400B) 0x109278: main (in /home/bakalem/Documents/info_systeme/Tp1/exercice2/exemple2)
'''
