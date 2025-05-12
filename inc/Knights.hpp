/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Knights.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:45:32 by allan             #+#    #+#             */
/*   Updated: 2025/05/12 16:54:16 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KNIGHTS_HPP
#define KNIGHTS_HPP

#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>

#include "Player.hpp"
#include "Globals.hpp"

struct Star {
	float x, y;
	float parallax; // 0.1 = slow stars, 1.0 = near stars
};


typedef std::vector<unsigned char> c_vector;

void handle_input(GLFWwindow** window, Player &player);

//Print
void draw_background(c_vector &pixels);
void initStars(int count, std::vector<Star> &stars ,std::vector<Star> &stars_reflect);
void draw_stars(std::vector<Star>& stars, uint8_t* pixels, float scroll_x);
void draw_moon(c_vector &pixels);
void draw_moonglow(uint8_t* pixels, Vec2 center, float radius, float intensity);
void draw_mountains(uint8_t* pixels, float scroll_x);
void draw_floor(c_vector &pixels);
void draw_pillars(c_vector &pixels, float scroll_x);
void draw_player(uint8_t *pixels, const Player &player);
void draw_player_reflection(uint8_t* pixels, const Player& player);
void drawRectangle(uint8_t *pixels, Vec2 start, Vec2 end, Rgba color);
void drawCircle(uint8_t *pixels, Vec2 start, float radius, Rgba color);
int	edge(Vec2 v1, Vec2 v2, Vec2 v3); 
void drawTriangle(uint8_t *pixels, Vec3 p, Rgba color);

//Mouse
void draw_crosshair(uint8_t* pixels, int x, int y);
void draw_digit(uint8_t* pixels, int width, int height, int digit, int x, int y, Rgba color);
void draw_number(uint8_t* pixels, int width, int height, int number, int x, int y, Rgba color);

//Render
void drawFullScreenQuad();

#endif