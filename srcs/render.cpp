/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:20:43 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 01:22:22 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_game.hpp"
#include "Player.hpp"

int game_loop(GLFWwindow** window, Player &player) {
	
	while (!glfwWindowShouldClose(*window)) { 	//Main Loop: Check if the user ask to close the window
		glfwPollEvents();						//Checks for input event (Keyboard, mouse, window resize...)
		
		//Handle Input
		if (glfwGetKey(*window, GLFW_KEY_W) == GLFW_PRESS) player.mooveUp();
        if (glfwGetKey(*window, GLFW_KEY_S) == GLFW_PRESS) player.mooveDown();
        if (glfwGetKey(*window, GLFW_KEY_A) == GLFW_PRESS) player.mooveLeft();
        if (glfwGetKey(*window, GLFW_KEY_D) == GLFW_PRESS) player.mooveRight();
		
		//Clamp position
		if (player.getPosX() < 0) player.setPosX(0);
        if (player.getPosY() < 0) player.setPosY(0);
        if (player.getPosX() > WIDTH - SQUARE_SIZE) player.setPosX(WIDTH - SQUARE_SIZE);
        if (player.getPosY() > HEIGHT - SQUARE_SIZE) player.setPosY(HEIGHT - SQUARE_SIZE);

		std::memset(player.pixels.data(), 0, player.pixels.size());

		draw_player(player);

		//upload buffer to gpu
		glBindTexture(GL_TEXTURE_2D, player.tex);
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, player.pixels.data());

		// Set Viewport
		int winW, winH;
		glfwGetFramebufferSize(*window, &winW, &winH);
		glViewport(0, 0, winW, winH);

		//Clear Screen
		glClear(GL_COLOR_BUFFER_BIT);			//Clear the Color Buffer (Set the color screen to black): First thing to render each frame before drawing
		
		// Draw fullscreen textures quad
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, player.tex);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex2f(-1, -1);
			glTexCoord2f(1, 0); glVertex2f(1, -1);
            glTexCoord2f(1, 1); glVertex2f(1, 1);
            glTexCoord2f(0, 1); glVertex2f(-1, 1);
        glEnd();
		
		glfwSwapBuffers(*window);				//Show/Push the image that we just rendered by swapping the back buffer and the front one
	}
	return SUCCESS;
}