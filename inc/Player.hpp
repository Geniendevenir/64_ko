/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:54:46 by allan             #+#    #+#             */
/*   Updated: 2025/05/13 18:29:22 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Globals.hpp"
#include "Stage.hpp"

class Player {
	public:
		GLuint tex;
		float scroll_x = 0.0f;
		
		Player();
		Player(std::string name);
		Player(const Player &src);
		~Player();

		Player &operator=(const Player &rhs);
	
		//Getter
		std::string getName(void) const;
		float getPosX(void) const;
		float getPosY(void) const;
		float getCenterX(void) const;
		float getCenterY(void) const;
		float getVelY(void) const;
		float getGravity(void) const;
		float getMoveSpeed(void) const;
		bool isOnGround();
		
		//Setter
		void autoSetCenterX();
		void autoSetCenterY();
		void setPosX(float const &x);
		void setPosY(float const &y);
		void setVelY(float const &y);
		void setOnGround(bool const &y);

		//Action
		void moveUp();
		void moveDown();
		void moveRight(const Stage &stage, double deltaTime);
		void moveLeft(const Stage &stage, double deltaTime);
		void addGravity(double deltaTime);
		void addVelocity(double deltaTime);

	private:
		std::string _name;
		float _posX;
		float _posY;
		float _centerX;
		float _centerY;
		float _velY;
		const float _gravity;
		const float _moveSpeed;
		bool _onGround;
};

std::ostream &operator<<(std::ostream &o, const Player &i);

void draw_player(uint8_t *pixels, const Player &player);
void draw_player_reflection(uint8_t* pixels, const Player& player);
void handle_input(GLFWwindow** window, Player &player, Stage &stage, double deltaTime);

#endif