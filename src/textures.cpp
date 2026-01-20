// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb/stb_image.h>

// #include <Shader.h>

// #include <iostream>

// // 函数声明
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow *window);

// // 屏幕设置
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// // 资源路径：利用 CMake 定义的宏拼接路径
// std::string texturePath1 = std::string(PROJECT_SOURCE_DIR) + "/resources/textures/container.jpg";
// std::string texturePath2 = std::string(PROJECT_SOURCE_DIR) + "/resources/textures/awesomeface.png";
// std::string vsPath = std::string(PROJECT_SOURCE_DIR) + "/resources/shaders/4.2.texture.vs";
// std::string fsPath = std::string(PROJECT_SOURCE_DIR) + "/resources/shaders/4.2.texture.fs";

// int main()
// {
//     // glfw: 初始化与配置
//     // ------------------------------
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     // glfw 窗口创建
//     // --------------------
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "学习OpenGL", NULL, NULL);
//     if (window == NULL)
//     {
//         std::cout << "无法创建 GLFW 窗口" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // glad: 加载所有 OpenGL 函数指针
//     // ---------------------------------------
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "无法初始化 GLAD" << std::endl;
//         return -1;
//     }

//     // 构建并编译着色器程序
//     // ------------------------------------
//     Shader ourShader(vsPath.c_str(), fsPath.c_str());

//     // 设置顶点数据、缓冲并配置顶点属性
//     // ------------------------------------------------------------------
//     float vertices[] = {
//         // 位置坐标            // 颜色颜色           // 纹理坐标
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 右下
//         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // 左下
//         -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // 左上
//     };
//     unsigned int indices[] = {
//         0, 1, 3, // 第一个三角形
//         1, 2, 3  // 第二个三角形
//     };
//     unsigned int VBO, VAO, EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     // 位置属性 (Location = 0)
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // 颜色属性 (Location = 1)
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
//     // 纹理坐标属性 (Location = 2)
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//     glEnableVertexAttribArray(2);


//     // 加载并创建纹理
//     // -------------------------
//     // texture1
//     unsigned int texture1;
//     glGenTextures(1, &texture1);
//     glBindTexture(GL_TEXTURE_2D, texture1); // 之后所有 GL_TEXTURE_2D 操作都将作用于此纹理对象

//     // 设置纹理环绕参数 (Wrapping)
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 横向重复
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // 纵向重复

//     // 设置纹理过滤参数 (Filtering)
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 缩小使用三线性过滤
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);               // 放大使用线性过滤

//     // 加载图片，生成纹理并生成多级渐远纹理 (Mipmaps)
//     int width, height, nrChannels;
//     stbi_set_flip_vertically_on_load(true);
//     // 加载图像数据
//     unsigned char *data = stbi_load(texturePath1.c_str(), &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         // 核心步骤：将像素数据传输给显卡
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "纹理加载失败" << std::endl;
//     }
//     stbi_image_free(data); // 释放 CPU 端的图片内存

//     // texture2
//     unsigned int texture2;
//     glGenTextures(1, &texture2);
//     glBindTexture(GL_TEXTURE_2D, texture2); // 之后所有 GL_TEXTURE_2D 操作都将作用于此纹理对象

//     // 设置纹理环绕参数 (Wrapping)
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 横向重复
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // 纵向重复

//     // 设置纹理过滤参数 (Filtering)
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 缩小使用三线性过滤
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);               // 放大使用线性过滤

//     // 加载图像数据
//     data = stbi_load(texturePath2.c_str(), &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         // 核心步骤：将像素数据传输给显卡
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "纹理加载失败" << std::endl;
//     }
//     stbi_image_free(data); // 释放 CPU 端的图片内存

//     // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//     // -------------------------------------------------------------------------------------------
//     ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
//     // either set it manually like so:
//     glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
//     // or set it via the texture class
//     ourShader.setInt("texture2", 1);


//     // 渲染循环
//     // -----------
//     while (!glfwWindowShouldClose(window))
//     {
//         // 输入处理
//         // -----
//         processInput(window);

//         // 渲染指令
//         // ------
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture1);
//         glActiveTexture(GL_TEXTURE1);
//         glBindTexture(GL_TEXTURE_2D, texture2);

//         // 绘制容器
//         ourShader.use();
//         glBindVertexArray(VAO);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         // glfw: 交换缓冲并轮询 IO 事件（按键按下/释放、鼠标移动等）
//         // -------------------------------------------------------------------------------
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // 可选：一旦资源超出生命周期，立即释放
//     // ------------------------------------------------------------------------
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);

//     // glfw: 终止，清理所有之前分配的 GLFW 资源
//     // ------------------------------------------------------------------
//     glfwTerminate();
//     return 0;
// }

// // 输入处理：询问 GLFW 本帧内是否有相关键按下或释放
// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// // 当窗口大小发生改变时（由系统或用户手动调整），此回调函数会被执行
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     // 确保视口匹配新窗口尺寸；注意在 Retina 屏幕上宽度和高度会显著大于指定的数值
//     glViewport(0, 0, width, height);
// }
