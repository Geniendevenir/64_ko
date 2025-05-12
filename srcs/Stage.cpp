/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:50:01 by allan             #+#    #+#             */
/*   Updated: 2025/05/11 21:12:43 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stage.hpp"

//////////////////////////////////////////////////////////
//				 CONSTRUCTOR/DESTRUCTOR					//
//////////////////////////////////////////////////////////

Stage::Stage() {
	_scene.rec_top_start = {static_cast<float>((globals::WIDTH / 2) - 50), 0.0f};
	_scene.rec_top_end = {static_cast<float>((globals::WIDTH / 2) + 50), static_cast<float>(globals::HEIGHT)};
	_scene.rec_top_color = {161, 180, 200, 255};
	
	_scene.rec_right_start = {0.0f, static_cast<float>(globals::GROUND_HEIGHT - 50)};
	_scene.rec_right_end = {static_cast<float>(globals::WIDTH), static_cast<float>(globals::GROUND_HEIGHT + 50)};
	_scene.rec_right_color= {161, 180, 200, 255};


	_middle.rec_top_start = {static_cast<float>((globals::WIDTH / 2) - 30), 0.0f};
	_middle.rec_top_end = {static_cast<float>((globals::WIDTH / 2) + 30), static_cast<float>(globals::HEIGHT)};
	_middle.rec_top_color = {150, 0, 0, 200};
	
	_middle.rec_right_start = {0.0f, static_cast<float>(globals::GROUND_HEIGHT - 30)};
	_middle.rec_right_end = {static_cast<float>(globals::WIDTH), static_cast<float>(globals::GROUND_HEIGHT + 30)};
	_middle.rec_right_color= {150, 0, 0, 200};

	return ;
}



//////////////////////////////////////////////////////////
//					OVERLOADED OPERATOR					//
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//					 GETTER/SETTER						//
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//						 ACTION							//
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//						 RENDER							//
//////////////////////////////////////////////////////////

void Stage::printStage(uint8_t *pixels) {
	drawRectangle(pixels, _scene.rec_top_start, _scene.rec_top_end, _scene.rec_top_color);
	drawRectangle(pixels, _scene.rec_right_start, _scene.rec_right_end, _scene.rec_right_color);


	drawRectangle(pixels, _middle.rec_top_start, _middle.rec_top_end, _middle.rec_top_color);
	drawRectangle(pixels, _middle.rec_right_start, _middle.rec_right_end, _middle.rec_right_color);
}
