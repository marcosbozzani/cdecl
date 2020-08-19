# cdecl

[![AppVeyor](https://img.shields.io/appveyor/build/marcosbozzani/cdecl)](https://ci.appveyor.com/project/marcosbozzani/cdecl)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/marcosbozzani/cdecl)](https://github.com/marcosbozzani/cdecl/releases/latest)
[![GitHub](https://img.shields.io/github/license/marcosbozzani/cdecl)](https://github.com/marcosbozzani/cdecl/blob/master/LICENSE)

Extracts `C declarations` using [`universal ctags`](https://ctags.io/)

# Install

- scoop: 
  1. run `scoop bucket add marcosbozzani https://github.com/marcosbozzani/scoop`
  2. run `scoop install cdecl`

- manual:
  1. download the [latest release](https://github.com/marcosbozzani/cdecl/releases/latest)
  2. move the `cdecl.exe` to the $PATH

# Usage

- run `cdecl <file> [filter]...`
- examples: 
  - `cdecl file.c`
  - `cdecl file.c structs`
  - `cdecl file.c variables functions`
- available filters:
  - unions
  - structs
  - variables
  - functions
  - static_variables
  - static_functions

# Build

1. prerequisites: `make`, `gcc` and `universal ctags`:
   - if you use scoop: 
     - `scoop add extras` (for universal-ctags)
     - `scoop install gcc universal-ctags`
2. clone `git clone https://github.com/marcosbozzani/cdecl.git`
3. run `make`

# Test

run `make release test` or `make debug test`
