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

void draw_player(Player &player) {

	for (int y = 0; y < SQUARE_SIZE; ++y) {
		for (int x = 0; x < SQUARE_SIZE; ++x) {
			int px = player.getPosX() + x;
			int py = player.getPosY() + y;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
				int i = (py * WIDTH + px) * 4;
				player.pixels[i + 0] = 255; //Red
				player.pixels[i + 1] = 255; //Green
				player.pixels[i + 2] = 255; //Blue
				player.pixels[i + 3] = 255; //Alpha
			}
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