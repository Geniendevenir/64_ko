/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:47:34 by allan             #+#    #+#             */
/*   Updated: 2025/05/07 16:34:16by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Globals.hpp"
#include "Knights.hpp"

void draw_background(c_vector &pixels) {
	for (int y = 0; y < globals::HEIGHT; ++y) {
		for (int x = 0; x < globals::WIDTH; ++x) {
				int i = (y * globals::WIDTH + x) * 4;
				pixels[i + 0] = 0; //Red
				pixels[i + 1] = 0; //Green
				pixels[i + 2] = 0; //Blue
				pixels[i + 3] = 255; //Alpha
		}
	}
	return ; 
}

void initStars(int count, std::vector<Star> &stars) {
	//int top_start = globals::HEIGHT * 2 / 3;
	//int top_end = globals::HEIGHT;
	stars.clear();
	for (int i = 0; i < count; ++i) {
		Star s;
		s.x = static_cast<float>(rand() % 4000); // world width
		//s.y = static_cast<float>(top_start + rand() % (top_end - top_start)); //Version A: upper half of screen
		s.y = static_cast<float>(rand() % globals::HEIGHT);// Version B: all the screen
		s.parallax = 0.1f + (rand() % 100) / 300.0f; // range 0.1–0.4
		stars.push_back(s);
	}
}

void draw_stars(std::vector<Star>& stars, uint8_t* pixels, float scroll_x) {
	for (const Star& s : stars) {
		float screen_x = s.x - scroll_x * s.parallax;
		int x = static_cast<int>(screen_x) % globals::WIDTH;
		if (x < 0) x += globals::WIDTH;

		int y = static_cast<int>(s.y);
		if (x >= 0 && x < globals::WIDTH && y >= 0 && y < globals::HEIGHT) {
			int i = (y * globals::WIDTH + x) * 4;
			pixels[i + 0] = 255;
			pixels[i + 1] = 255;
			pixels[i + 2] = 255;
			pixels[i + 3] = 255;
		}
	}
}

/* void draw_mountains(uint8_t* pixels, float scroll_x) {
	const float parallax = 0.1f;
	const int base_y = globals::GROUND_HEIGHT;  // where mountains start

	float mountain_scroll = scroll_x * parallax;

	const int peak_height = 150;
	const int mountain_width = 250;

	float screen_x = (globals::WIDTH / 4) - mountain_scroll;
	int x0 = static_cast<int>(screen_x);
	int x1 = x0 + mountain_width;

	int peak_x = x0 + mountain_width / 2;
	int peak_y = base_y + peak_height;

	Vec2 base_left = {static_cast<float>(x0), static_cast<float>(base_y)};
	Vec2 base_right = {static_cast<float>(x1), static_cast<float>(base_y)};
	Vec2 base_top = {static_cast<float>(peak_x), static_cast<float>(peak_y)};

	Vec2 tip_left = {static_cast<float>(x0 * 1.5), static_cast<float>(base_y)};
	Vec2 tip_right = {static_cast<float>(x1 * 0.5), static_cast<float>(base_y)};

	Vec2 tip_top = base_top; 

	drawTriangle(pixels, {base_left, base_top, base_right}, {10, 10, 10, 255}); // dark gray mountains
	drawTriangle(pixels, {tip_left, tip_top, tip_right}, {0, 0, 0, 255}); // dark gray mountains
} */

void draw_mountains(uint8_t* pixels, float scroll_x) {

	float parallax = 0.1f;
	float mountain_scroll = scroll_x * parallax;
	
	int base_x     = 300;   // left edge of mountain
	int base_y     = globals::GROUND_HEIGHT + 50; //starts at background floor
	int width      = 200;   // total mountain width
	int height     = 100;   // full mountain height
	int tip_width  = 40;    // width of the flat gap at the tip

	int tip_y      = base_y + height;

 	int left_x     = base_x - mountain_scroll;
	int right_x    = (base_x + width) - mountain_scroll;

	int gap_left   = (base_x + (width - tip_width) / 2) - mountain_scroll;
	int gap_right  = (gap_left + tip_width);

	drawTriangle(
		pixels,
		{	{static_cast<float>(left_x), static_cast<float>(base_y)},
			{static_cast<float>(gap_left), static_cast<float>(tip_y)},
			{static_cast<float>((gap_left + gap_right) / 2.0f), static_cast<float>(base_y)}
		},
		{10, 10, 10, 255});

	drawTriangle(
		pixels,
		{ 
			{static_cast<float>(gap_right),  static_cast<float>(tip_y)},//
			{static_cast<float>(right_x),    static_cast<float>(base_y)},
			{static_cast<float>((gap_left + gap_right) / 2.0f), static_cast<float>(base_y)}
		},
		{10, 10, 10, 255});

	drawTriangle(
    	pixels,
    	{ 
			{static_cast<float>((gap_left + gap_right) / 2.0f), static_cast<float>(base_y)},
    		{static_cast<float>(gap_left),   static_cast<float>(tip_y)},
    		{static_cast<float>(gap_right),  static_cast<float>(tip_y)}//
    	},
    	{10, 10, 10, 255});
}



