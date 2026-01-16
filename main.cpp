#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// 函数声明：当窗口大小改变时，回调此函数进行适配
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 函数声明：处理输入（如按键检测）
void processInput(GLFWwindow *window);

// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 顶点着色器源码
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// 片段着色器源码
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    // glfw: 初始化和配置
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    // 苹果系统需要此配置才能正常工作
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw 窗口创建
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "学习OpenGL (LearnOpenGL)", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "无法创建 GLFW 窗口" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 注册窗口大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: 加载所有 OpenGL 函数指针
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "无法初始化 GLAD" << std::endl;
        return -1;
    }


    // 构建并编译着色器程序
    // ------------------------------------

    // 1. 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 检查顶点着色器编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "错误::着色器::顶点::编译失败\n" << infoLog << std::endl;
    }

    // 2. 编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // 检查片段着色器编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "错误::着色器::片段::编译失败\n" << infoLog << std::endl;
    }

    // 3. 链接着色器
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // 检查链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "错误::着色器::程序::链接失败\n" << infoLog << std::endl;
    }
    // 链接完成后可以删除着色器对象，它们已经不再需要了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置顶点数据（及缓冲区）并配置顶点属性
    // ------------------------------------------------------------------
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f,  // 左下角
        -0.5f,  0.5f, 0.0f   // 左上角
    };
    unsigned int indices[] = {  // 注意：索引从 0 开始！
        0, 1, 3,  // 第一个三角形
        1, 2, 3   // 第二个三角形
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 1. 首先绑定 VAO
    glBindVertexArray(VAO);

    // 2. 复制顶点数组到 VBO 中供 OpenGL 使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. 复制索引数组到 EBO 中供 OpenGL 使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 注意：这是允许的。调用 glVertexAttribPointer 后，VBO 已经注册为顶点属性绑定的缓存对象，
    // 所以之后可以安全地解绑 VBO。
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 记住：当 VAO 处于激活状态时，不要解绑 EBO，因为索引缓冲对象直接存储在 VAO 中；请保持 EBO 的绑定。
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // 之后你可以解绑 VAO，这样其他的 VAO 调用就不会意外地修改这个 VAO。
    // 但这种情况很少发生。修改其他 VAO 无论如何都需要调用 glBindVertexArray，
    // 所以在没有直接必要的情况下，我们通常不解绑 VAO（也不解绑 VBO）。
    //glBindVertexArray(0);


    // 若想以线框模式绘制多边形，请取消下面代码的注释。
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 渲染循环
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 输入处理
        // -----
        processInput(window);

        // 渲染指令
        // ------
        // 设置清屏颜色（深青色）
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制我们的第一个矩形
        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO); // 既然我们只有一个 VAO，没必要每次都绑定它，但这样做可以让代码更有组织性
        //glDrawArrays(GL_TRIANGLES, 0, 6); // 如果不使用 EBO，则用此行
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 使用 EBO 进行索引绘制
        // glBindVertexArray(0); // 也没必要每次都解绑

        // glfw: 交换缓冲区并轮询 IO 事件（按键按下/释放、鼠标移动等）
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 可选：一旦这些资源超出了生命周期，就释放它们：
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: 终止，清除之前分配的所有 GLFW 资源。
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// 处理所有输入：查询 GLFW 在本帧内是否按下了特定的键，并做出相应反应
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    // 如果按下 ESC 键，则设置窗口关闭标志
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: 每当窗口大小改变（由操作系统或用户手动调整），此回调函数就会执行
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 确保视口（Viewport）匹配新的窗口尺寸；
    // 注意：在 Retina 显示器上，宽度和高度会比指定的原始尺寸显著大一些。
    glViewport(0, 0, width, height);
}
