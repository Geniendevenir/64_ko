/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:35:46 by allan             #+#    #+#             */
/*   Updated: 2025/05/13 18:53:06 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Knights.hpp"
#include "Player.hpp"

void handle_input(GLFWwindow** window, Player &player, Stage &stage, double deltaTime) {
		//Handle Input
/* 		if (glfwGetKey(*window, GLFW_KEY_W) == GLFW_PRESS) player.moveUp();
        if (glfwGetKey(*window, GLFW_KEY_S) == GLFW_PRESS) player.moveDown(); */
        if (glfwGetKey(*window, GLFW_KEY_A) == GLFW_PRESS) player.moveLeft(stage, deltaTime);
        if (glfwGetKey(*window, GLFW_KEY_D) == GLFW_PRESS) player.moveRight(stage, deltaTime);
		

		bool jumpPressed = glfwGetKey(*window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(*window, GLFW_KEY_SPACE) == GLFW_PRESS;
		if (jumpPressed && player.isOnGround()) {
		    player.setVelY(-450.0f); // negative = upward
		    player.setOnGround(false);
		}
		
		//Apply Gravity
		player.addGravity(deltaTime);
		player.addVelocity(deltaTime);	
		
	//Groung Collision
		//With Upper Stage
		if (player.getPosX() >= stage.getUpperStageStart().x - 20 && player.getPosX() <= stage.getUpperStageEnd().x) {
			if (player.getPosY() <= stage.getUpperStageY()) {
				player.setPosY(stage.getUpperStageY());
				player.setVelY(0);
				player.setOnGround(true);	
			}	
		}
		//With Floor
		else if (player.getPosY() <= globals::GROUND_HEIGHT) {
			player.setPosY(globals::GROUND_HEIGHT);
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