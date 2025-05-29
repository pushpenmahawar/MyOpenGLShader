#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "JNI", __VA_ARGS__)

const char *vertexShaderCode = R"(
    attribute vec4 vPosition;
    void main() {
        gl_Position = vPosition;
    }
)";

const char *fragmentShaderCode = R"(
    precision mediump float;
    void main() {
        gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

GLuint program;
GLuint vbo;

GLuint loadShader(GLenum type, const char *code) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    return shader;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_pushpen_myopenglshader_renderer_MyRenderer_nativeInit(JNIEnv
*, jobject) {
GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderCode);
GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

program = glCreateProgram();
glAttachShader(program, vertexShader
);
glAttachShader(program, fragmentShader
);
glLinkProgram(program);

float triangle[] = {
        0.0f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
};

glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo
);
glBufferData(GL_ARRAY_BUFFER,
sizeof(triangle), triangle, GL_STATIC_DRAW);

LOGI("OpenGL initialized");
}

//com.pushpen.myopenglshader.renderer
extern "C"
JNIEXPORT void JNICALL
Java_com_pushpen_myopenglshader_renderer_MyRenderer_nativeRender(JNIEnv
*, jobject,
jint width, jint
height) {
if (width > 0 && height > 0)
glViewport(0, 0, width, height);

glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

glUseProgram(program);
glBindBuffer(GL_ARRAY_BUFFER, vbo
);

GLint posAttrib = glGetAttribLocation(program, "vPosition");
glEnableVertexAttribArray(posAttrib);
glVertexAttribPointer(posAttrib,
2, GL_FLOAT, GL_FALSE, 0, 0);

glDrawArrays(GL_TRIANGLES,
0, 3);
glDisableVertexAttribArray(posAttrib);
}
