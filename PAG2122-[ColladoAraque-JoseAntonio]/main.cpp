#include <iostream>
// IMPORTANTE: El include de GLEW debe estar siempre ANTES de el de GLFW
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

float red = 0.6;
float green = 0.6;
float blue = 0.6;

int color = 0;
std::string colores[3] = {"Rojo", "Verde", "Azul"};

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void callbackRefrescoVentana(GLFWwindow *ventana) {
    PAG::Renderer::getInstancia()->refrescar();
    glfwSwapBuffers(ventana);
    std::cout << "Finaliza el callback de refresco" << std::endl;
}


// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void callbackFramebufferSize(GLFWwindow *window, int width, int height) {
    PAG::Renderer::getInstancia()->setViewport(0, 0, width, height);
    std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void callbackTecla(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    std::cout << "Key callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void callbackBotonRaton(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << "Pulsado el boton: " << button << std::endl;
        color = (color + 1) % 3;
        std::cout << "Seleccionado el color " << colores[color] << std::endl;
    } else if (action == GLFW_RELEASE) {
        std::cout << "Soltado el boton: " << button << std::endl;
    }
}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void callbackScroll(GLFWwindow *window, double xoffset, double yoffset) {
//    std::cout << "Movida la rueda del raton " << xoffset << " Unidades en horizontal y "
//              << yoffset << " unidades en vertical" << std::endl;

    //Cambio del color en función al color seleccionado. La selección se altera con el clic izquierdo del ratón
    if (color == 0) {
        red += (float) (yoffset * 0.05f);
        if (red > 1) {
            red = 1;
        } else if (red < 0) {
            red = 0;
        }
    } else if (color == 1) {
        green += (float) (yoffset * 0.05f);
        if (green > 1) {
            green = 1;
        } else if (green < 0) {
            green = 0;
        }
    } else {
        blue += (float) (yoffset * 0.05f);
        if (blue > 1) {
            blue = 1;
        } else if (blue < 0) {
            blue = 0;
        }
    }


    std::cout << "Red: " << red << " green: " << green << " blue: " << blue << std::endl;
    PAG::Renderer::getInstancia()->setColorFondo(red, green, blue, 1.0);
    PAG::Renderer::getInstancia()->limpiarGL(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main() {
    std::cout << "Starting application pag prueba 01" << std::endl;
    // - Inicializa GLFW. Es un proceso que solo debe realizarse una vez en la aplicación
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint(GLFW_SAMPLES, 4); // - Activa antialiasing con 4 muestras.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // - Esta y las 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // OpenGL Core Profile 4.1.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;

    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow(1024, 576, "PAG2122-[ColladoAraque-JoseAntonio]", nullptr, nullptr);
    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }
    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent(window);
    // - Ahora inicializamos GLEW.
    // IMPORTANTE: GLEW debe inicializarse siempre DESPUÉS de que se haya
    // inicializado GLFW y creado la ventana
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
        return -3;
    }
    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
    // 3D construido.
    std::cout << PAG::Renderer::getInstancia()->getPropiedadGL(GL_RENDERER) << std::endl
              << PAG::Renderer::getInstancia()->getPropiedadGL(GL_VENDOR) << std::endl
              << PAG::Renderer::getInstancia()->getPropiedadGL(GL_VERSION) << std::endl
              << PAG::Renderer::getInstancia()->getPropiedadGL(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback(window, callbackRefrescoVentana);
    glfwSetFramebufferSizeCallback(window, callbackFramebufferSize);
    glfwSetKeyCallback(window, callbackTecla);
    glfwSetMouseButtonCallback(window, callbackBotonRaton);
    glfwSetScrollCallback(window, callbackScroll);

    // - Establecemos un gris medio como color con el que se borrará el frame buffer.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    PAG::Renderer::getInstancia()->setColorFondo(0.6, 0.6, 0.6, 1.0);

    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    PAG::Renderer::getInstancia()->activarUtilidadGL(GL_DEPTH_TEST);
    // - Ciclo de eventos de la aplicación. La condición de parada es que la
    // ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
    // botón de cerrar la ventana (la X).
    while (!glfwWindowShouldClose(window)) {
        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finishing application pag prueba" << std::endl;
    glfwDestroyWindow(window); // - Cerramos y destruimos la ventana de la aplicación.
    glfwTerminate(); // - Liberamos los recursos que ocupaba GLFW.
}
