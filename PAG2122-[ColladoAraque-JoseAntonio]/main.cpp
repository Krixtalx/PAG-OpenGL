#include <iostream>
// IMPORTANTE: El include de GLEW debe estar siempre ANTES de el de GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

int colorSeleccionado = 0;
std::string colores[3] = {"Rojo", "Verde", "Azul"};

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void callbackRefrescoVentana(GLFWwindow *ventana) {
	PAG::Renderer::getInstancia()->refrescar();
	glfwSwapBuffers(ventana);
	//std::cout << "Finaliza el callback de refresco" << std::endl;
}


// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void callbackFramebufferSize(GLFWwindow *window, int width, int height) {
	PAG::Renderer::getInstancia()->setViewport(0, 0, width, height);
	//std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void callbackTecla(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	//std::cout << "Key callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void callbackBotonRaton(GLFWwindow *window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		//std::cout << "Pulsado el boton: " << button << std::endl;
		colorSeleccionado = (colorSeleccionado + 1) % 3;
		std::cout << "Seleccionado el colorSeleccionado "
		          << colores[colorSeleccionado]
		          << std::endl;
	} else if (action == GLFW_RELEASE) {
		//std::cout << "Soltado el boton: " << button << std::endl;
	}
}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void callbackScroll(GLFWwindow *window, double xoffset, double yoffset) {
//    std::cout << "Movida la rueda del raton " << xoffset << " Unidades en horizontal y "
//              << yoffset << " unidades en vertical" << std::endl;

	float rojo = PAG::Renderer::getInstancia()->getRojoFondo();
	float verde = PAG::Renderer::getInstancia()->getVerdeFondo();
	float azul = PAG::Renderer::getInstancia()->getAzulFondo();
	//Cambio del colorSeleccionado en función al colorSeleccionado seleccionado. La selección se altera con el clic izquierdo del ratón
	if (colorSeleccionado == 0) {
		rojo += (float) (yoffset * 0.05f);
		if (rojo > 1) {
			rojo = 1;
		} else if (rojo < 0) {
			rojo = 0;
		}
	} else if (colorSeleccionado == 1) {
		verde += (float) (yoffset * 0.05f);
		if (verde > 1) {
			verde = 1;
		} else if (verde < 0) {
			verde = 0;
		}
	} else {
		azul += (float) (yoffset * 0.05f);
		if (azul > 1) {
			azul = 1;
		} else if (azul < 0) {
			azul = 0;
		}
	}


	std::cout << "rojoFondo: " << rojo << " verdeFondo: " << verde << " azulFondo: " << azul << std::endl;
	PAG::Renderer::getInstancia()->setColorFondo(rojo, verde, azul, 1);
	callbackRefrescoVentana(window);
	PAG::Renderer::getInstancia()->limpiarGL(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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


	PAG::Renderer::getInstancia()->inicializaOpenGL();

	// - Ciclo de eventos de la aplicación. La condición de parada es que la
	// ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
	// botón de cerrar la ventana (la X).
	std::cout
			<< "Con el clic izquierdo del raton se selecciona el color a cambiar. Por defecto se encuentra el color rojo seleccionado."
			<< std::endl;
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
