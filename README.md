# RayTracing-CEP2021
A course project for Cpp Engineering Practice Course at ZJU.

## compile:

- debug

```bash
cmake . -G "Visual Studio 16" -DCMAKE_BUILD_TYPE=Debug -Bbuild
msbuild /m /p:Configuration=Debug ./build/RayTracing.sln
```

- release

```bash
cmake . -G "Visual Studio 16" -DCMAKE_BUILD_TYPE=Release -Bbuild
msbuild /m /p:Configuration=Release ./build/RayTracing.sln
```

