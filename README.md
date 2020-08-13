# cdecl

Extracts `C declarations` using [`universal ctags`](https://ctags.io/)

## Usage

1. install `ctags`
  - scoop: `scoop install universal-ctags`
  - chocolatey: `choco install universal-ctags`
  - apt: `sudo apt install universal-ctags`
  - snap: `sudo snap install universal-ctags`
2. build (see below)
3. add `out/bin/release` to path
4. run `cdecl file.c`


## Build

1. clone `git clone https://github.com/marcosbozzani/cdecl.git`
2. go to the workspace root
3. run `make`

## Test

1. go to the workspace root
2. run `make test`
