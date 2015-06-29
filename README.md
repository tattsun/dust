## dust: An dusty C++ Library

tattsun's useless C++ library

### Requirements

- CppUTest
    + See [install instruction](http://cpputest.github.io/).

### Install

On the dust root directory, run the following commands.
 
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Copy ```src/``` and ```build/src/libdust.a``` into your projects.
Then, include header files you need, link ```libdust.a``` when compiling. 

### Install as a shared library

On the dust root directory, run the following commands.

```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```

All headers and shared library will be installed.