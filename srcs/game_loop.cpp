/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:20:43 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 18:46:53 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_game.hpp"
#include "Player.hpp"

int game_loop(GLFWwindow** window, Player &player, c_vector &pixels) {
	
	while (!glfwWindowShouldClose(*window)) { 	//Main Loop: Check if the user ask to close the window
		glfwPollEvents();						//Checks for input event (Keyboard, mouse, window resize...)
		
		handle_input(window, player);

		std::memset(pixels.data(), 0, pixels.size());

		draw_player(player, pixels);
		draw_floor(pixels);

		//upload buffer to gpu
		glBindTexture(GL_TEXTURE_2D, player.tex);
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

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