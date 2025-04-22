/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:54:46 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 00:51:26 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "global.hpp"

class Player {
	public:
		c_vector pixels;
		GLuint tex;
		
		Player();
		Player(std::string name);
		Player(const Player &src);
		~Player();

		Player &operator=(const Player &rhs);
	
		//Getter
		std::string getName(void) const;
		int getPosX(void) const;
		int getPosY(void) const;
		//c_vector getPixels(void) const;
		
		//Setter
		void setPosX(int x);
		void setPosY(int y);
		//void setPixels(c_vector pixels);

		//Action
		void mooveUp();
		void mooveDown();
		void mooveRight();
		void mooveLeft();

	private:
		std::string _name;
		int _posX;
		int _posY;
};

std::ostream &operator<<(std::ostream &o, const Player &i);

#endif