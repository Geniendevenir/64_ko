/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:50:01 by allan             #+#    #+#             */
/*   Updated: 2025/05/13 19:40:09 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stage.hpp"
#include "Knights.hpp"
#include "Player.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

Stage::Stage(const Player &player) {
	_upper_scene = {
		{ static_cast<float>((globals::WIDTH / 2) - 200), static_cast<float>(globals::GROUND_HEIGHT) },
		{ static_cast<float>((globals::WIDTH / 2) - 100), static_cast<float>(globals::GROUND_HEIGHT + 60) },
		{ 80, 80, 80, 255 }
	};
	_upperLineToDraw = _upper_scene.end.y - _upper_scene.start.y ;
	_upperLineDrawn = 0;
		
	centerStage(player);

	spawnArrow(UP, {player.getCenterX(), player.getCenterY()});
	spawnArrow(DOWN, {player.getCenterX(), player.getCenterY()});
	spawnArrow(RIGHT, {player.getCenterX(), player.getCenterY()});
	spawnArrow(LEFT, {player.getCenterX(), player.getCenterY()});
	return ;
}



//////////////////////////////////////////////////////////
//					OVERLOADED OPERATOR					//
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//					 GETTER/SETTER						//
//////////////////////////////////////////////////////////
Vec2 Stage::getUpperStageStart() const {
	return _upper_scene.start;
}

Vec2 Stage::getUpperStageEnd() const {
	return _upper_scene.end;
}

float Stage::getUpperStageY() const {
	return _upperLineDrawn + globals::GROUND_HEIGHT;
}

void Stage::centerStage(const Player &player) {
	_scene.rec_top_start = {player.getCenterX() - 50, 0.0f};
	_scene.rec_top_end = {player.getCenterX() + 50, static_cast<float>(globals::HEIGHT)};
	_scene.rec_top_color = {161, 180, 200, 255};
	
	_scene.rec_right_start = {0.0f, player.getCenterY() - 50};
	_scene.rec_right_end = {static_cast<float>(globals::WIDTH), player.getCenterY() + 50};
	_scene.rec_right_color= {161, 180, 200, 255};


	_middle.rec_top_start = {player.getCenterX() - 30, 0.0f};
	_middle.rec_top_end = {player.getCenterX() + 30, static_cast<float>(globals::HEIGHT)};
	_middle.rec_top_color = {200, 200, 200, 200};
	
	_middle.rec_right_start ={0.0f, player.getCenterY() - 30};
	_middle.rec_right_end ={static_cast<float>(globals::WIDTH), player.getCenterY() + 30};
	_middle.rec_right_color= {200, 200, 200, 200};
}


//////////////////////////////////////////////////////////
//						 ACTION							//
//////////////////////////////////////////////////////////
void Stage::spawnArrow(Direction dir, const Vec2& playerCenter) {
    Arrow arrow;
    arrow.dir = dir;
    arrow.speed = 300.0f; // You can tune this
    arrow.active = true;

    float offset = 200.0f; // Distance from center to spawn

    switch (dir) {
        case UP:
            arrow.position = {playerCenter.x, playerCenter.y + offset};
            break;
        case DOWN:
            arrow.position = {playerCenter.x, playerCenter.y - offset};
            break;
        case LEFT:
            arrow.position = {playerCenter.x - offset, playerCenter.y};
            break;
        case RIGHT:
            arrow.position = {playerCenter.x + offset, playerCenter.y};
            break;
    }
    _arrows.push_back(arrow);
}

void Stage::playBeatMap(uint8_t* pixels) {
	for (const auto& arrow : _arrows)
		if (arrow.active)
			drawArrow(pixels, arrow);
}


void Stage::updateArrows(const Vec2& playerCenter, float deltaTime) {
    for (auto& arrow : _arrows) {
        if (!arrow.active) continue;

        Vec2 dirVec;

        switch (arrow.dir) {
            case UP:    dirVec = {0, -1}; break;
            case DOWN:  dirVec = {0, 1}; break;
            case RIGHT:  dirVec = {-1, 0}; break;
            case LEFT: dirVec = {1, 0}; break;
        }

        arrow.position.x += dirVec.x * arrow.speed * deltaTime;
        arrow.position.y += dirVec.y * arrow.speed * deltaTime;

        // Optional: deactivate when close to player
        float distance = std::sqrt(
            (arrow.position.x - playerCenter.x) * (arrow.position.x - playerCenter.x) +
            (arrow.position.y - playerCenter.y) * (arrow.position.y - playerCenter.y)
        );
        if (distance < 10.0f) {
            arrow.active = false;
            // Check for hit/miss here
        }
    }
}

void drawArrow(uint8_t* pixels, const Arrow& arrow) {
    Rgba color = {0, 0, 255, 255};

    Vec2 tip = arrow.position;
    Vec2 base1, base2;

    float size = 10.0f;

    switch (arrow.dir) {
        case UP:
            base1 = {tip.x - size, tip.y + size * 2};
            base2 = {tip.x + size, tip.y + size * 2};
            break;
        case DOWN:
            base1 = {tip.x - size, tip.y - size * 2};
            base2 = {tip.x + size, tip.y - size * 2};
            break;
        case RIGHT:
            base1 = {tip.x + size * 2, tip.y - size};
            base2 = {tip.x + size * 2, tip.y + size};
            break;
        case LEFT:
            base1 = {tip.x - size * 2, tip.y - size};
            base2 = {tip.x - size * 2, tip.y + size};
            break;
    }

    drawTriangle(pixels, {tip, base1, base2}, color);
}



//////////////////////////////////////////////////////////
//						 RENDER							//
//////////////////////////////////////////////////////////

void Stage::printStage(uint8_t *pixels) {
	drawRectangle(pixels, _scene.rec_top_start, _scene.rec_top_end, _scene.rec_top_color);
	drawRectangle(pixels, _scene.rec_right_start, _scene.rec_right_end, _scene.rec_right_color);


	drawRectangle(pixels, _middle.rec_top_start, _middle.rec_top_end, _middle.rec_top_color);
	drawRectangle(pixels, _middle.rec_right_start, _middle.rec_right_end, _middle.rec_right_color);
}

void Stage::printUpperStage(uint8_t *pixels) {
		if (_upperLineDrawn <= _upperLineToDraw) {
			int y = _upperLineDrawn + globals::GROUND_HEIGHT;
			for (int prev_y = globals::GROUND_HEIGHT; prev_y < y; ++prev_y) {
				for (int x = _upper_scene.start.x; x < _upper_scene.end.x; ++x) {
					if (x >= 0 && x < globals::WIDTH && prev_y >= 0 && prev_y < globals::HEIGHT) {
						int i = (prev_y * globals::WIDTH + x) * 4;
						pixels[i + 0] = _upper_scene.color.r; //Red
						pixels[i + 1] = _upper_scene.color.g; //Green
						pixels[i + 2] = _upper_scene.color.b; //Blue
						pixels[i + 3] = _upper_scene.color.a; //Alpha
					}
				}
			}
			_upperLineDrawn++;
		}
		else {
			//Little problem with the y value (had to add extra two lines)
			drawRectangle(pixels, _upper_scene.start, { _upper_scene.end.x, _upper_scene.end.y}, _upper_scene.color);
		}
}
