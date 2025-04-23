/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:35:46 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 19:56:03 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_game.hpp"

void handle_input(GLFWwindow** window, Player &player) {
		//Handle Input
/* 		if (glfwGetKey(*window, GLFW_KEY_W) == GLFW_PRESS) player.mooveUp();
        if (glfwGetKey(*window, GLFW_KEY_S) == GLFW_PRESS) player.mooveDown(); */
        if (glfwGetKey(*window, GLFW_KEY_A) == GLFW_PRESS) player.mooveLeft();
        if (glfwGetKey(*window, GLFW_KEY_D) == GLFW_PRESS) player.mooveRight();
		

		bool jumpPressed = glfwGetKey(*window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(*window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (jumpPressed && player.isOnGround()) {
		    player.setVelY(-10.0f); // negative = upward
		    player.setOnGround(false);
		}
		
		//Apply Gravity
		player.addGravity();
		player.addVelocity();	
		
		//Groung Collision
		//float playerFeet = player.getPosY() + globals::PLAYER_SIZE;	
		if (player.getPosY() <= globals::GROUND_Y) {
			player.setPosY(globals::GROUND_Y + 1);
			player.setVelY(0);
			player.setOnGround(true);
		} else {
			player.setOnGround(false);
		}
		
		//Clamp position
		if (player.getPosX() < 0) player.setPosX(0);
        if (player.getPosX() > globals::WIDTH - globals::PLAYER_SIZE) player.setPosX(globals::WIDTH - globals::PLAYER_SIZE);
      	//if (player.getPosY() < 0) player.setPosY(0);
        //if (player.getPosY() > globals::HEIGHT - globals::PLAYER_SIZE) player.setPosY(globals::HEIGHT - globals::PLAYER_SIZE);
}