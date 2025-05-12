/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allan <allan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 08:47:43 by allan             #+#    #+#             */
/*   Updated: 2025/05/07 16:41:04by allan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Globals.hpp"
#include "Knights.hpp"
#include "Monster.hpp"
#include "Stage.hpp"

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(globals::WIDTH, globals::HEIGHT, "Basics", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    GLuint backgroundTex, playerTex, monsterTex, stageTex, crossTex;
    glGenTextures(1, &backgroundTex);
    glBindTexture(GL_TEXTURE_2D, backgroundTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &monsterTex);
    glBindTexture(GL_TEXTURE_2D, monsterTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &stageTex);
    glBindTexture(GL_TEXTURE_2D, stageTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &playerTex);
    glBindTexture(GL_TEXTURE_2D, playerTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenTextures(1, &crossTex);
    glBindTexture(GL_TEXTURE_2D, crossTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	std::vector<unsigned char> backgroundPixels(globals::WIDTH * globals::HEIGHT * 4);
	std::vector<unsigned char> monsterPixels(globals::WIDTH * globals::HEIGHT * 4);
	std::vector<unsigned char> stagePixels(globals::WIDTH * globals::HEIGHT * 4);
	std::vector<unsigned char> playerPixels(globals::WIDTH * globals::HEIGHT * 4);
	std::vector<unsigned char> crossPixels(globals::WIDTH * globals::HEIGHT * 4);

	Player cube("pacman");
	Monster monster;
	Stage stage;

	std::vector<Star> stars;
	initStars(300, stars);
	const double frameDuration = 1.0 / 60.0;
	double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
		//60FPS
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		if (deltaTime < frameDuration) {
			continue;
		}
		float star_scroll = currentTime * 50.0f;

		glfwPollEvents();
		
		//Action / Calcul
		handle_input(&window, cube);	

		//Mousse cursor
		double mouse_x, mouse_y;
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
		int mx = static_cast<int>(mouse_x);
		int my = globals::HEIGHT - static_cast<int>(mouse_y); // Flip Y axis

		float t = glfwGetTime();
		float x = (globals::WIDTH - 200) + std::sin(t) * 50;
		float y = globals::GROUND_HEIGHT;

		//Move Monster Target
		monster.moveTo({x, y});
		//monster.moveArmTo({cube.getPosX(), cube.getPosY()});	
		
        // Clear screen
        std::memset(backgroundPixels.data(), 0, backgroundPixels.size());
        std::memset(monsterPixels.data(), 0, monsterPixels.size());
        std::memset(stagePixels.data(), 0, stagePixels.size());
        std::memset(playerPixels.data(), 0, playerPixels.size());
        std::memset(crossPixels.data(), 0, crossPixels.size());
		
		
		//Print
		draw_background(backgroundPixels);
		draw_stars(stars, backgroundPixels.data(), star_scroll);
		drawRectangle(backgroundPixels.data(),
			{0 , static_cast<float>(globals::GROUND_HEIGHT)},
			{static_cast<float>(globals::WIDTH), static_cast<float>(globals::GROUND_HEIGHT + 50)},
			{10, 10, 10, 255}); //Background floor
		draw_mountains(backgroundPixels.data(), cube.scroll_x);
		draw_floor(backgroundPixels);
		draw_pillars(backgroundPixels, cube.scroll_x);


		//stage.printStage(stagePixels.data());	
		
		//Monster
		monster.printMonster(window, monsterPixels.data(), {cube.getPosX(), cube.getPosY()});
		
		draw_crosshair(crossPixels.data(), mx, my);
		draw_number(crossPixels.data(), globals::WIDTH, globals::HEIGHT, mx, 5, globals::HEIGHT - 10, {255, 0, 0, 255});
		draw_number(crossPixels.data(), globals::WIDTH, globals::HEIGHT, my, 50, globals::HEIGHT - 10, {255, 0, 0, 255});
		
		draw_player(playerPixels.data(), cube);


        // Upload to GPU
        glBindTexture(GL_TEXTURE_2D, backgroundTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundPixels.data());

        glBindTexture(GL_TEXTURE_2D, monsterTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, monsterPixels.data());
		
        glBindTexture(GL_TEXTURE_2D, playerTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, playerPixels.data());

        glBindTexture(GL_TEXTURE_2D, stageTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, stagePixels.data());

        glBindTexture(GL_TEXTURE_2D, crossTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, globals::WIDTH, globals::HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, crossPixels.data());


        // Draw
        int winW, winH;
        glfwGetFramebufferSize(window, &winW, &winH);
        glViewport(0, 0, winW, winH);

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, backgroundTex);
		drawFullScreenQuad();

        glBindTexture(GL_TEXTURE_2D, stageTex);
		drawFullScreenQuad();

        glBindTexture(GL_TEXTURE_2D, monsterTex);
		drawFullScreenQuad();

        glBindTexture(GL_TEXTURE_2D, playerTex);
		drawFullScreenQuad();
		
        glBindTexture(GL_TEXTURE_2D, crossTex);
		drawFullScreenQuad();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
