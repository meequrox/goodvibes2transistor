# radio2transistor

Convert bookmarks from desktop radio apps to Android [Transistor](https://codeberg.org/y20k/transistor) radio app via backup archive. The [URL Radio](https://github.com/jamal2362/URL-Radio) app is also supported as it is a fork of Transistor.

Currently supported:
- [Goodvibes](https://gitlab.com/goodvibes/goodvibes)
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

mkdir build && cd build

cmake ..

make
```

## Usage

```bash
# Print help message
./r2t -h

# Print bookmarks files paths
./r2t -g

# Common use
./r2t -a -i /home/$USER/.local/share/goodvibes/stations.xml
```

The __transistor_backup.zip__ archive will be created in the current working directory. It can be imported into Transistor via settings.

When you import any backup, it will replace your existing Transistor stations.

Note that without `-a` flag program will create __transistor_backup__ directory with collection files. You could probably sync the contents of _transistor_backup/_ to _/storage/emulated/0/Android/data/org.y20k.transistor/files/_, but Android usually won't let you do that ¯\\_(ツ)_/¯

## Contributing

It is easy to create reader for any app.

__\<AppName>Reader.hpp__:
```cpp
#include "BookmarksReader.hpp"

class AppNameReader : public BookmarksReader {
   private:
    // Some variables you need to parse bookmarks

   public:
    AppNameReader(const std::string& path);

    stationsList getStationsList() const override;
};
```

__\<AppName>Reader.cpp__:
```cpp
AppNameReader::AppNameReader(const std::string& path) noexcept(false) {
    if (path.substr(path.find_last_of(".")) != ".EXT")
        throw std::invalid_argument(path + " is not a EXT file.");

    // Open bookmarks file and read its contents to private class variable
}

AppNameReader::stationsList AppNameReader::getStationsList() const {
    stationsList v;

    // Add each station to vector using
    // v.push_back(std::make_pair(StationName, StationURL));

    return v;
}
```

Pull requests are welcome!
