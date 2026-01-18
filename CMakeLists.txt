cmake_minimum_required(VERSION 3.16)
project(OpenGL LANGUAGES CXX C) # 增加 C 语言支持，因为 glad.c 是 C 文件

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 定义源文件（包含你的代码和 GLAD 源码）
set(SOURCES
    src/main.cpp
    src/main1.cpp
    src/main2.cpp
    src/main3.cpp
    src/Shader.cpp
    include/Shader.h
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/glad.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

# 2. 头文件路径 (包含你自己和第三方库的)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
)

# 3. 库目录设置
target_link_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.4.bin.WIN64/lib-vc2019"
)

# 4. 链接库文件
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw3
    opengl32
)

# 5. 安装设置
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
