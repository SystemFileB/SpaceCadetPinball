## mds2midi
这是一个将Full Tilt! Space Cadet的SOUND/TABA*.MDS文件转换为MIDI文件的工具

具体使用方法请通过 `mds2midi` 查看

## 编译
请先准备这些工具：
- g++ 或 clang++
- cmake 3.10及以上
- make 或 ninja

然后，生成编译配置文件：
```
mkdir build
cd build

# 以下命令三选一
# 默认编译工具
cmake ..

# 使用make
cmake -G"Unix Makefiles" ..

# 使用ninja
cmake -GNinja ..
```

编译：
```
make

# 或者
ninja
```