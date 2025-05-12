/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:02:24 by allan             #+#    #+#             */
/*   Updated: 2025/05/08 16:23:55 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include <iostream>

#include "Globals.hpp"
#include "Knights.hpp"
#include "RobotArm.hpp"

struct Body {
	Vec2 head_start;
	Vec2 head_end;
	Rgba head_color;	

	Vec2 forehead_rec_start;
	Vec2 forehead_rec_end;
	Vec3 forehead_tri;
	Rgba forehead_color;
	
	Vec2 mouth_start;
	Vec2 mouth_end;
	Rgba mouth_color;
	
	Vec3 nose;
	Rgba nose_color;

	Vec2 eye_start;
	float eye_radius;
	Rgba eye_color;
};

class Monster {
	public:
	
		Monster();
		
		//std::string getSomething(void) const;
		//void setSomething(std::string new_value);
		void setBody(Body body, Vec2 new_pos);
		
		void printMonster(GLFWwindow *window, uint8_t *pixels, Vec2 p_pos);
		
		void moveTo(Vec2 new_pos);
		void moveArmTo(Vec2 new_target);
		
	private:
		Body _bodyBase;
		Body _bodyMove;
		RobotArm _topArm;
		RobotArm _bottomArm;
		/* float _x, _y;
		float _mouth_openness;
		float _eye_blink;
		float _jaw_angle;
		float _time; */

};

//std::ostream &operator<<(std::ostream &o, const Monster &i);

#endif