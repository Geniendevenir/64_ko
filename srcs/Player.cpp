/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:59:20 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 00:53:42 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

Player::Player() : pixels(WIDTH * HEIGHT * 4), tex(0), _name("Player"), _posX(WIDTH / 2), _posY(HEIGHT / 2) {
	return ;
}

Player::Player(std::string name) : pixels(WIDTH * HEIGHT * 4), tex(0), _name(name), _posX(WIDTH / 2), _posY(HEIGHT / 2) {
	return ;
}

Player::Player(const Player &src) {
	*this = src;
	return ;
}


Player::~Player() {
	return ;
}


//////////////////////////////////////////////////////////
//					OVERLOADED OPERATOR					//
//////////////////////////////////////////////////////////

Player& Player::operator=(const Player &rhs) {
	if (this != &rhs) {
		_name = rhs._name;
		_posX = rhs._posX;
		_posY = rhs._posY;
		pixels = rhs.pixels;
		tex = rhs.tex;
	}
	return *this;
}


std::ostream &operator<<(std::ostream &o, const Player &i) {
	o << "Player Name: " << i.getName() << "\n"
		<< "PosX: " << i.getPosX() << "\n"
		<< "PosY: " << i.getPosY() << "\n"
		<< std::endl;
	return o;
}


//////////////////////////////////////////////////////////
//					 GETTER/SETTER						//
//////////////////////////////////////////////////////////

std::string Player::getName(void) const {
	return _name;
}

int Player::getPosX(void) const {
	return _posX;
}

int Player::getPosY(void) const {
	return _posY;
}

/* c_vector Player::getPixels(void) const {
	return _pixels;
} */


void Player::setPosX(int x) {
	_posX = x;
}

void Player::setPosY(int y) {
	_posY = y;
}

/* void Player::setPixels(c_vector pixels) {
	_pixels = pixels;
} */


//////////////////////////////////////////////////////////
//						 ACTION							//
//////////////////////////////////////////////////////////


void Player::mooveUp() {
	_posY += 2;
}

void Player::mooveDown() {
	_posY -= 2;
}

void Player::mooveRight() {
	_posX += 2;
}

void Player::mooveLeft() {
	_posX -= 2;
}
