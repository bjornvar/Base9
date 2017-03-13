[![Build Status](https://api.travis-ci.org/youngar/Base9.svg?branch=master)](https://travis-ci.org/youngar/Base9)

Cloning
-------
To clone the source code, use:
```
git clone https://github.com/youngar/Base9
```

Building
--------
You may not need to disable warnings as errors to build.
```
make
```

To run tests, use:
```
make test
```

To run the benchmark, use:
```
make bench
```

Generate DDR structures
-----------------------
Add the following annotation to all the files that contain relevant macros and defines:
```
/*
 * @ddr_namespace: default
 */
```

Get the macros and defines using this script (the output will be written to `macroList`):
```
omr/tools/ddrgen/src/macros/getMacros.sh .
```

Compile with debug symbols (default behaviour with this makefile):
```
make b9
```

Add the object file names to a file (e.g. `objectFiles`).

Run `ddrgen`:
```
omr/ddrgen -m macroList -f objectFiles -b ddr.dat
```

Running with DDR
----------------
Place `ddr.dat` in working directory. This is where `b9` expects to find it.
Run `b9`, e.g. using `make program`. The program will hang when completed, allowing you to call `gcore`. The resulting core file contains the DDR structure blob (search for pattern "J9VMRAS").

