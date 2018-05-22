// Using OpenGL Compute Shader to implement SAXPY

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/glext.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#define N 20480

int main (int argc, char** argv)
{

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (1, 1);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Compute Shader");

    // get OpenGL version info
    const GLubyte* renderer;
    const GLubyte* version;

    renderer = glGetString (GL_RENDERER);
    version = glGetString (GL_VERSION);
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported: %s\n", version);

    const char* compute_shader =
        "#version 430\n"
        "uniform float a;"
        "layout (local_size_x = 32) in;"
        "layout (std430, binding=0) buffer xblock { float x[]; };"
        "layout (std430, binding=1) buffer yblock { float y[]; };"
        "void main () {"
        "    int index = int(gl_GlobalInvocationID);"
        "    y[index] += a * x[index];"
        "}";

    GLuint cs = glCreateShader (GL_COMPUTE_SHADER);
    glShaderSource (cs, 1, &compute_shader, NULL);
    glCompileShader (cs);

    GLuint cs_program = glCreateProgram ();
    glAttachShader (cs_program, cs);
    glLinkProgram (cs_program);

    // initialize x and y
    float *x, *y;
    size_t size = N * sizeof (float);
    x = (float *) malloc (size);
    y = (float *) malloc (size);

    srand (time (NULL));
    int i;
    for (i=0; i<N; i++)
        x[i] = (float) random () / RAND_MAX;
    for (i=0; i<N; i++)
        y[i] = (float) random () / RAND_MAX;

    float a = (float) random () / RAND_MAX;

    // buffer objects
    GLuint bo[2];
    glGenBuffers(2, bo);

    // bind buffer object bo[0] to indexed buffer target with binding=0
    // (xblock in computer_shader)
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bo[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, x, GL_STATIC_READ);

    // bind buffer object bo[1] to indexed buffer target with binding=1
    // (yblock in computer_shader)
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bo[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, y, GL_DYNAMIC_READ);

    glUseProgram (cs_program);
    glUniform1f (glGetUniformLocation (cs_program, "a"), a);

    glDispatchCompute(N/32, 1, 1);

    // read from buffer object to host memory
    float *d;
    d = (float *) malloc (size);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, size, d);

    // verify the results
    float m = -1.0f;
    float tmp;
    for (i=0; i<N; i++) {
        y[i] += a * x[i];
      	tmp = fabsf ( (d[i]-y[i])/y[i] );
	      if ( tmp > m ) m = tmp;
    }

    // clean up
    glDeleteBuffers(2, bo);
    glDetachShader(cs_program, cs);
    glDeleteShader(cs);
    glDeleteProgram(cs_program);

    free(x);
    free(y);
    free(d);

    if ( m < 1E-6 ) {
        printf("Success!\n");
        return 0;
    }
    else {
        printf("Failure!\n");
        return 1;
    }
}
