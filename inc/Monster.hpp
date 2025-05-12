/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:02:24 by allan             #+#    #+#             */
/*   Updated: 2025/05/12 19:38:55 by adebert          ###   ########.fr       */
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

struct Health {
	Vec2 big_rec_start;
	Vec2 big_rec_end;
	Rgba big_rec_color;

	Vec2 small_rec_start;
	Vec2 small_rec_end;
	Rgba small_rec_color;
};

class Monster {
	public:
	
		Monster();
		
		//std::string getSomething(void) const;
		//void setSomething(std::string new_value);
		void setBody(Body body, Vec2 new_pos);
		
		void printMonster(GLFWwindow *window, uint8_t *pixels, Vec2 p_pos);
		void printMonsterReflection(GLFWwindow* window, uint8_t* pixels);
		
		void moveTo(Vec2 new_pos);
		void moveArmTo(Vec2 new_target);
		
	private:
		Body _bodyBase;
		Body _bodyMove;
		RobotArm _topArm;
		RobotArm _bottomArm;
		Health _healthBase;
		Health _healthMove;
		/* float _x, _y;
		float _mouth_openness;
		float _eye_blink;
		float _jaw_angle;
		float _time; */

};

//std::ostream &operator<<(std::ostream &o, const Monster &i);

#endif