#include "mds2midi_deps.hpp"
#include "mdsconvert.hpp"


int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        printf("mds2midi v1.00, Full Tilt! MDS文件转换器\n");
        printf("By SystemFileB and contributors\n\n");
        printf("用法: mds2midi <INPUT.mds> <OUTPUT.mid>\n\n");
        printf("INPUT       来自Full Tilt! Space Cadet的SOUND/TABA*.MDS文件\n");
        printf("OUTPUT      输出的MIDI文件\n\n");
        printf("Full Tilt! 来自Cinematronics和Maxis\n");
        return 1;
    }

    auto midiData = midi::MdsToMidi(argv[1]);
    if (!midiData) {
        printf("转换失败：文件格式错误或读取失败\n");
        return 2;
    }

    std::ofstream outFile(argv[2], std::ios::binary);
    if (!outFile) {
        printf("无法创建输出文件\n");
        return 3;
    }

    outFile.write(reinterpret_cast<char*>(midiData->data()), midiData->size());
    printf("成功生成MIDI文件，大小：%zu字节\n", midiData->size());
    delete midiData;
    return 0;
}