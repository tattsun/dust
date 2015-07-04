## dust: An dusty C++ Library


[![Circle CI](https://circleci.com/gh/tattsun/dust.svg?style=svg)](https://circleci.com/gh/tattsun/dust)

tattsun's useless C++ library(experimental)

### Requirements

- CppUTest
    + See [install instruction](http://cpputest.github.io/).

### Build

On the dust root directory, run the following commands.

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Copy ```src/``` and ```build/src/libdust.a``` into your projects.
Then, include header files you need, link ```libdust.a``` when compiling.

### Install

On the dust root directory, run the following commands.

```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```

All headers and static library will be installed.