void draw_floor(c_vector &pixels) {
	for (int y = 0; y < globals::GROUND_HEIGHT; ++y) {
		for (int x = 0; x < globals::WIDTH; ++x) {
				int i = (y * globals::WIDTH + x) * 4;
				pixels[i + 0] = 80; //Red
				pixels[i + 1] = 80; //Green
				pixels[i + 2] = 80; //Blue
				pixels[i + 3] = 255; //Alpha
		}
	}
	return ; 
}

void draw_pillars(c_vector &pixels, float scroll_x) {
	const int p_height = globals::HEIGHT * 0.8;
	const int pillar_thickness = 40;
	const int pillar_spacing = 100;

	// Loop through all possible visible pillars, including a bit off-screen for smooth entry
	int start_x = static_cast<int>(scroll_x) - (static_cast<int>(scroll_x) % pillar_spacing) - pillar_spacing;

	for (int x = start_x; x < scroll_x + globals::WIDTH; x += pillar_spacing) {
		int screen_x_start = static_cast<int>(x - scroll_x);
		int screen_x_end = screen_x_start + pillar_thickness;

		// Skip if entirely off-screen
		if (screen_x_end <= 0 || screen_x_start >= globals::WIDTH)
			continue;

		// Clamp within screen bounds
		int draw_x_start = std::max(0, screen_x_start);
		int draw_x_end = std::min(globals::WIDTH, screen_x_end);

		Vec2 shade1_top_left = {static_cast<float>(draw_x_start), static_cast<float>(globals::GROUND_HEIGHT)};
		Vec2 shade1_top_right = {static_cast<float>(draw_x_end), static_cast<float>(globals::GROUND_HEIGHT)};
		Vec2 shade1_bot_left = {static_cast<float>(draw_x_start - 50), 0.0f};
		drawTriangle(pixels.data(), {shade1_top_left, shade1_bot_left, shade1_top_right}, {100, 100, 100, 230});
		Vec2 shade2_bot_left = shade1_bot_left;
		Vec2 shade2_top_right = shade1_top_right;
		Vec2 shade2_bot_right = {static_cast<float>(draw_x_end - 50), 0.0f};
		drawTriangle(pixels.data(), {shade2_bot_left, shade2_bot_right, shade2_top_right}, {100, 100, 100, 230});

		for (int y = globals::GROUND_HEIGHT; y < p_height; ++y) {
			for (int x_draw = draw_x_start; x_draw < draw_x_end; ++x_draw) {
				
				int i = (y * globals::WIDTH + x_draw) * 4;
			 	pixels[i + 0] = 100;
				pixels[i + 1] = 100;
				pixels[i + 2] = 100;
				pixels[i + 3] = 255;
			}
		}
	}
}


void draw_player(uint8_t *pixels, const Player &player) {
	
	for (int y = 0; y < globals::PLAYER_SIZE; ++y) {
		for (int x = 0; x < globals::PLAYER_SIZE; ++x) {
			int px = static_cast<int>(player.getPosX()) + x;
			int py = static_cast<int>(player.getPosY()) + y;
			if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
				int i = (py * globals::WIDTH + px) * 4;
				pixels[i + 0] = 255; //Red
				pixels[i + 1] = 0; //Green
				pixels[i + 2] = 0; //Blue
				pixels[i + 3] = 255; //Alpha
			}
		}
	}
}

//Draw Basics Shapes

void drawRectangle(uint8_t *pixels, Vec2 start, Vec2 end, Rgba color) {
	for (int y = start.y; y < end.y; y++) {
		for (int x = start.x; x < end.x; x++) {
			if (x >= 0 && x < globals::WIDTH && y >= 0 && y < globals::HEIGHT) {
				int i = (y * globals::WIDTH + x) * 4;
				pixels[i + 0] = color.r; //Red
				pixels[i + 1] = color.g; //Green
				pixels[i + 2] = color.b; //Blue
				pixels[i + 3] = color.a; //Alpha
			}
		}
	}
}

