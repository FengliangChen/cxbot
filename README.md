#CXBOT

## Dependency:

1.xlnt for .xlsx
[xlnt](https://github.com/tfussell/xlnt)
![xlnt](https://user-images.githubusercontent.com/1735211/29433390-f37fa28e-836c-11e7-8a60-f8df4c30b424.png)
2.libxls
[libxls](https://sourceforge.net/projects/libxls/files/)

## Build

1. build the dynamic lib for myxls.c.

```bash
gcc -dynamiclib -o libopxls.dylib -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader myxls.c
```

2. Scode set the xlnt lib and header path, add the (ibopxls.dylib) in the debug folder.



Build Path setting in Xcode.

Go to File -> Project Settings.

 $(BUILD_DIR) 