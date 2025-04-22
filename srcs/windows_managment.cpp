/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_managment.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:17:07 by allan             #+#    #+#             */
/*   Updated: 2025/04/22 22:28:46 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_game.hpp"

int	window_init(GLFWwindow** window) {
	glfwSetErrorCallback(error_callback);	//Tells Glfw to use our function error_callback for error reporting
	if (!glfwInit())						//Initializes the GLfw Library
		return ERROR;
		
	*window = glfwCreateWindow(800, 600, "Tiny Game", NULL, NULL); //Creates a pointer to a Window
	if (!*window) {
		glfwTerminate();
		return ERROR;
	}
	
	glfwMakeContextCurrent(*window);				//Makes the window passed as param the current context
	glewExperimental = GL_TRUE;					//Makes GLEW load all possible extensions
	if (glewInit() != GLEW_OK)	{				//Load all GLEW EXTENTIONS
		glfwDestroyWindow(*window);
		glfwTerminate();	
		return ERROR;
	}

	return SUCCESS;
}

void clean_window(GLFWwindow** window) {
	glfwDestroyWindow(*window);
	glfwTerminate();							//Cleans up all GLFW resources and shut down the library
}