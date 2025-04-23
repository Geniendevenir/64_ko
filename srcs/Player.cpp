/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:59:20 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 19:53:26 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

Player::Player() : tex(0), _name("Player"), _posX(globals::WIDTH / 2), _posY(globals::GROUND_Y + 1), _velY(0.0f), _gravity(0.5f), _moveSpeed(2.0f), _onGround(true){
	return ;
}

Player::Player(std::string name) : tex(0), _name(name), _posX(globals::WIDTH / 2), _posY(globals::GROUND_Y + 1), _velY(0.0f), _gravity(0.5f), _moveSpeed(2.0f), _onGround(true) {
	return ;
}

Player::Player(const Player &src) : _gravity(0.5f), _moveSpeed(2.0f) {
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
		tex = rhs.tex;
		_name = rhs._name;
		_posX = rhs._posX;
		_posY = rhs._posY;
		_velY = rhs._velY;
		_onGround = rhs._onGround;
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

float Player::getPosX(void) const {
	return _posX;
}

float Player::getPosY(void) const {
	return _posY;
}

float Player::getVelY(void) const {
	return _velY;
}

float Player::getGravity(void) const {
	return _gravity;
}

float Player::getMoveSpeed(void) const {
	return _moveSpeed;
}

bool Player::isOnGround() {
	return _onGround;
}

void Player::setPosX(float const &x) {
	_posX = x;
}

void Player::setPosY(float const &y) {
	_posY = y;
}

void Player::setVelY(float const &y) {
	_velY = y;
}

void Player::setOnGround(bool const &y) {
	_onGround = y;
}

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
	_posX += _moveSpeed;
}

void Player::mooveLeft() {
	_posX -= _moveSpeed;
}

void Player::addGravity() {
	_velY += _gravity;
}

void Player::addVelocity() {
	_posY -= _velY;
}
