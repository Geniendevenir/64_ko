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
#include "Player.hpp"

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(globals::WIDTH, globals::HEIGHT, "Basics", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();
	glfwSwapInterval(1);


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
	Stage stage(cube);

	std::vector<Star> stars;
	std::vector<Star> stars_reflect;
	initStars(300, stars, stars_reflect);
	//const double frameDuration = 1.0 / 60.0;
	double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
		//60FPS
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
/* 		if (deltaTime < frameDuration) {
			continue;
		} */
		if (deltaTime > 0.05) deltaTime = 0.05;

		float star_scroll = currentTime * 50.0f;

		glfwPollEvents();
		
		//Action / Calcul
		handle_input(&window, cube, stage, deltaTime);	

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
		draw_moonglow(backgroundPixels.data(), {490.0f, 345.0f}, 30.0f, 1.0f);
		drawCircle(backgroundPixels.data(), {490.0f, 345.0f}, 15.0f, {255, 255, 255, 210}); 
		draw_stars(stars, backgroundPixels.data(), star_scroll);
		drawRectangle(backgroundPixels.data(),
		{0 , static_cast<float>(globals::GROUND_HEIGHT)},
		{static_cast<float>(globals::WIDTH), static_cast<float>(globals::GROUND_HEIGHT + 50)},
		{30, 30, 30, 255}); //Background floor
		draw_mountains(backgroundPixels.data(), cube.scroll_x);
		draw_floor(backgroundPixels);
		draw_stars(stars_reflect, backgroundPixels.data(), star_scroll);
		draw_pillars(backgroundPixels, cube.scroll_x);
		
		stage.printUpperStage(backgroundPixels.data());
		stage.centerStage(cube);	
		stage.printStage(stagePixels.data());	
		
		//Monster
		monster.printMonsterReflection(window, monsterPixels.data());
		monster.printMonster(window, monsterPixels.data(), {cube.getPosX(), cube.getPosY()});
		
		draw_crosshair(crossPixels.data(), mx, my);
		draw_number(crossPixels.data(), globals::WIDTH, globals::HEIGHT, mx, 5, globals::HEIGHT - 10, {255, 0, 0, 255});
		draw_number(crossPixels.data(), globals::WIDTH, globals::HEIGHT, my, 50, globals::HEIGHT - 10, {255, 0, 0, 255});
		
		draw_player(playerPixels.data(), cube);
		draw_player_reflection(playerPixels.data(), cube);
		//draw_pixel(playerPixels.data(), {cube.getPosX() + globals::PLAYER_SIZE - 1, cube.getPosY()});
		draw_pixel(playerPixels.data(), {cube.getCenterX(), cube.getCenterY()});
		//draw_pixel(playerPixels.data(), {stage.getUpperStageStart().x, stage.getUpperStageStart().y});
		stage.playBeatMap(stagePixels.data());
		stage.updateArrows({cube.getCenterX(), cube.getCenterY()}, deltaTime); 

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
