/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stage.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:44:03 by allan             #+#    #+#             */
/*   Updated: 2025/05/11 20:55:48 by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAGE_HPP
#define STAGE_HPP

#include <string>
#include <iostream>

#include "Globals.hpp"
#include "Knights.hpp"

struct scene {
	Vec2 rec_top_start;
	Vec2 rec_top_end;
	Rgba rec_top_color;
	
	Vec2 rec_right_start;
	Vec2 rec_right_end;
	Rgba rec_right_color;
};

class Stage {
	public:
		Stage();
		
		void printStage(uint8_t *pixels);

	private:
		scene _scene;		
		scene _middle;
};

#endif