## mds2midi
这是一个将Full Tilt! Space Cadet的SOUND/TABA*.MDS文件转换为MIDI文件的工具

具体使用方法请通过直接运行 `mds2midi` 查看

## 编译
请先准备这些工具：
- g++ 或 clang++
- cmake 3.10及以上
- make 或 ninja

然后，生成编译配置文件：
```bash
mkdir build
cd build

cmake ..
```

编译：
```bash
make
```

如果你在`cmake`命令中加入了`-GNinja`，你需要使用`ninja`来编译