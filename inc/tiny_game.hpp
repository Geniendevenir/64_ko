/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_game.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 23:02:41 by allan             #+#    #+#             */
/*   Updated: 2025/04/23 01:12:45 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>

#include "global.hpp"
#include "Player.hpp"


//error_manamgment
void error_callback(int error, const char* description);

//windows_managment
void clean_window(GLFWwindow** window);
int	window_init(GLFWwindow** window);

//texture
void draw_player(Player &player);
void gl_texture_setup(Player &player);

//render
int game_loop(GLFWwindow** window, Player &player);

#define ERROR -1
#define SUCCESS 0