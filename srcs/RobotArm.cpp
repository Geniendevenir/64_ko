/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotArm.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:23:56 by allan             #+#    #+#             */
/*   Updated: 2025/04/26 19:05:23 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotArm.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

RobotArm::RobotArm() : _name("Jarvis"), _sumAngle(0) {
	_base = {globals::WIDTH / 2.0f, globals::HEIGHT / 2.0f};
	_segments.push_back({100.0f, 0.0f});
	_segments.push_back({100.0f, 0.0f});
	_points.resize(_segments.size() + 1);
	_points[0] = _base;
	updatePoints();
	_target = _points.back();
	_lastInputTime = 0.0f;
	return ;
}


RobotArm::RobotArm(std::string name, Vec2 base, std::vector<Segment> segments) : _name(name), _sumAngle(0), _base(base), _segments(segments) {
	_points.resize(_segments.size() + 1);
	_points[0] = base;
	updatePoints();
	_target = _points.back();
	_lastInputTime = 0.0f;
	return ; 
}

RobotArm::RobotArm(const RobotArm &src) {
	*this = src;
	return ;
}


RobotArm::~RobotArm() {
	return ;
}


//////////////////////////////////////////////////////////
//					OVERLOADED OPERATOR					//
//////////////////////////////////////////////////////////

RobotArm& RobotArm::operator=(const RobotArm &rhs) {
	if (this != &rhs) {
		_name = rhs._name;
		_base = rhs._base;
		_segments = rhs._segments;
		_points = rhs._points;
		_sumAngle = rhs._sumAngle;
		updatePoints();
		_target = rhs._target; 
		_lastInputTime = rhs._lastInputTime;
	}
	return *this;
}


std::ostream &operator<<(std::ostream &o, const RobotArm &i) {
	o << "Base Coordinate:\n"
	<< "\tx = " << i.getBase().x
	<< "\ty = " << i.getBase().y
	<< std::endl;
	return o;
}


//////////////////////////////////////////////////////////
//					 GETTER/SETTER						//
//////////////////////////////////////////////////////////

Vec2 RobotArm::getBase() const {
	return _base;
}

Vec2 RobotArm::getPoint(int i) const {
	if (i < static_cast<int>(_segments.size())+ 1)
		return _points[i];
	return {0.00f, 0.00f};	
}

Segment RobotArm::getSegment(size_t i) const {
	if (i < _segments.size())
		return _segments[i];
	return {0.00f, 0.00f};
}


/* void RobotArm::setSomething(std::string new_value) {
	//if (new_value >= x)
	//this->something = new_value;
	return ;
} */


//////////////////////////////////////////////////////////
//						 ACTION							//
//////////////////////////////////////////////////////////
void RobotArm::moveArms(GLFWwindow **window, float currentTime) {
	if (currentTime - _lastInputTime > _inputCooldown) {
		if (glfwGetKey(*window, GLFW_KEY_W) == GLFW_PRESS) {
			_target.y = _points.back().y + 2.0f;
			inverseKinematics();
			_lastInputTime = currentTime;
		}
		if (glfwGetKey(*window, GLFW_KEY_A) == GLFW_PRESS) { 
			_target.x = _points.back().x - 2.0f;
			inverseKinematics();
			_lastInputTime = currentTime;
		}
		if (glfwGetKey(*window, GLFW_KEY_S) == GLFW_PRESS) { 
			_target.y = _points.back().y - 2.0f;
			inverseKinematics();
			_lastInputTime = currentTime;
		}
		if (glfwGetKey(*window, GLFW_KEY_D) == GLFW_PRESS) { 
			_target.x = _points.back().x + 2.0f;
			inverseKinematics();
			_lastInputTime = currentTime;
		}
	}
}

//////////////////////////////////////////////////////////
//					INVERSE KINEMATICS					//
//////////////////////////////////////////////////////////

void RobotArm::inverseKinematics() {
	const float tolerance = 1.0f;
	int ik_passes = 100; // <--- NEW (small value)
    while (ik_passes-- > 0 && Vec2::distance(_points.back(), _target) > tolerance)
    {
        for (int joint = _segments.size() - 1; joint >= 0; --joint)
            adjustAngle(joint, _target);
        updatePoints();
    }	
}

void RobotArm::updatePoints() {
	_sumAngle = 0;
	for (size_t i = 0; i < _segments.size(); i++) {
		_sumAngle += _segments[i].angle;
		_points[i+1].x = _points[i].x + cos(_sumAngle) * _segments[i].lenght;
		_points[i+1].y = _points[i].y + sin(_sumAngle) * _segments[i].lenght;
	}
}

void RobotArm::adjustAngle(int jointIndex, Vec2 target) {
	const float samplingDistance = 0.01f;
	const float learningRate = 0.5f;

	float originalAngle = _segments[jointIndex].angle;

	float error = Vec2::distance(target, _points.back()); //Evaluate the current distance between target and foot (last joint);

	_segments[jointIndex].angle += samplingDistance; //Tempoarily move the angle to test if we're getting closer
	updatePoints();

	float errorPlusDelta = Vec2::distance(target, _points.back()); //Re-evaluate the foot/target distance after mooving
	
	//Estimate gradient (slope)
	float gradient = (errorPlusDelta - error) / samplingDistance;
	//If gradient > 0: The error increased we are going in the wrong direction
	//If gradient < 0: The error decreased we are going in the right direction
	
	
	_segments[jointIndex].angle = originalAngle; //restore
	_segments[jointIndex].angle -= learningRate * gradient; 
	//If gradient > 0: substracting it reverses the move (go in the other direction)
	//If gradient < 0: substraction it amplifies the move;
	
	updatePoints();
}

//////////////////////////////////////////////////////////
//						RENDER							//
//////////////////////////////////////////////////////////

void RobotArm::printRobotArm(std::vector<unsigned char> &pixels) {
	_printRoundPoints(pixels);	
		for (size_t i = 0; i < _segments.size(); ++i) {
		_printSegments(_points[i], _points[i + 1], pixels);
	}
}

void RobotArm::_printRoundPoints(std::vector<unsigned char> &pixels) {
	for (size_t nbr = 0; nbr < _segments.size() + 1; ++nbr) {
        float radius = globals::DOT_SIZE / 2.0f;

        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                float dx = x;
                float dy = y;
                if (dx * dx + dy * dy <= radius * radius) {
                    int px = _points[nbr].x + x;
                    int py = _points[nbr].y + y;
                    if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
                        int i = (py * globals::WIDTH + px) * 4;
                        pixels[i + 0] = 255;
                        pixels[i + 1] = 255;
                        pixels[i + 2] = 255;
                        pixels[i + 3] = 255;
                    }
                }
            }
        }
    }
}

void RobotArm::_printSegments(Vec2 &a, const Vec2 &b, std::vector<unsigned char>& pixels) {
    const int steps = 100;

    float ax = a.x;
    float ay = a.y;
    float bx = b.x;
    float by = b.y;

    for (int i = 0; i <= steps; i++) { //draw steps time in between squares
        float t = i / (float)steps; // Goes from 0 to 1
        float x = ax * (1 - t) + bx * t;
        float y = ay * (1 - t) + by * t;

        for (int j = -3; j <= 2; ++j) {
            for (int k = -3; k <= 2; ++k) {
                int px = (int)x + k;
                int py = (int)y + j;
                if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
                    int offset = (py * globals::WIDTH + px) * 4;
                    pixels[offset + 0] = 255;
                    pixels[offset + 1] = 255;
                    pixels[offset + 2] = 255;
                    pixels[offset + 3] = 255;
                }
            }
        }
    }
}
