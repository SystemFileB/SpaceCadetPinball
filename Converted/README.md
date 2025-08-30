## Converted
这里存放了从Windows三维弹球和Full Tilt! Space Cadet转换后的音乐文件

包括TABA*.MDS的转换：TABA*.mid，以及游戏所有音乐的ogg转换版本

## 转换方法

### MIDI → OGG
通过VLC的媒体→转换 / 保存工具实现，我使用了GM DLS Remastered Version 2 Alt音色库，这个和Windows使用的gm.dls音色库基本一致

### SOUND/TABA*.MDS
这个格式可能是Full Tilt!的专有格式，但是上游已经有了对这种格式的支持  
我根据上游代码，写了mds2midi工具，你可以在Tools/mds2midi文件夹下编译使用

转换后会得到MIDI文件，然后在使用上面的方法来转换它

## 为什么要转换？
Emscripten的SDL不支持MIDI😅，所以需要转成其他的音频格式

alula/SpaceCadetPinball的实现策略可能是直接加入FulidSynth支持，但是音色库太大我不想要用这种方法