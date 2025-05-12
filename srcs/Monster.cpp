/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:09:52 by allan             #+#    #+#             */
/*   Updated: 2025/05/11 21:25:33 by allan            ###   ########.fr       */
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

void Monster::moveArmTo(Vec2 new_target) {
	_topArm.targetPlayer(new_target);
}

void Monster::printMonster(GLFWwindow *window, uint8_t* pixels, Vec2 p_pos) {
	const Body& body = _bodyMove; // always draw the animated version

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
}

void Monster::moveTo(Vec2 new_pos) {
	_bodyMove = _bodyBase;

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
	// No need to offset radius/color
}
