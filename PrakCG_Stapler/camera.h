#pragma once
#ifndef CAMERA_H
#define CAMERA_H


#include "UsefullStuff.h"
#include <iostream>
#include <list>

int ACTIVE_SECCAM = 0;
bool AUTO_SECCAM = true;

enum CAMERAMODI {
	ORBIT = 0,
	SECURITYCAM ,
	FAHRER,
	FOLLOW,
	WALK,
	TOPDOWN,
	MODICOUNT
};


char* CameraModiStrings[] = { "ORBIT", "SECURITYCAM", "FAHRER", "FOLLOW", "WALK", "TOPDOWN" };

std::map<int, std::list<std::string>> Steuerung{
	{0, {"Kamera Steuerung:",
		"",
		"linke Maus Taste      Kamerabewegung",
		"mittlere Maus Taste   Zoom",
		"",
		"Stapler Steuerung:",
		"",
		"Pfeiltasten           Staplerbewegung",
		"NUMPAD_8 / NUMPAD_2   Gabel hoch/runter",
		"NUMPAD_4 / NUMPAD_6   Gabel zusammen/auseinander",
		"NUMPAD_7              Stapler Scheinwerfer(an/aus)",
		"r, R                  Reset Stapler"}},
	{1, {"Security Kamera Steuerung:",
		"",
		"Die Security Kamera verfolgt automatisch",
		"den Stapler und laesst sich nicht steuern!",
		"Bild UP               Naechste",
		"                      Security Kamera",
		"",
		"Stapler Steuerung:",
		"",
		"Pfeiltasten           Staplerbewegung",
		"NUMPAD_8 / NUMPAD_2   Gabel hoch/runter",
		"NUMPAD_4 / NUMPAD_6   Gabel zusammen/auseinander",
		"NUMPAD_7              Stapler Scheinwerfer(an/aus)",
		"r, R                  Reset Stapler"}},
	{2, {"Fahrer Kamera Steuerung:",
		"",
		"linke Maus Taste      Kamerabewegung",
		"",
		"Stapler Steuerung:",
		"",
		"Pfeiltasten           Staplerbewegung",
		"NUMPAD_8 / NUMPAD_2   Gabel hoch/runter",
		"NUMPAD_4 / NUMPAD_6   Gabel zusammen/auseinander",
		"NUMPAD_7              Stapler Scheinwerfer(an/aus)",
		"r, R                  Reset Stapler"}},
	{3, {"Verfolger Kamera Steuerung:",
		"",
		"mittlere Maus Taste   Kameraentfernung",
		"",
		"Stapler Steuerung:",
		"",
		"Pfeiltasten           Staplerbewegung",
		"NUMPAD_8 / NUMPAD_2   Gabel hoch/runter",
		"NUMPAD_4 / NUMPAD_6   Gabel zusammen/auseinander",
		"NUMPAD_7              Stapler Scheinwerfer(an/aus)",
		"r, R                  Reset Stapler"}},
	{4, {"Walking Kamera Steuerung:",
		"",
		"linke Maus Taste      Blickrichtung",
		"Pfeiltasten           Bewegung"
		"",
		"Stapler Steuerung:",
		"",
		"Der Stapler laesst sich im Walk", 
		"Modus nicht steuern!"}},
	{5, {"Topdown Kamera Steuerung:",
		"",
		"mittlere Maus Taste   Zoom",
		"",
		"Stapler Steuerung:",
		"",
		"Pfeiltasten           Staplerbewegung",
		"NUMPAD_8 / NUMPAD_2   Gabel hoch/runter",
		"NUMPAD_4 / NUMPAD_6   Gabel zusammen/auseinander",
	    "NUMPAD_7              Stapler Scheinwerfer(an/aus)",
		"r, R                  Reset Stapler"}}
};


struct camera {
	int CameraMode = TOPDOWN;
	position walkpos = position::newPosition(-20.0f,12.0f,0.0f,0.0f);
	position pos;
	position lookat;
	float upvector[3] = { 0,1,0 };
	float front[3] = { 0,0,-1 };
	float dx = 0;
	float dy = 0;
	float followerdist = 1;
	float topdowndist = 70;

	float speed = 0.2f;

	void setCameraMode(int mode) {
		CameraMode = mode;
		std::cout << CameraMode;
	}

	char* stringFromCameraMode()
	{
		return CameraModiStrings[CameraMode];
	}

	std::list<std::string> getCameraModeControls() {
		return Steuerung[CameraMode];
	}




}cg_camera;


float Clamp(float value, float min, float max)
{
	if (value >= max) value = max;
	if (value <= min) value = min;
	return value;
}
#endif // CAMERA_H