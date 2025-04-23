/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:22:14 by allan             #+#    #+#             */
/*   Updated: 2025/04/22 21:27:39by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_game.hpp"
#include "Player.hpp"

void draw_player(Player &player, c_vector &pixels) {

	for (int y = 0; y < globals::PLAYER_SIZE; ++y) {
		for (int x = 0; x < globals::PLAYER_SIZE; ++x) {
			int px = static_cast<int>(player.getPosX()) + x;
			int py = static_cast<int>(player.getPosY()) + y;
			if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
				int i = (py * globals::WIDTH + px) * 4;
				pixels[i + 0] = 255; //Red
				pixels[i + 1] = 255; //Green
				pixels[i + 2] = 255; //Blue
				pixels[i + 3] = 255; //Alpha
			}
		}
	}
	return ; 
}

void draw_floor(c_vector &pixels) {
	for (int y = 0; y < globals::GROUND_Y; ++y) {
		for (int x = 0; x < globals::WIDTH; ++x) {
				int i = (y * globals::WIDTH + x) * 4;
				pixels[i + 0] = 0; //Red
				pixels[i + 1] = 0; //Green
				pixels[i + 2] = 255; //Blue
				pixels[i + 3] = 255; //Alpha
		}
	}
	return ; 
}

void	gl_texture_setup(Player &player) {
	glGenTextures(1, &player.tex);					//Generate a Texture giving it an ID
	glBindTexture(GL_TEXTURE_2D, player.tex);		//Focus our texture as the main subject

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//Re-sizing texture down: pick the nearest texel (no smoothing) 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//Re-sizing texture up: same

}