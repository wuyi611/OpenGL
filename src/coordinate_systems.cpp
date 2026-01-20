// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <stb/stb_image.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include <Shader.h>

// #include <iostream>

// // 函数声明
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow *window);

// // 设置
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// // 资源路径：利用 CMake 定义的宏拼接路径（确保能找到图片和着色器）
// std::string texturePath1 = std::string(PROJECT_SOURCE_DIR) + "/resources/textures/container.jpg";
// std::string texturePath2 = std::string(PROJECT_SOURCE_DIR) + "/resources/textures/awesomeface.png";
// std::string vsPath = std::string(PROJECT_SOURCE_DIR) + "/resources/shaders/6.1.coordinate_systems.vs";
// std::string fsPath = std::string(PROJECT_SOURCE_DIR) + "/resources/shaders/6.1.coordinate_systems.fs";


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
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // glad: 加载所有 OpenGL 函数指针
//     // ---------------------------------------
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     // 编译着色器程序
//     // ------------------------------------
//     Shader ourShader(vsPath.c_str(), fsPath.c_str());

//     // 设置顶点数据 (和缓冲区) 并配置顶点属性
//     // ------------------------------------------------------------------
//     float vertices[] = {
//         // 位置坐标            // 纹理坐标
//         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // 右上
//         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // 右下
//         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // 左下
//         -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // 左上
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

//     // 位置属性 (location = 0)
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // 纹理坐标属性 (location = 1)
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);


//     // 加载并创建纹理
//     // -------------------------
//     unsigned int texture1, texture2;
//     // 纹理 1 (木箱)
//     // ---------
//     glGenTextures(1, &texture1);
//     glBindTexture(GL_TEXTURE_2D, texture1);
//     // 设置纹理环绕参数
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     // 设置纹理过滤参数
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     // 加载图片，创建纹理并生成多级渐远纹理 (Mipmaps)
//     int width, height, nrChannels;
//     stbi_set_flip_vertically_on_load(true); // 告诉 stb_image.h 在加载时翻转 Y 轴（解决图片颠倒问题）
//     unsigned char *data = stbi_load(texturePath1.c_str(), &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);

//     // 纹理 2 (笑脸)
//     // ---------
//     glGenTextures(1, &texture2);
//     glBindTexture(GL_TEXTURE_2D, texture2);
//     // 设置环绕与过滤参数
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     // 加载笑脸纹理
//     data = stbi_load(texturePath2.c_str(), &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         // 注意：awesomeface.png 有透明通道(Alpha)，所以格式要设为 GL_RGBA
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);

//     // 告诉 OpenGL 每个采样器属于哪个纹理单元 (只需设置一次)
//     // -------------------------------------------------------------------------------------------
//     ourShader.use();
//     ourShader.setInt("texture1", 0);
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

//         // 在相应的纹理单元上绑定纹理
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture1);
//         glActiveTexture(GL_TEXTURE1);
//         glBindTexture(GL_TEXTURE_2D, texture2);

//         // 激活着色器
//         ourShader.use();

//         // 创建变换矩阵
//         // -----------------------------------------------------------------
//         glm::mat4 model         = glm::mat4(1.0f); // 确保初始化为单位矩阵
//         glm::mat4 view          = glm::mat4(1.0f);
//         glm::mat4 projection    = glm::mat4(1.0f);

//         // 模型变换：绕 X 轴旋转 55 度，让物体“躺下”
//         model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//         // 观察变换：将场景沿 Z 轴负方向移动（模拟摄像机后退）
//         view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//         // 投影变换：设置透视效果（视野角度 45 度，近平面 0.1，远平面 100）
//         projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

//         // 获取着色器中 Uniform 变量的位置
//         unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//         unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");

//         // 将矩阵传递到着色器中（这里展示了三种不同的传递方式）
//         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//         glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//         // 注：虽然每一帧都设置投影矩阵，但如果投影不随时间变化，放在循环外设置效率更高。
//         ourShader.setMat4("projection", projection);

//         // 绘制容器
//         glBindVertexArray(VAO);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         // glfw: 交换缓冲区并轮询 IO 事件（按键、鼠标等）
//         // -------------------------------------------------------------------------------
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // 可选：一旦资源不再使用，立即释放：
//     // ------------------------------------------------------------------------
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);

//     // glfw: 终止，清理所有分配的资源
//     // ------------------------------------------------------------------
//     glfwTerminate();
//     return 0;
// }

// // 处理所有输入：查询 GLFW 是否按下/释放了特定按键，并做出相应反应
// // ---------------------------------------------------------------------------------------------------------
// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// // 每当窗口大小改变（由操作系统或用户手动调整）时，该回调函数就会执行
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     // 确保视口匹配新的窗口尺寸
//     glViewport(0, 0, width, height);
// }
