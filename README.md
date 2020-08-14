# cdecl

[![AppVeyor](https://img.shields.io/appveyor/build/marcosbozzani/cdecl)](https://ci.appveyor.com/project/marcosbozzani/cdecl)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/marcosbozzani/cdecl)](https://github.com/marcosbozzani/cdecl/releases/latest)
[![GitHub](https://img.shields.io/github/license/marcosbozzani/cdecl)](https://github.com/marcosbozzani/cdecl/blob/master/LICENSE)

Extracts `C declarations` using [`universal ctags`](https://ctags.io/)

# Install

- scoop: 
  1. run `scoop bucket add extras`
  2. run `scoop install https://github.com/marcosbozzani/cdecl/raw/master/cdecl.json`

- manual:
  1. download the [latest release](https://github.com/marcosbozzani/cdecl/releases/latest)
  2. move the `cdecl.exe` to the $PATH

# Usage

- run `cdecl <file> [filter]...`
- exeamples: 
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

1. install or build `universal ctags`:
   - scoop: `scoop install universal-ctags`
   - chocolatey: `choco install universal-ctags`
   - apt: `sudo apt install universal-ctags`
   - snap: `sudo snap install universal-ctags`
   - build: `https://docs.ctags.io/en/latest/building.html`
2. clone `git clone https://github.com/marcosbozzani/cdecl.git`
3. run `make`

# Test

run `make release test` or `make debug test`
