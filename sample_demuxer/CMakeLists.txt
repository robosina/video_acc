cmake_minimum_required(VERSION 3.14)

project(sample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(sample
    /home/saeed/Codes/Video_Codec_SDK/Samples/NvCodec/NvDecoder/NvDecoder.cpp
  main.cpp
)
INCLUDE_DIRECTORIES(/home/saeed/Codes/Video_Codec_SDK/Samples)
INCLUDE_DIRECTORIES(/home/saeed/Codes/Video_Codec_SDK/SamplesAppDecode)
target_include_directories(sample PUBLIC /home/saeed/Codes/Video_Codec_SDK/Samples)
target_include_directories(sample PRIVATE /home/saeed/Codes/Video_Codec_SDK/Samples/AppDecode)

INCLUDE_DIRECTORIES(/usr/local/cuda/include)
target_include_directories(sample PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(sample ${OpenCV_LIBS})
target_link_libraries(sample Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES} -lcuda
    /home/saeed/Codes/Video_Codec_SDK/Lib/linux/stubs/x86_64/libnvcuvid.so
    /home/saeed/Codes/Video_Codec_SDK/Lib/linux/stubs/x86_64/libnvidia-encode.so
)
target_link_libraries(${PROJECT_NAME}
/usr/lib/x86_64-linux-gnu/libavcodec.so
/usr/lib/x86_64-linux-gnu/libavutil.so
/usr/lib/x86_64-linux-gnu/libavformat.so
/usr/lib/x86_64-linux-gnu/libavutil.so
/usr/lib/x86_64-linux-gnu/libswscale.so
)
