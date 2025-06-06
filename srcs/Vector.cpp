/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:49:07 by allan             #+#    #+#             */
/*   Updated: 2025/05/08 00:01:55 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Globals.hpp"
#include <cmath>

float Vec2::distance(Vec2 a, Vec2 b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	
	return sqrt(dx * dx + dy * dy);
}

Vec2 offsetVec2(Vec2 v, Vec2 offset) {
	return { v.x + offset.x, v.y + offset.y };
}

Vec3 offsetVec3(Vec3 tri, Vec2 offset) {
	return {
		{ tri.v1.x + offset.x, tri.v1.y + offset.y },
		{ tri.v2.x + offset.x, tri.v2.y + offset.y },
		{ tri.v3.x + offset.x, tri.v3.y + offset.y }
	};
}