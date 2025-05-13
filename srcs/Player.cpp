/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:59:20 by allan             #+#    #+#             */
/*   Updated: 2025/05/13 18:53:14 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

Player::Player() : tex(0), _name("Player"), _posX(globals::WIDTH / 2), _posY(globals::GROUND_HEIGHT + 1), _centerX(_posX + globals::PLAYER_SIZE / 2), _centerY(_posY + globals::PLAYER_SIZE / 2), _velY(0.0f), _gravity(1200.0f), _moveSpeed(200.0f), _onGround(true) {
	return ;
}

Player::Player(std::string name) : tex(0), _name(name), _posX(globals::WIDTH / 2 - 200), _posY(globals::GROUND_HEIGHT + 1), _centerX(_posX + globals::PLAYER_SIZE / 2), _centerY(_posY + globals::PLAYER_SIZE / 2), _velY(0.0f), _gravity(1200.0f), _moveSpeed(120.0f), _onGround(true) {
	return ;
}

Player::Player(const Player &src) : _gravity(800.0f), _moveSpeed(200.0f) {
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
		_centerX = rhs._centerX;
		_centerY = rhs._centerY;
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

float Player::getCenterX(void) const {
	return _centerX;
}

float Player::getCenterY(void) const {
	return _centerY;
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
void Player::autoSetCenterX() {
	_centerX = _posX + globals::PLAYER_SIZE / 2;
}

void Player::autoSetCenterY() {
	_centerY = _posY + globals::PLAYER_SIZE / 2;
}

void Player::setPosX(float const &x) {
	_posX = x;
	autoSetCenterX();
}


void Player::setPosY(float const &y) {
	_posY = y;
	autoSetCenterY();
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


void Player::moveUp() {
	_posY += 2;
	autoSetCenterY();
}

void Player::moveDown() {
	_posY -= 2;
	autoSetCenterY();
}


void Player::moveRight(const Stage &stage, double deltaTime) {
	float rightMostPixel = _posX + globals::PLAYER_SIZE; 
	if (_posY < stage.getUpperStageY()) {
		if (rightMostPixel < stage.getUpperStageStart().x && rightMostPixel + _moveSpeed * deltaTime >= stage.getUpperStageStart().x)
		{
			_posX = (stage.getUpperStageStart().x - globals::PLAYER_SIZE) - 1;
			autoSetCenterX();
			return;
		}
	}
	_posX += _moveSpeed * deltaTime;
	autoSetCenterX();
	scroll_x += _moveSpeed * deltaTime;
}

void Player::moveLeft(const Stage &stage, double deltaTime) {
	float leftMostPixel = _posX; 
	if (_posY < stage.getUpperStageY()) {
		if (leftMostPixel > stage.getUpperStageEnd().x && leftMostPixel - _moveSpeed * deltaTime <= stage.getUpperStageEnd().x)
		{
			_posX = stage.getUpperStageEnd().x + 1;
			autoSetCenterX();
			return;
		}
	}
	_posX -= _moveSpeed * deltaTime;
	autoSetCenterX();
	scroll_x -= _moveSpeed * deltaTime;
}

void Player::addGravity(double deltaTime) {
	_velY += _gravity * deltaTime;
}

void Player::addVelocity(double deltaTime) {
	_posY -= _velY * deltaTime;
	autoSetCenterY();
}


//////////////////////////////////////////////////////////
//						 PRINT							//
//////////////////////////////////////////////////////////

void draw_player(uint8_t *pixels, const Player &player) {
	
	for (int y = 0; y < globals::PLAYER_SIZE; ++y) {
		for (int x = 0; x < globals::PLAYER_SIZE; ++x) {
			int px = static_cast<int>(player.getPosX()) + x;
			int py = static_cast<int>(player.getPosY()) + y;
			if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
				int i = (py * globals::WIDTH + px) * 4;
				pixels[i + 0] = 255; //Red
				pixels[i + 1] = 0; //Green
				pixels[i + 2] = 0; //Blue
				pixels[i + 3] = 255; //Alpha
			}
		}
	}
}

void draw_player_reflection(uint8_t* pixels, const Player& player) {
	for (int y = 0; y < globals::PLAYER_SIZE; ++y) {
		for (int x = 0; x < globals::PLAYER_SIZE; ++x) {
			int px = static_cast<int>(player.getPosX()) + x;
			int py_original = static_cast<int>(player.getPosY()) + y;

			// Reflect across the floor line (GROUND_HEIGHT)
			int py_reflect = globals::GROUND_HEIGHT - (py_original - globals::GROUND_HEIGHT);

			// Clamp to stay in floor area
			if (px >= 0 && px < globals::WIDTH &&
			    py_reflect >= 0 && py_reflect < globals::GROUND_HEIGHT) {

				int i = (py_reflect * globals::WIDTH + px) * 4;

				// Dimmed color for reflection
				pixels[i + 0] = 150;  // Red
				pixels[i + 1] = 0;    // Green
				pixels[i + 2] = 0;    // Blue
				pixels[i + 3] = 120;  // Alpha (faded)
			}
		}
	}
}