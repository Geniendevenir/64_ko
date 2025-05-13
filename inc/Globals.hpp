/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Globals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebert <adebert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:28:31 by allan             #+#    #+#             */
/*   Updated: 2025/05/13 19:53:13 by adebert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

namespace globals {
	extern const int WIDTH;
	extern const int HEIGHT;
	extern const int DOT_SIZE;
	extern const float DOT_DIST;
	extern const int DOT_NBR;
	extern const float STEP_SIZE;
	extern const int GROUND_HEIGHT;
	extern const int PLAYER_SIZE;
}

struct Vec2 {
    float x, y;
	static float distance(Vec2 a, Vec2 b);
};


//For Triangle Vertices
struct Vec3 {
	Vec2 v1;
	Vec2 v2;
	Vec2 v3;
};

Vec2 offsetVec2(Vec2 v, Vec2 offset);
Vec3 offsetVec3(Vec3 tri, Vec2 offset);


struct Rgba {
	int r;
	int g;
	int b;
	int a;
};

struct Star {
	float x, y;
	float parallax; // 0.1 = slow stars, 1.0 = near stars
};

enum GamePhase {
	INTRO,
	PILLARS,
	MONSTER,
	FIGHT
};

#endif