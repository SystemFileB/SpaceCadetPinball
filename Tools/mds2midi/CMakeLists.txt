cmake_minimum_required(VERSION 3.10)
project(mds2midi)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(mds2midi
    mds2midi.cpp
    mdsconvert.cpp
)

# 设置目标属性
set_target_properties(mds2midi PROPERTIES
    OUTPUT_NAME "mds2midi"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# 添加编译参数
set(CMAKE_CXX_FLAGS "-O2 ${CMAKE_CXX_FLAGS}")

# 在Windows环境下自动添加.exe后缀
if(WIN32)
    set_target_properties(mds2midi PROPERTIES SUFFIX ".exe")
endif()

# 安装目标（可选）
install(TARGETS mds2midi
    RUNTIME DESTINATION bin
)