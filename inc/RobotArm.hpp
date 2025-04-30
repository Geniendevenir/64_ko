/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotArm.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:16:13 by allan             #+#    #+#             */
/*   Updated: 2025/04/26 17:58:27 by allan            ###   ########.fr       */
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

struct Vec2 {
    float x, y;
	static float distance(Vec2 a, Vec2 b);
};

struct Segment {
	float lenght;
	float angle; //in radians
};

class RobotArm {
	public:
		RobotArm();
		RobotArm(std::string name, Vec2 base, std::vector<Segment> segments);
		RobotArm(const RobotArm &src);
		~RobotArm();

		RobotArm &operator=(const RobotArm &rhs);
		
		int getPointsNbr(void) const;
		Vec2 getBase() const;
		Vec2 getPoint(int i) const;
		Segment getSegment(size_t i) const;
		void setSomething(std::string new_value);
		
		void inverseKinematics();
		void moveArms(GLFWwindow **window, float currentTime);
		void updatePoints();
		void printRobotArm(std::vector<unsigned char> &pixels);
		void adjustAngle(int jointIndex, Vec2 target);
		
	private:
		std::string _name;
		float _sumAngle;
		Vec2 _base;
		std::vector<Vec2> _points;
		std::vector<Segment> _segments;
		Vec2 _target;	

		float _lastInputTime;
		const float _inputCooldown = 0.1f;
		
		void _printRoundPoints(std::vector<unsigned char> &pixels);
		void _printSegments(Vec2 &a, const Vec2 &b, std::vector<unsigned char>& pixels);

		
};

std::ostream &operator<<(std::ostream &o, const RobotArm &i);

#endif