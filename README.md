# radio2transistor

Convert bookmarks from desktop radio apps to Android [Transistor](https://codeberg.org/y20k/transistor) radio app via backup archive. The [URL Radio](https://github.com/jamal2362/URL-Radio) app is also supported as it is a fork of Transistor.

Currently supported:
- [Goodvibes](https://gitlab.com/GOODVIBES/GOODVIBES)
- [Radiotray-NG](https://github.com/ebruck/radiotray-ng)

## Screenshots

![Goodvibes](https://i.ibb.co/kx5wXJK/preview.png)

![Radiotray-NG](https://i.ibb.co/2gRXCKW/preview.png)


## Installation

You need to install these libraries first:
- TinyXML-2 (Debian: `libtinyxml2-dev`, Arch: `tinyxml2`)
- nlohmann/json (Debian: `nlohmann-json-dev`, Arch: `nlohmann-json`)
- CLI11 (Debian: `libcli11-dev`, Arch: `cli11`)
- Minizip (Debian: `libminizip-dev`, Arch: `minizip`)

```bash
git clone https://github.com/meequrox/radio2transistor.git

cd radio2transistor

cmake --preset=release

cmake --build --preset=release
```

The compiled files will be located in the `build/release/bin` directory.

## Usage

```bash
# Print help message
./radio2transistor -h

# Print bookmarks files paths
./radio2transistor -g

# Common use
./radio2transistor -i ~/.local/share/goodvibes/stations.xml
```

The __transistor-backup.zip__ archive will be created in the current working directory. It can be imported into Transistor via settings.

When you import any backup, it will replace your existing Transistor stations.
