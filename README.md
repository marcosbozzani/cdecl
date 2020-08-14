# cdecl

Extracts `C declarations` using [`universal ctags`](https://ctags.io/)

[![AppVeyor](https://img.shields.io/appveyor/build/marcosbozzani/cdecl)](https://ci.appveyor.com/project/marcosbozzani/cdecl)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/marcosbozzani/cdecl)](https://github.com/marcosbozzani/cdecl/releases/latest)
[![GitHub](https://img.shields.io/github/license/marcosbozzani/cdecl)](https://github.com/marcosbozzani/cdecl/blob/master/LICENSE)

## Usage

1. build or install
2. run `cdecl file.c`

## Install

scoop: `scoop install https://github.com/marcosbozzani/cdecl/raw/master/cdecl.json`

## Build

1. install `universal ctags`
  - scoop: `scoop install universal-ctags`
  - chocolatey: `choco install universal-ctags`
  - apt: `sudo apt install universal-ctags`
  - snap: `sudo snap install universal-ctags`
  - build: `https://docs.ctags.io/en/latest/building.html`
2. clone `git clone https://github.com/marcosbozzani/cdecl.git`
3. run `make`

## Test

run `make release test` or `make debug test`
