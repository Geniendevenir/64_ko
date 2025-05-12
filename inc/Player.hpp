/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:54:46 by allan             #+#    #+#             */
/*   Updated: 2025/05/06 22:43:58 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Globals.hpp"

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
		float getVelY(void) const;
		float getGravity(void) const;
		float getMoveSpeed(void) const;
		bool isOnGround();
		
		//Setter
		void setPosX(float const &x);
		void setPosY(float const &y);
		void setVelY(float const &y);
		void setOnGround(bool const &y);

		//Action
		void mooveUp();
		void mooveDown();
		void mooveRight();
		void mooveLeft();
		void addGravity();
		void addVelocity();

	private:
		std::string _name;
		float _posX;
		float _posY;
		float _velY;
		const float _gravity;
		const float _moveSpeed;
		bool _onGround;
};

std::ostream &operator<<(std::ostream &o, const Player &i);

#endif