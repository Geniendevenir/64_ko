/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:44:03 by allan             #+#    #+#             */
/*   Updated: 2025/05/13 19:30:44by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAGE_HPP
#define STAGE_HPP

#include <string>
#include <iostream>
#include <vector>

#include "Globals.hpp"

class Player;

struct scene {
	Vec2 rec_top_start;
	Vec2 rec_top_end;
	Rgba rec_top_color;
	
	Vec2 rec_right_start;
	Vec2 rec_right_end;
	Rgba rec_right_color;
};

struct Rec {
	Vec2 start;
	Vec2 end;
	Rgba color;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Arrow {
    Vec2 position;
    Direction dir;
    float speed;
    bool active;
};


class Stage {
	public:
		Stage(const Player &player);
		
		void centerStage(const Player &player);
		Vec2 getUpperStageStart() const;
		Vec2 getUpperStageEnd() const;
		float getUpperStageY() const;
		
		void printStage(uint8_t *pixels);
		void printUpperStage(uint8_t *pixels);
		
		void spawnArrow(Direction dir, const Vec2& playerCenter);
		void updateArrows(const Vec2& playerCenter, float deltaTime);
		void playBeatMap(uint8_t* pixels);

	private:
		scene _scene;		
		scene _middle;
		Rec _upper_scene;
		int _upperLineToDraw;
		int _upperLineDrawn;
		std::vector<Arrow> _arrows;
};

void drawArrow(uint8_t* pixels, const Arrow& arrow);

#endif