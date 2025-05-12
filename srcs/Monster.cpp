/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:09:52 by allan             #+#    #+#             */
/*   Updated: 2025/05/12 19:51:15 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Monster.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

Monster::Monster() {
	
	_bodyBase.head_start = {650.0f, static_cast<float>(globals::GROUND_HEIGHT)};
	_bodyBase.head_end = {800.0f, static_cast<float>(globals::GROUND_HEIGHT + 200)};
	_bodyBase.head_color = {255, 255, 255, 255};
	
	_bodyBase.forehead_rec_start = {642.0f, 240.0f};
	_bodyBase.forehead_rec_end = {650.0f, 305.0f};
	_bodyBase.forehead_tri = {{650.0f, 320.0f}, {642.0f, 305.0f}, {650.0f, 305.0f}};
	_bodyBase.forehead_color = {255, 255, 255, 255};
	
	_bodyBase.mouth_start = {650.0f, static_cast<float>(globals::GROUND_HEIGHT + 20)};
	_bodyBase.mouth_end = {700.0, static_cast<float>(globals::GROUND_HEIGHT + 40)};
	_bodyBase.mouth_color = {0, 0, 0, 255};
	
	_bodyBase.nose = {{650.0f, 250.0f}, {625.0f, 220.0f}, {650.0f, 175.0f}};
	_bodyBase.nose_color = {255, 255, 255, 255};

	_bodyBase.eye_start = {690.0, static_cast<float>(globals::GROUND_HEIGHT + 125)};
	_bodyBase.eye_radius = 30.0f;
	_bodyBase.eye_color = {0, 0, 0, 255};

	_bodyMove = _bodyBase;

	_topArm = RobotArm("topArm", {788.0f, 220.0f}, {{200.0f, 3.0f}, {300.0f, 0.0f}});

	//Health bar Version 1: Big souls Healthbar 
/* 	_health.big_rec_start = {static_cast<float>(globals::WIDTH * 0.2), 50.0f};
	_health.big_rec_end= {static_cast<float>(globals::WIDTH * 0.8), 60.0f};
	_health.big_rec_color = {0, 0, 0, 255};
	_health.small_rec_start = {static_cast<float>(globals::WIDTH * 0.2) + 2.5f, 52.0f};
	_health.small_rec_end = {static_cast<float>(globals::WIDTH * 0.8) - 2.5f, 58.0f};
	_health.small_rec_color = {200, 0, 0, 255}; */
	
	//Health bar Version 2: Small healthbar that follows head 
	_healthBase.big_rec_start = {_bodyBase.forehead_rec_start.x, _bodyBase.head_end.y + 10};
	_healthBase.big_rec_end = {_bodyBase.head_end.x + (_bodyBase.forehead_rec_end.x - _bodyBase.forehead_rec_start.x), _bodyBase.head_end.y + 20};
	_healthBase.big_rec_color = {0, 0, 0, 255};
	
	_healthBase.small_rec_start = {_healthBase.big_rec_start.x + 2.5f, _healthBase.big_rec_start.y + 2.5f};
	_healthBase.small_rec_end= {_healthBase.big_rec_end.x - 2.5f, _healthBase.big_rec_end.y - 2.5f};
	_healthBase.small_rec_color = {200, 0, 0, 255};
	
	_healthMove = _healthBase;
	return ;
}


//////////////////////////////////////////////////////////
//					OVERLOADED OPERATOR					//
//////////////////////////////////////////////////////////

/* std::ostream &operator<<(std::ostream &o, const Monster &i) {
	return o;
} */


//////////////////////////////////////////////////////////
//					 GETTER/SETTER						//
//////////////////////////////////////////////////////////

/* std::string Monster::getSomething(void) const {
} */

/* void Monster::setSomething(std::string new_value) {
	//if (new_value >= x)
	//this->something = new_value;
	return ;
} */


//////////////////////////////////////////////////////////
//						 ACTION							//
//////////////////////////////////////////////////////////
Vec2 reflect(Vec2 v) {
	return {v.x, globals::GROUND_HEIGHT - (v.y - globals::GROUND_HEIGHT)};
}

float reflectY(float y) {
	return globals::GROUND_HEIGHT - (y - globals::GROUND_HEIGHT);
}

void Monster::moveArmTo(Vec2 new_target) {
	_topArm.targetPlayer(new_target);
}

void Monster::printMonster(GLFWwindow *window, uint8_t* pixels, Vec2 p_pos) {
	const Body& body = _bodyMove; // always draw the animated version
	const Health& health = _healthMove;

	//float time = glfwGetTime();
	
	//Top Arm
	//_topArm.moveArms(window, time);
	//_topArm.printRobotArm(pixels);
	
	//Neck
	drawRectangle(pixels, {body.head_end.x, body.head_start.y + 5}, {_bodyBase.head_end.x, body.head_end.y - 100}, body.head_color);
	//Head
	drawRectangle(pixels, body.head_start, body.head_end, body.head_color);
	drawRectangle(pixels, body.forehead_rec_start, body.forehead_rec_end, body.forehead_color);
	drawTriangle(pixels, body.forehead_tri, body.forehead_color);
	//Mouth	
	drawRectangle(pixels, body.mouth_start, body.mouth_end, body.mouth_color);
	//Nose	
	drawTriangle(pixels, body.nose, body.nose_color);
	//Eye
	drawCircle(pixels, body.eye_start, body.eye_radius, body.eye_color);

	//Heatlth Bar
	drawRectangle(pixels, health.big_rec_start, health.big_rec_end, health.big_rec_color);
	drawRectangle(pixels, health.small_rec_start, health.small_rec_end, health.small_rec_color);
}

