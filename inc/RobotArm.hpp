/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotArm.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:16:13 by allan             #+#    #+#             */
/*   Updated: 2025/05/08 15:05:19 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTARM_HPP
#define ROBOTARM_HPP

#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Globals.hpp"


struct Segment {
	float length;
	float angle; //in radians
};

class RobotArm {
	public:
		//Constructor - Destructor
		RobotArm();
		RobotArm(std::string name, Vec2 base, std::vector<Segment> segments);
		RobotArm(const RobotArm &src);
		~RobotArm();

		//Overloaded Operator
		RobotArm &operator=(const RobotArm &rhs);

		//Getter - Setter	
		int getPointsNbr(void) const;
		Vec2 getBase() const;
		Vec2 getPoint(int i) const;
		Segment getSegment(size_t i) const;
		void setSomething(std::string new_value);
		void setDesiredTarget(const Vec2& newTarget);
		
		//Action
		void moveArms(GLFWwindow *window, float currentTime);
		void targetPlayer(Vec2 p_pos);
		void smoothTargetTracking();
		float getMaxReach() const;
		Vec2 clampTarget(Vec2 desired) const;
		
		//Inverse Kinematics Algo
		void inverseKinematics();
		void updatePoints();
		void printRobotArm(uint8_t *pixels);
		void adjustAngle(int jointIndex, Vec2 target);

		
		
	private:
		std::string _name;
		float _sumAngle;
		Vec2 _base;
		std::vector<Vec2> _points;
		std::vector<Segment> _segments;
		Vec2 _target;	
		Vec2 _desiredTarget;

		float _lastInputTime;
		const float _inputCooldown = 0.1f;

		//Render
		void _printRoundPoints(uint8_t *pixels);
		void _printSegments(Vec2 &a, const Vec2 &b, uint8_t * pixels);
		void _printTarget(uint8_t * pixels);

		
};

std::ostream &operator<<(std::ostream &o, const RobotArm &i);

#endif