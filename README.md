# Cobalt

This is a repository for some 3D experiments I'm working on.

## Building locally

This project is built using cmake. You can build the targets with the following commands:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

You can now execute the targets.

## Targets

### glb-info

glb-info is a tiny utility for extracting and printing GLB file contents

for more information on the glTF specification see the following references:

[glTF 2.0.0 Specification](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.pdf)

[glTF 2.0.0 Overview](https://raw.githubusercontent.com/KhronosGroup/glTF/refs/heads/main/specification/2.0/figures/gltfOverview-2.0.0d.png)

#### Usage

```
./glb-info [OPTIONS] file


POSITIONALS:
  file TEXT REQUIRED          Path to the GLB file

OPTIONS:
  -h,     --help              Print this help message and exit
  -o,     --output TEXT [default]
                              Output format (json or bin)
```

#### Common usage

1. Get an overview of GLB metadata

   ```sh
   ./glb-info path/to/file.glb
   ```

2. Output and pretty print the JSON chunk data (requires `jq`)

   ```sh
   ./glb-info path/to/file.glb -o json | jq
   ```

3. View the binary contents using `xxd`

   ```sh
   ./glb-info path/to/file.glb -o bin | xxd
   ```