void Monster::printMonsterReflection(GLFWwindow* window, uint8_t* pixels) {
	const Body& body = _bodyMove;

	Rgba dim = { static_cast<uint8_t>(body.head_color.r * 0.5f),
	             static_cast<uint8_t>(body.head_color.g * 0.5f),
	             static_cast<uint8_t>(body.head_color.b * 0.5f),
	             120 };

	// Neck
	Vec2 neck_start = reflect({body.head_end.x, body.head_start.y + 5});
	Vec2 neck_end = reflect({_bodyBase.head_end.x, body.head_end.y - 100});
	if (neck_start.y > neck_end.y) std::swap(neck_start.y, neck_end.y);
	if (neck_start.x > neck_end.x) std::swap(neck_start.x, neck_end.x);
	drawRectangle(
		pixels,
		neck_start,
		neck_end,
		dim);
		
	// Head 
	Vec2 head_start = reflect(body.head_start);
	Vec2 head_end = reflect(body.head_end);
	if (head_start.y > head_end.y) std::swap(head_start.y, head_end.y);
	if (head_start.x > head_end.x) std::swap(head_start.x, head_end.x);
	drawRectangle(
		pixels,
		head_start,
		head_end,
		dim);
		
	// Forehead Rect
	Vec2 forehead_rec_start = reflect(body.forehead_rec_start);
	Vec2 forehead_rec_end = reflect(body.forehead_rec_end);
	if (forehead_rec_start.y > forehead_rec_end.y) std::swap(forehead_rec_start.y, forehead_rec_end.y);
	if (forehead_rec_start.x > forehead_rec_end.x) std::swap(forehead_rec_start.x, forehead_rec_end.x);
	drawRectangle(pixels,
		forehead_rec_start,
		forehead_rec_end,
		dim);

	// Forehead Triangle TO DO IF MONSTER GOES UP
	Vec3 reflected_tri = {
		{body.forehead_tri.v1.x, reflectY(body.forehead_tri.v1.y)},
		{body.forehead_tri.v2.x, reflectY(body.forehead_tri.v2.y)},
		{body.forehead_tri.v3.x, reflectY(body.forehead_tri.v3.y)}
	};
	drawTriangle(pixels, reflected_tri, dim);

	// Mouth
	Vec2 mouth_start = reflect(body.mouth_start);
	Vec2 mouth_end = reflect(body.mouth_end);
	if (mouth_start.y > mouth_end.y) std::swap(mouth_start.y, mouth_end.y);
	if (mouth_start.x > mouth_end.x) std::swap(mouth_start.x, mouth_end.x);
	drawRectangle(pixels,
		mouth_start,
		mouth_end,
		{0, 0, 0, 100}); // faded black

	// Nose
	Vec3 nose_reflected = {
		{body.nose.v1.x, reflectY(body.nose.v1.y)},
		{body.nose.v2.x, reflectY(body.nose.v2.y)},
		{body.nose.v3.x, reflectY(body.nose.v3.y)} };
	drawTriangle(pixels, nose_reflected, dim);

	// Eye
	drawCircle(pixels,
		{body.eye_start.x, reflectY(body.eye_start.y)},
		body.eye_radius,
		{0, 0, 0, 100});
}


void Monster::moveTo(Vec2 new_pos) {
	_bodyMove = _bodyBase;
	_healthMove = _healthBase;
	
	Vec2 base_pos = _bodyBase.head_start;
	Vec2 delta = { new_pos.x - base_pos.x, new_pos.y - base_pos.y };

	_bodyMove.head_start = offsetVec2(_bodyMove.head_start, delta);
	_bodyMove.head_end   = offsetVec2(_bodyMove.head_end, delta);

	_bodyMove.forehead_rec_start = offsetVec2(_bodyMove.forehead_rec_start, delta);
	_bodyMove.forehead_rec_end   = offsetVec2(_bodyMove.forehead_rec_end, delta);
	_bodyMove.forehead_tri       = offsetVec3(_bodyMove.forehead_tri, delta);

	_bodyMove.mouth_start = offsetVec2(_bodyMove.mouth_start, delta);
	_bodyMove.mouth_end   = offsetVec2(_bodyMove.mouth_end, delta);

	_bodyMove.nose = offsetVec3(_bodyMove.nose, delta);

	_bodyMove.eye_start = offsetVec2(_bodyMove.eye_start, delta);
	
	_healthMove.big_rec_start = offsetVec2(_healthMove.big_rec_start, delta);
	_healthMove.big_rec_end = offsetVec2(_healthMove.big_rec_end, delta);
	_healthMove.small_rec_start = offsetVec2(_healthMove.small_rec_start, delta);
	_healthMove.small_rec_end = offsetVec2(_healthMove.small_rec_end, delta);
}
