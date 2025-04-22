/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 23:02:48 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 00:15:52by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_game.hpp"
#include "Player.hpp"

int main() {
	GLFWwindow* window = NULL;
	
	if (window_init(&window) == ERROR)
		return ERROR;	
	
	Player cube("pacman");
	draw_player(cube);

	gl_texture_setup(cube);
	
	if (game_loop(&window, cube) == ERROR) {
		clean_window(&window);
		return ERROR;
	}

	clean_window(&window);
	return SUCCESS;	
}