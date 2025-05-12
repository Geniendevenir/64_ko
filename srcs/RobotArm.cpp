/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotArm.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:23:56 by allan             #+#    #+#             */
/*   Updated: 2025/05/08 15:27:05 by allan            ###   ########.fr       */
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
	_desiredTarget = _target;
	_lastInputTime = 0.0f;
	return ;
}


RobotArm::RobotArm(std::string name, Vec2 base, std::vector<Segment> segments) : _name(name), _sumAngle(0), _base(base), _segments(segments) {
	_points.resize(_segments.size() + 1);
	_points[0] = base;
	updatePoints();
	_target = _points.back();
	_desiredTarget = _target;
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

void RobotArm::setDesiredTarget(const Vec2& newTarget) {
	_desiredTarget = newTarget;
}


/* void RobotArm::setSomething(std::string new_value) {
	//if (new_value >= x)
	//this->something = new_value;
	return ;
} */


//////////////////////////////////////////////////////////
//						 ACTION							//
//////////////////////////////////////////////////////////

void RobotArm::moveArms(GLFWwindow *window, float currentTime) {
	if (currentTime - _lastInputTime > _inputCooldown) {
		
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			Vec2 new_target {_target.x, _points.back().y + globals::STEP_SIZE};
			_target = clampTarget(new_target);
			inverseKinematics();
			_lastInputTime = currentTime;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { 
			Vec2 new_target {_points.back().x - globals::STEP_SIZE, _target.y};
			_target = clampTarget(new_target);
			inverseKinematics();
			_lastInputTime = currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { 
			Vec2 new_target {_target.x, _points.back().y - globals::STEP_SIZE};
			_target = clampTarget(new_target);
			inverseKinematics();
			_lastInputTime = currentTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { 
			Vec2 new_target {_points.back().x + globals::STEP_SIZE, _target.y};
			_target = clampTarget(new_target);
			inverseKinematics();
			_lastInputTime = currentTime;
		}
	}
}

void RobotArm::targetPlayer(Vec2 p_pos) {
	setDesiredTarget(p_pos);
	smoothTargetTracking();
	inverseKinematics();
}

void RobotArm::smoothTargetTracking() {
	float smoothing = 0.1f;
	_target.x += (_desiredTarget.x - _target.x) * smoothing;
	_target.y += (_desiredTarget.y - _target.y) * smoothing;

	// Clamp target to max reach
	float maxReach = 0.0f;
	for (const auto& seg : _segments)
		maxReach += seg.length;

	Vec2 toTarget = { _target.x - _points[0].x, _target.y - _points[0].y };
	float dist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

	if (dist > maxReach) {
		float scale = maxReach / dist;
		toTarget.x *= scale;
		toTarget.y *= scale;
		_target.x = _points[0].x + toTarget.x;
		_target.y = _points[0].y + toTarget.y;
	}
}

//Calculate the max distance possible = size of all segments
float RobotArm::getMaxReach() const {
    float total = 0.0f;
    for (const auto& seg : _segments)
        total += seg.length;
    return total;
}

//Clamp the target if its too far/unreachable
Vec2 RobotArm::clampTarget(Vec2 desired) const {
    Vec2 toTarget = { desired.x - _base.x, desired.y - _base.y };
    float d = sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
    float maxReach = getMaxReach();

    if (d > maxReach) {
        float scale = maxReach / d;
        toTarget.x *= scale;
        toTarget.y *= scale;
        return { _base.x + toTarget.x, _base.y + toTarget.y };
    }

    return desired;
}


//////////////////////////////////////////////////////////
//					INVERSE KINEMATICS					//
//////////////////////////////////////////////////////////

void RobotArm::inverseKinematics() {
	const float tolerance = 5.0f;
	int ik_passes = 100000;
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

            float px = _points[i].x + std::cos(_sumAngle) * _segments[i].length;
            float py = _points[i].y + std::sin(_sumAngle) * _segments[i].length;

            if (!std::isfinite(px) || !std::isfinite(py)) {
                std::cerr << "NaN detected in updatePoints! Aborting update.\n";
                return;
            }

            _points[i + 1].x = px;
            _points[i + 1].y = py;
        }
	
/* 	_sumAngle = 0;
	for (size_t i = 0; i < _segments.size(); i++) {
		_sumAngle += _segments[i].angle;
		_points[i+1].x = _points[i].x + cos(_sumAngle) * _segments[i].length;
		_points[i+1].y = _points[i].y + sin(_sumAngle) * _segments[i].length;
	} */
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

void RobotArm::printRobotArm(uint8_t *pixels) {
	_printRoundPoints(pixels);	
	for (size_t i = 0; i < _segments.size(); ++i) {
		_printSegments(_points[i], _points[i + 1], pixels);
	}
	_printTarget(pixels);
}

void RobotArm::_printRoundPoints(uint8_t *pixels) {
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
                        pixels[i + 0] = 100;
                        pixels[i + 1] = 100;
                        pixels[i + 2] = 100;
                        pixels[i + 3] = 255;
                    }
                }
            }
        }
    }
}

void RobotArm::_printSegments(Vec2 &a, const Vec2 &b, uint8_t * pixels) {
    const int steps = 100;

    float ax = a.x;
    float ay = a.y;
    float bx = b.x;
    float by = b.y;

    for (int i = 0; i <= steps; i++) { //draw steps time in between squares
        float t = i / (float)steps; // Goes from 0 to 1
        float x = ax * (1 - t) + bx * t;
        float y = ay * (1 - t) + by * t;

        for (int j = -8; j <= 7; ++j) {
            for (int k = -8; k <= 7; ++k) {
                int px = (int)x + k;
                int py = (int)y + j;
                if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
                    int offset = (py * globals::WIDTH + px) * 4;
                    pixels[offset + 0] = 100;
                    pixels[offset + 1] = 100;
                    pixels[offset + 2] = 100;
                    pixels[offset + 3] = 255;
                }
            }
        }
    }
}

void RobotArm::_printTarget(uint8_t * pixels) {
	const int target_size = 6;
	
    for (int y = -target_size / 2; y <= target_size / 2; ++y) {
    	for (int x = -target_size / 2; x <= target_size / 2; ++x) {
    	    int px = static_cast<int>(_target.x) + x;
    	    int py = static_cast<int>(_target.y) + y;
    	    if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
    	        int offset = (py * globals::WIDTH + px) * 4;
    	        pixels[offset + 0] = 255;
    	        pixels[offset + 1] = 0;
    	        pixels[offset + 2] = 0;
    	        pixels[offset + 3] = 255;
    	    }
    	}
    }
}