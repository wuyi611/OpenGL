#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.h>

#include <iostream>

// 函数声明
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// 屏幕设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: 初始化并配置
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw 窗口创建
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "无法创建 GLFW 窗口" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
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
    Shader ourShader("shader.vs", "shader.fs");

    // 设置顶点数据 (以及缓冲区) 并配置顶点属性
    // ------------------------------------------------------------------
    float vertices[] = {
        // 位置坐标            // 颜色
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 首先绑定顶点数组对象 (VAO)，然后绑定并设置顶点缓冲区 (VBO)，最后配置顶点属性。
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 位置属性配置
    // 参数: 索引, 大小, 类型, 是否归一化, 步长, 偏移量
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性配置
    // 参数: 索引, 大小, 类型, 是否归一化, 步长, 偏移量 (颜色从第4个float开始，即偏移3个float)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 通常不需要解绑 VAO 或 VBO，除非有特殊需要。
    // glBindVertexArray(0);


    // 渲染循环
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 输入处理
        // -----
        processInput(window);

        // 渲染指令
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置清空屏幕后的背景色
        glClear(GL_COLOR_BUFFER_BIT);        // 清空颜色缓冲区

        // 绘制三角形
        ourShader.use();             // 激活着色器程序
        glBindVertexArray(VAO);      // 绑定 VAO
        glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制 3 个顶点

        // glfw: 交换缓冲区并轮询 IO 事件（按键按下/释放、鼠标移动等）
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 可选：一旦这些资源超出其生命周期，就释放它们：
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: 终止并清除之前分配的所有 GLFW 资源。
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// 处理所有输入：查询 GLFW 在本帧内是否按下了相关按键并做出相应反应
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: 每当窗口大小改变（由操作系统或用户手动调整）时，该回调函数就会执行
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 确保视口匹配新窗口尺寸；请注意，在视网膜(Retina)显示器上，
    // 宽度和高度将比指定的显著更大。
    glViewport(0, 0, width, height);
}
