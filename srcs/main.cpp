/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:47:43 by allan             #+#    #+#             */
/*   Updated: 2025/04/26 18:31:22 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotArm.hpp"
#include "Globals.hpp"

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(globals::WIDTH, globals::HEIGHT, "Basics", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	std::vector<unsigned char> pixels(globals::WIDTH * globals::HEIGHT * 4);


	RobotArm Jarvis;

    while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		float currentTime = glfwGetTime();
		Jarvis.moveArms(&window, currentTime);	
		
        // Clear screen
        std::memset(pixels.data(), 0, pixels.size());
		
		Jarvis.printRobotArm(pixels);

        // Upload to GPU
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        // Draw
        int winW, winH;
        glfwGetFramebufferSize(window, &winW, &winH);
        glViewport(0, 0, winW, winH);

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-1, -1);
        glTexCoord2f(1, 0); glVertex2f( 1, -1);
        glTexCoord2f(1, 1); glVertex2f( 1,  1);
        glTexCoord2f(0, 1); glVertex2f(-1,  1);
        glEnd();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