void drawCircle(uint8_t *pixels, Vec2 start, float radius, Rgba color) {
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                float dx = x;
                float dy = y;
                if (dx * dx + dy * dy <= radius * radius) {
                    int px = start.x + x;
                    int py = start.y + y;
                    if (px >= 0 && px < globals::WIDTH && py >= 0 && py < globals::HEIGHT) {
                        int i = (py * globals::WIDTH + px) * 4;
                        pixels[i + 0] = color.r;
                        pixels[i + 1] = color.g;
                        pixels[i + 2] = color.b;
                        pixels[i + 3] = color.a;
                    }
                }
            }
        }
}

void drawTriangle(uint8_t* pixels, Vec3 p, Rgba color) {
    auto edge = [](float x0, float y0, float x1, float y1, float px, float py) -> float {
        return (px - x0) * (y1 - y0) - (py - y0) * (x1 - x0);
    };

    int min_x = std::max(0, (int)std::floor(std::min({p.v1.x, p.v2.x, p.v3.x})));
    int max_x = std::min(globals::WIDTH - 1, (int)std::ceil(std::max({p.v1.x, p.v2.x, p.v3.x})));
    int min_y = std::max(0, (int)std::floor(std::min({p.v1.y, p.v2.y, p.v3.y})));
    int max_y = std::min(globals::HEIGHT - 1, (int)std::ceil(std::max({p.v1.y, p.v2.y, p.v3.y})));

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float w0 = edge(p.v2.x, p.v2.y, p.v3.x, p.v3.y, px, py);
            float w1 = edge(p.v3.x, p.v3.y, p.v1.x, p.v1.y, px, py);
            float w2 = edge(p.v1.x, p.v1.y, p.v2.x, p.v2.y, px, py);

            // Accept all pixels where all 3 edge functions have the same sign
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                int i = (y * globals::WIDTH + x) * 4;
                pixels[i + 0] = color.r;
                pixels[i + 1] = color.g;
                pixels[i + 2] = color.b;
                pixels[i + 3] = color.a;
            }
        }
    }
}


void draw_crosshair(uint8_t* pixels, int x, int y) {
	for (int dx = -3; dx <= 3; ++dx) {
		int xx = x + dx;
		if (xx >= 0 && xx < globals::WIDTH && y >= 0 && y < globals::HEIGHT) {
			int i = (y * globals::WIDTH + xx) * 4;
			pixels[i + 0] = 255;
			pixels[i + 1] = 0;
			pixels[i + 2] = 0;
			pixels[i + 3] = 255;
		}
	}
	for (int dy = -3; dy <= 3; ++dy) {
		int yy = y + dy;
		if (x >= 0 && x < globals::WIDTH && yy >= 0 && yy < globals::HEIGHT) {
			int i = (yy * globals::WIDTH + x) * 4;
			pixels[i + 0] = 255;
			pixels[i + 1] = 0;
			pixels[i + 2] = 0;
			pixels[i + 3] = 255;
		}
	}
}

const int digit_width = 3;
const int digit_height = 5;

const uint8_t digit_font[10][digit_height][digit_width] = {
    {{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}}, // 0
    {{1,1,1},{0,1,0},{0,1,0},{1,1,0},{0,1,0}}, // 1
    {{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}}, // 2
    {{1,1,1},{0,0,1},{0,1,1},{0,0,1},{1,1,1}}, // 3
    {{0,0,1},{0,0,1},{1,1,1},{1,0,1},{1,0,1}}, // 4
    {{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}}, // 5
    {{1,1,1},{1,0,1},{1,1,1},{1,0,0},{1,1,1}}, // 6
    {{0,1,0},{0,1,0},{0,1,0},{0,0,1},{1,1,1}}, // 7
    {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}}, // 8
    {{1,1,1},{0,0,1},{1,1,1},{1,0,1},{1,1,1}}, // 9
};

void draw_digit(uint8_t* pixels, int width, int height, int digit, int x, int y, Rgba color) {
    if (digit < 0 || digit > 9) return;

    for (int dy = 0; dy < digit_height; ++dy) {
        for (int dx = 0; dx < digit_width; ++dx) {
            if (digit_font[digit][dy][dx]) {
                int px = x + dx;
                int py = y + dy;
                if (px >= 0 && px < width && py >= 0 && py < height) {
                    int i = (py * width + px) * 4;
                    pixels[i + 0] = color.r;
                    pixels[i + 1] = color.g;
                    pixels[i + 2] = color.b;
                    pixels[i + 3] = 255;
                }
            }
        }
    }
}

void draw_number(uint8_t* pixels, int width, int height, int number, int x, int y, Rgba color) {
    std::string digits = std::to_string(number);
    for (size_t i = 0; i < digits.size(); ++i) {
        int d = digits[i] - '0';
        draw_digit(pixels, width, height, d, x + i * (digit_width + 1), y, color);
    }
}

