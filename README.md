# ModernCPlusProjectTemplate [![CMake](https://github.com/intellistream/ModernCPlusProjectTemplate/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/intellistream/ModernCPlusProjectTemplate/actions/workflows/cmake.yml)

Template for C++ 20 project; using CMAKE to manage; Enable cuda at c++11

## Requires G++11
# for ubuntu22.04 onwards, use the default gcc/g++ is ENOUGH!!
Otherwise, follow these instructions
```shell
sudo add-apt-repository 'deb http://mirrors.kernel.org/ubuntu jammy main universe'
sudo apt-get update"
sudo apt install gcc-11 g++-11"
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 11
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 11
```
# warning: don't run apt-get upgrade after you add the jammy source to an older version, it may destroy your older distribution!!!
## Requires Log4cxx
```shell
sudo apt-get install -y liblog4cxx-dev
```
## CUDACXX
Make sure you have set up CUDACXX environment. If not, try `export CUDACXX= xxx' before cmake, the xxx is usually /usr/local/cuda/bin/nvcc, but depends on your installation.
## Code Structure
- benchmark -- application code to use the generated shared library
- cmake -- cmake configuration files
- docs -- any documents
- include -- all the header files
- src -- corresponding source files, will generate a shared library
- test -- test code based on google test

## How to start?
- Please rename IntelliStream to your desired project name.
- Implement your core function code in src and include folders.
- Implement your application code in benchmark folder.
- Implement your test code in test folder.
