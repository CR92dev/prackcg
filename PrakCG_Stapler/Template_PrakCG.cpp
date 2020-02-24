#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include "Include/freeglut.h"
#include "Include/glext.h"
#include "help.h"
#include "window.h"
#include "wavefront.h"
#include "input.h"
#include "light.h"
#include "colors.h"
#include "camera.h"
#include <time.h>       /* time */
#include "textures.h"


using std::string;
using std::map;

#ifndef	M_PI				// Pi
#define M_PI 3.14159265358979323846
#endif
#ifndef MIN					// Minimum bestimmen
#define MIN(a,b) ((a) > (b))? (b) : (a)
#endif
#ifndef MAX					// Maximum bestimmen
#define MAX(a,b) ((a) > (b))? (a) : (b)
#endif

#pragma region Region Define Objects

constexpr auto RESPATH = ".\\resources";
constexpr auto RES_HALL = "\\hall\\";
constexpr auto RES_STAPLER = "\\stapler\\";
constexpr auto RES_INDOOR = "\\indoor\\";
constexpr auto HALL_OBJECTS_COUNT = 14;
constexpr auto STAPLER_OBJECTS_COUNT = 21;
constexpr auto INDOOR_OBJECTS_COUNT = 9;


enum INDOORSTUFF {
	EUROPALETTE = 0,
	EUROPALETTE_FOUR,
	SECURITY_CAM,
	REGAL,
	REGAL_PLATTE,
	LAMP_CEILING,
	BOX,
	BOXES,
	CUBE //just for BB test 
};

map<int, string> objectfiles_indoor = {
	{EUROPALETTE, "europalette.obj"},
	{EUROPALETTE_FOUR, "eurofour.obj"},
	{SECURITY_CAM, "securitycam.obj"},
	{REGAL, "regal.obj"},
	{REGAL_PLATTE,"regal_platte.obj"},
	{LAMP_CEILING, "lamp_ceiling.obj"},
	{BOX, "box.obj"},
	{BOXES, "boxes.obj"},
	{CUBE, "cube.obj"}
};

map<int, color> colors_indoor = {
	{EUROPALETTE, brown},
	{EUROPALETTE_FOUR, brown},
	{REGAL,silver},
	{REGAL_PLATTE,darkslategray},
	{BOX,sandybrown},
	{BOXES,saddlebrown},
	{CUBE,red}
};


struct Europalette {

	float half_high = 0.1f;
	float half_width = 2.82f;
	float half_depth = 3.04f;

	float pos[3] = { 0,0,0 };

	Europalette() {

	}


} myEuropalette;

map<int, position> euro_positions = {

};

map<int, position> box_positions = {

};

map<int, position> boxes_positions = {};


map<int, position> eurofour_positions = {
	{0, position::newPosition(-42.0f,0.0f,42.0f)},
	{1, position::newPosition(-42.0f,0.0f,50.0f)},
};

map<int, position> regal_positions = {

	//west
	{0, position::newPosition(0.0f,8.85f,25.0f)},
	{1, position::newPosition(28.0f,8.85f,25.0f)},
	{2, position::newPosition(56.0f,8.85f,25.0f)},
	{3, position::newPosition(100.0f,8.85f,25.0f)},
	{4, position::newPosition(128.0f,8.85f,25.0f)},
	//mid
	{5, position::newPosition(0.0f,8.85f,-10.0f)},
	{6, position::newPosition(28.0f,8.85f,-10.0f)},
	{7, position::newPosition(56.0f,8.85f,-10.0f)},
	{8, position::newPosition(100.0f,8.85f,-10.0f)},
	{9, position::newPosition(128.0f,8.85f,-10.0f)},
	//east
	{10, position::newPosition(0.0f,8.85f,-45.0f)},
	{11, position::newPosition(28.0f,8.85f,-45.0f)},
	{12, position::newPosition(56.0f,8.85f,-45.0f)},
	{13, position::newPosition(100.0f,8.85f,-45.0f)},
	{14, position::newPosition(128.0f,8.85f,-45.0f)}

};

map<int, float> regal_platte_offsets = {
	{0, 2.5f},
	{1, 7.5f}
};


map<int, position> securitycam_positions = {
	{0, position::newPosition(-53.0f,48.0f,53.0f,-50.0f)},
	{1, position::newPosition(-53.0f,48.0f,-63.0f,-140.0f)},
	{2, position::newPosition(163.0f,48.0f,-63.0f,140.0f)},
	{3, position::newPosition(163.0f,48.0f,53.0f,50.0f)},
};

map<int, position> lamp_ceiling_positions = {
	//WEST
	{0, position::newPosition(-5.0f,28.0f,45.0f)},
	{1, position::newPosition(65.0f,28.0f,45.0f)},
	{2, position::newPosition(125.0f,28.0f,45.0f)},
	//MID
	{3, position::newPosition(-5.0f,35.0f,5.0f)},
	{4, position::newPosition(65.0f,35.0f,5.0f)},
	{5, position::newPosition(125.0f,35.0f,5.0f)},
	//EAST
	{6, position::newPosition(-5.0f,28.0f,-30.0f)},
	{7, position::newPosition(65.0f,28.0f,-30.0f)},
	{8, position::newPosition(125.0f,28.0f,-30.0f)}
};

enum HALLOBJ {
	MAIN_FLOOR = 0,
	FLOOR_RAMP,
	FLOOR_RAMP_BORDER,
	HALL_FLOOR,
	HALL_WALLS,
	HALL_DOOR,
	HALL_DOOR_ROOF,
	HALL_LOADING_DOOR,
	HALL_ROOF,
	HALL_WALK,
	HALL_STAIRS,
	HALL_RAILING,
	HALL_FENSTER,
	CUBE_MAP_TEST //nur test
};


map<int, string> objectfiles_hall = {
	{MAIN_FLOOR, "floor.obj"},
	{FLOOR_RAMP,"floor_ramp.obj"},
	{FLOOR_RAMP_BORDER,"floor_ramp_border.obj"},
	{HALL_FLOOR,"hall_floor.obj"},
	{HALL_WALLS,"hall_walls.obj"},
	{HALL_DOOR,"hall_doors.obj"},
	{HALL_DOOR_ROOF,"hall_door_roof.obj"},
	{HALL_LOADING_DOOR,"hall_loading_door.obj"},
	{HALL_ROOF,"hall_roof.obj"},
	{HALL_WALK,"hall_walk.obj"},
	{HALL_STAIRS,"hall_stairs.obj"},
	{HALL_RAILING,"hall_railing.obj"},
	{HALL_FENSTER,"hall_fenster.obj"}, //als letztes zeichnen sonst sieht man nicht alles durch das fesnter^^
	{CUBE_MAP_TEST,"cube_maptest.obj"}
};

map<int, color> colors_hall = {
	{MAIN_FLOOR, lightgreen},
	{FLOOR_RAMP, lightgrey},
	{FLOOR_RAMP_BORDER, darkgray},
	{HALL_FLOOR, lightgrey},
	{HALL_WALLS, darkgray},
	{HALL_DOOR, lightslategray},
	{HALL_DOOR_ROOF, slategray},
	{HALL_LOADING_DOOR,lightslategray},
	{HALL_ROOF, darkorange},
	{HALL_WALK, darkgray},
	{HALL_STAIRS, darkgray},
	{HALL_RAILING, black},
	{HALL_FENSTER, white},
	{CUBE_MAP_TEST, lightblue}
};

map<int, area> boundingareas = {
	{0, area::newArea(position::newPosition(-33, 0, 8.3), position::newPosition(-47, 0, -34.7))},	//STAIRS_BB
	{1, area::newArea(position::newPosition(-43, 0, 8.3), position::newPosition(-55, 0, -63.4))},	//WALK_BB
	{2, area::newArea(position::newPosition(-55, 0, 67), position::newPosition(-65, 0, -63.4))},	//WALL_NORTH_BB
	{3, area::newArea(position::newPosition(172, 0, 67), position::newPosition(162, 0, -63.4))},	//WALL_SOUTH_BB
	{4, area::newArea(position::newPosition(-65, 0, -67), position::newPosition(172, 0, -73))},		//WALL_EAST_BB
	{5, area::newArea(position::newPosition(-65, 0, 54), position::newPosition(172, 0, 67))},		//WALL_WEST_BB
};


map<int, area> regalareas;


enum STAPLEROBJ {
	KAROSSE = 0,
	KAROSSE_FRONT,
	STAPLER_ABCSAEULEN,
	STAPLER_ROOF,
	STAPLER_AMATUR,
	STAPLER_SITZ,
	STAPLER_SITZ_IN,
	LAMPENHALTER,
	REELS_FRONT,
	REELS_FRONT_IN,
	REEL_BACK,
	REEL_BACK_IN,
	LENKRAD,
	LIGHT_FRONT_LEFT,
	LIGHT_FRONT_RIGHT,
	GABEL_LIFT,
	GABEL_HALTER,
	GABEL_STIFT_LEFT,
	GABEL_STIFT_RIGHT,
	BB_STAPLER,			//wird nicht gezeichnet
	BB_GABEL			//wird nicht gezeichnet
};

struct Stapler {
	float speed;    // Geschwindigkeit [m/s]
	float steer;    // Lenkeinschlag   [°]
	float pos[3];   // Position        [m]
	float rot[3];   // Rotation        [°]
	float initialpos[3];
	float wheelrot_front; // Rollposition der Räder [°]
	float wheelrot_back; // Rollposition der Räder [°]
	float wheel_radius_front = 0.67f; //1.17f; - karosse floor dist    // Radius der Front Räder 
	float wheel_radius_back = 1.25f;//1.75f; - karosse floor dist    // Radius des Hinter Rads TODO
	float lenkrad_offset = -1.0f; // offset des lenkrads
	float lenkrad_high = 5.9f;
	float lenkrad_rot = 35.0f;
	float front_axis = -4.8f;    // Abstand vordere Achse zum Nullpunkt (auf Z)
	float back_axis = 2.4f;		 // Abstand hintere Achse zum Nullpunkt (auf Z)
	float karosse_floordist = 0.5f; //Abstand der Karosse zum boden
	float max_speed = 8.0f;
	float min_speed = -5.0f;
	float lights_high = 10.0f;
	float lights_dist = -3.7f;
	float lights_offset = 2.95f;
	bool lights_on = false;

	float collisionPoint_FrontLeft[3] = { -2.5f,0.0f,-11.0f };
	float collisionPoint_FrontRight[3] = { 2.5f,0.0f,-11.0f };
	float collisionPoint_BackLeft[3] = { -4.0f,0.0f,3.0f };
	float collisionPoint_BackRight[3] = { 4.0f,0.0f,3.0f };
	//für die Regale kommen die Kollisionspunkte FrontLeft/FrontRight nicht in frage - da der stapler ja mit den gabel in die Regale fahren kann
	float collisionPoint_FrontLeft_Karosse[3] = {-4.0f,0.0f,-6.5f};		
	float collisionPoint_FrontRight_Karosse[3] = { 4.0f,0.0f,-6.5f };

	float cockpit[3] = {0 ,8.0f,1.0f };
	float follower[3] = { 0,15, 16 };

	Stapler()
	{
		initialpos[0]= -25.0f;
		initialpos[1] = 0;
		initialpos[2] = 20.0f;

		reset();
	}

	void reset() {
		wheelrot_front = wheelrot_back = 0;
		speed = 0; steer = 0;
		//start position
		pos[0] = initialpos[0];
		pos[1] = initialpos[1];
		pos[2] = initialpos[2];
		//start rotation
		rot[0] = rot[2] = rot[1] = 0;
	}

	position getCollider(float* colliderpos) {
		float cos_ = cos(rot[1] * M_PI / 180);
		float sin_ = sin(rot[1] * M_PI / 180);

		float checkpoint[3];
		checkpoint[0] = (colliderpos[0] * cos_) + (colliderpos[2] * sin_);
		checkpoint[1] = colliderpos[1];
		checkpoint[2] = (colliderpos[0] * -sin_) + colliderpos[2] * cos_;

		position colpoint = position::newPosition(checkpoint[0] + pos[0], checkpoint[1] + pos[1], checkpoint[2] + pos[2]);
		return colpoint;
	}

} myStapler;

struct Gabel {
	float liftspeed;
	float forkspeed;
	float lifthigh;
	float holderhigh;
	float stickoffset;
	float max_liftheight = 8.0f;
	float max_holderheight = 8.0f;
	float max_stickoffset = 1.0f;

	//float bb_pos[3] = { 0.0f, myStapler.karosse_floordist + 0.5f ,-7.6f };
	//float bb_width = 1.8f;

	Gabel() {
		liftspeed = forkspeed = 0;
		lifthigh = 0;
		holderhigh = 0;
		stickoffset = 0;
	}
} myGabel;

map<int, string> objectfiles_stapler = {
	{KAROSSE, "stapler_karosse.obj"},
	{KAROSSE_FRONT, "stapler_karosse_front.obj"},
	{STAPLER_ABCSAEULEN, "stapler_abcsaeulen.obj"},
	{STAPLER_ROOF, "stapler_roof.obj"},
	{STAPLER_AMATUR,"stapler_amatur.obj"},
	{STAPLER_SITZ,"stapler_sitz.obj"},
	{STAPLER_SITZ_IN,"stapler_sitz_1.obj"},
	{LAMPENHALTER,"stapler_Lampenhalter.obj"},
	{REELS_FRONT,"stapler_reels_front.obj"},
	{REELS_FRONT_IN,"stapler_reels_front_in.obj"},
	{REEL_BACK,"stapler_reel_back.obj"},
	{REEL_BACK_IN,"stapler_reel_back_in.obj"},
	{LENKRAD,"stapler_lenkrad.obj"},
	{LIGHT_FRONT_LEFT,"stapler_light_front_l.obj"},
	{LIGHT_FRONT_RIGHT,"stapler_light_front_r.obj"},
	{GABEL_LIFT,"stapler_gabel_lift.obj"},
	{GABEL_HALTER,"stapler_gabel_halter.obj"},
	{GABEL_STIFT_LEFT,"stapler_gabel_stift_l.obj"},
	{GABEL_STIFT_RIGHT,"stapler_gabel_stift_r.obj"},
	{BB_STAPLER,"stapler_BB.obj"},
	{BB_GABEL, "stapler_gabel_BB.obj"}
};

map<int, color> colors_stapler = {
	{KAROSSE, yellow},
	{KAROSSE_FRONT,silver},
	{STAPLER_ABCSAEULEN,darkgray},
	{STAPLER_ROOF,yellow},
	{STAPLER_SITZ,black},
	{STAPLER_SITZ_IN,silver},
	{STAPLER_AMATUR,silver},
	{LENKRAD, black},
	{GABEL_LIFT,darkgray},
	{LIGHT_FRONT_LEFT,darkorange},
	{LIGHT_FRONT_RIGHT,darkorange},
	{REEL_BACK,black},
	{REEL_BACK_IN,silver},
	{REELS_FRONT,black},
	{REELS_FRONT_IN,silver}
};

static cg_light front_lights[2] = { 1, 2 };
static cg_light lamp_ceiling[9] = { 3,4,5,6,7,8,9,10,11 };
static bool globalLight = true;
static bool ceilingLight = true;
object3D* objects_hall[HALL_OBJECTS_COUNT];
object3D* objects_stapler[STAPLER_OBJECTS_COUNT];
object3D* objects_indoor[INDOOR_OBJECTS_COUNT];

//textures
GLuint textures[2];


#pragma endregion 

#pragma region Region Define Methods

void setCamera ();		// Kamera platzieren, siehe Maus-Callbacks
void drawScene ();		// Zeichnet die Szene im Weltkoordinatensystem
void keyHandler(cg_help ,cg_globState , cg_key );    // Handle Key Input
void Load_Objects(void);			//Load object
void Draw_Hall();
void Draw_Stapler();
void Draw_Indoor();
void Process(cg_key);
void processCameraMovement(cg_key);

#pragma endregion 


/*
Berechnet die Bounding Areas der Regale für den Kollisioncheck
*/
void initregalareas() {
	float dx = 12.75;
	float dz = 7.5;
	for (auto obj : regal_positions) {
		regalareas.insert(std::pair<int,area> (obj.first, area::newArea(position::newPosition(obj.second.x + dx, 0, obj.second.z + dz), position::newPosition(obj.second.x - dx, 0, obj.second.z - dz))));
	}
}

void initPalettenPositions() {
	//random Paletten zeichnen
	srand(time(NULL));
	int count = rand() % 20 + 30;
	float height[3] = { 0.0f,7.0f, 14.3f };
	float dx[3] = { -6.0f,0.0f, 6.0f };
	float dz[2] = { -4.0f,4.0f };

	for (int i = 0; i < count; i++) {
		int regalpos = rand() % regal_positions.size();
		position pos = position::newPosition(regal_positions[regalpos].x + dx[rand() % 3], height[rand() % 3], regal_positions[regalpos].z + +dz[rand() % 2]);
		//was wenn durch zufall 2 mal die exakt selben positionen ermittelt werden?
		//-> prüfe ob position bereits existiert!
		bool exists = false;
		for (auto p : euro_positions) {
			if (exists = p.second.equals(pos)) 
				break;
		}
		if (!exists) {
			euro_positions.insert(std::pair<int, position>(i, pos));
			int boxdecider = rand() % 10;
			if (boxdecider < 4) {
				box_positions.insert(std::pair<int, position>(i, pos));
			}
			else if (boxdecider > 5) {
				boxes_positions.insert(std::pair<int, position>(i, pos));
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
//	Anfang des OpenGL Programmes
/////////////////////////////////////////////////////////////////////////////////
int main ( int argc, char **argv )
{
	init( argc, argv );

	//init textures - test
	textures[0] = createTexture("resources/images/test.png");
	textures[1] = createTexture("resources/images/box.jpg");

	//init some stuff
	initregalareas();
	initPalettenPositions();
	//anzeigen updaten
	cg_help::setCameraModeString(cg_camera.stringFromCameraMode());
	cg_help::setCameraModeControls(cg_camera.getCameraModeControls());
	cg_help::setCollisionMode(cg_globState::collision);

	// Die Hauptschleife starten

	glutMainLoop ();
	return 0;
}


void Load_Objects(void) {

	//load hall objects and init colors
	for (auto obj : objectfiles_hall) {
		char file[255] = "";
		strcat(file, RESPATH);
		strcat(file, RES_HALL);
		strcat(file, obj.second.c_str());

		objects_hall[obj.first] = loadobject(file, false);
		if (colors_hall.count(obj.first) > 0) {

			if (obj.first == HALL_FENSTER) { // ist transparent
				set_obj_material(objects_hall[obj.first], colors_hall[obj.first].fRed, colors_hall[obj.first].fGreen, colors_hall[obj.first].fBlue, 0.3f, 0.0f, 128.0f, 0.0f);
			}
			else {
				set_obj_material(objects_hall[obj.first], colors_hall[obj.first].fRed, colors_hall[obj.first].fGreen, colors_hall[obj.first].fBlue, 1.0f, 0.0f, 128.0f, 0.0f);
			}

		}
	}

	//load indoor objects and init colors
	for (auto obj : objectfiles_indoor) {
		char file[255] = "";
		strcat(file, RESPATH);
		strcat(file, RES_INDOOR);
		strcat(file, obj.second.c_str());

		objects_indoor[obj.first] = loadobject(file, false);
		if (colors_indoor.count(obj.first) > 0) {
			set_obj_material(objects_indoor[obj.first], colors_indoor[obj.first].fRed, colors_indoor[obj.first].fGreen, colors_indoor[obj.first].fBlue, 1.0f, 0.0f, 128.0f, 0.0f);
		}
	}


//load stapler objects and init colors
for (auto obj : objectfiles_stapler) {
	char file[255] = "";
	strcat(file, RESPATH);
	strcat(file, RES_STAPLER);
	strcat(file, obj.second.c_str());

	objects_stapler[obj.first] = loadobject(file, false);
	if (colors_stapler.count(obj.first) > 0) {
		set_obj_material(objects_stapler[obj.first], colors_stapler[obj.first].fRed, colors_stapler[obj.first].fGreen, colors_stapler[obj.first].fBlue, 1.0f, 0.0f, 128.0f, 0.0f);
	}
}



};


void displayFunc()
{
	// Hilfe-Instanzen
	cg_help help;
	cg_globState globState;
	cg_key key;
	keyHandler(help, globState, key);

	// Szene zeichnen: CLEAR, SETCAMERA, DRAW_SCENE

	// Back-Buffer neu initialisieren
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	processCameraMovement(key);
	// Kamera setzen (spherische Mausnavigation)
	setCamera();

	// Koordinatensystem zeichnen
	help.drawKoordsystem(-8, 10, -8, 10, -8, 10);

	//smoothshading
	glShadeModel(globState.shadeMode);

	// Zeichenmodus einstellen (Wireframe on/off)
	glPolygonMode(GL_FRONT_AND_BACK, globState.drawMode);

	// Backface Culling on/off);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	if (globState.cullMode) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	// Farbmodus oder Beleuchtungsmodus ?
	if (globState.lightMode == GL_TRUE) // Beleuchtung aktivieren
	{
		float m_amb[4] = { 0.2, 0.2, 0.2, 1.0 };
		float m_diff[4] = { 0.2, 0.2, 0.6, 1.0 };
		float m_spec[4] = { 0.8, 0.8, 0.8, 1.0 };
		float m_shine = 32.0;
		float m_emiss[4] = { 0.0, 0.0, 0.0, 1.0 };

		SetMaterial(GL_FRONT_AND_BACK, m_amb, m_diff, m_spec, m_shine, m_emiss);

		SetLights(globalLight);

		glEnable(GL_LIGHTING);
	}
	else   // Zeichnen im Farbmodus
	{
		glDisable(GL_LIGHTING);
		glColor4f(0.2, 0.2, 0.6, 1.0);
	}


	// Process Input/ Objects
	if(cg_camera.CameraMode != CAMERAMODI::WALK)
		Process(key);
	

	// Geometrie zeichnen 
	drawScene();


	// Hilfetext zeichnen
	help.draw();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glFlush();				// Daten an Server (fuer die Darstellung) schicken
	glutSwapBuffers();		// Buffers wechseln
}


void Process(cg_key key)
{
	//TODO der Lenkeinschlag des hinterrads muss bei bewegung wieder veringert werden wenn speed > oder < 0 ist
	//rearange backwheel
	if (myStapler.speed > 0.1f || myStapler.speed < -0.1f) {
		if(myStapler.steer < 0.0f)
			if (key.specialKeyState(GLUT_KEY_LEFT) == 0) {
				myStapler.steer += 0.01f;
			}
		if(myStapler.steer > 0.0f)
			if (key.specialKeyState(GLUT_KEY_RIGHT) == 0)
			{
				myStapler.steer -= 0.01f;
			}
	}


	//inputs

	//turn light on/off
	if (key.keyState('7')) {
		myStapler.lights_on = !myStapler.lights_on;
		if (!myStapler.lights_on) {
			set_obj_material(objects_stapler[LIGHT_FRONT_LEFT],colors_stapler[LIGHT_FRONT_LEFT].fRed, colors_stapler[LIGHT_FRONT_LEFT].fGreen, colors_stapler[LIGHT_FRONT_LEFT].fBlue, 1.0f, 0.0f, 128.0f, 0.0f);
			set_obj_material(objects_stapler[LIGHT_FRONT_RIGHT], colors_stapler[LIGHT_FRONT_RIGHT].fRed, colors_stapler[LIGHT_FRONT_RIGHT].fGreen, colors_stapler[LIGHT_FRONT_RIGHT].fBlue, 1.0f, 0.0f, 128.0f, 0.0f);
		}
		else {
			set_obj_material(objects_stapler[LIGHT_FRONT_LEFT], colors_stapler[LIGHT_FRONT_LEFT].fRed, colors_stapler[LIGHT_FRONT_LEFT].fGreen, colors_stapler[LIGHT_FRONT_LEFT].fBlue, 1.0f, 0.0f, 128.0f, 1.0f);
			set_obj_material(objects_stapler[LIGHT_FRONT_RIGHT], colors_stapler[LIGHT_FRONT_RIGHT].fRed, colors_stapler[LIGHT_FRONT_RIGHT].fGreen, colors_stapler[LIGHT_FRONT_RIGHT].fBlue, 1.0f, 0.0f, 128.0f, 1.0f);
		}
	}
	//reset Stapler
	if (key.keyState('r') == 1 || key.keyState('R') == 1) {
		myStapler.reset();
	}

	//moving the vehicle
	if (key.specialKeyState(GLUT_KEY_LEFT) == 2) myStapler.steer -= 0.2f;		//left
	if (key.specialKeyState(GLUT_KEY_RIGHT) == 2) myStapler.steer += 0.2f;		//right
	if (key.specialKeyState(GLUT_KEY_UP) == 2) myStapler.speed += 0.003f;		//forward
	if (key.specialKeyState(GLUT_KEY_DOWN) == 2) myStapler.speed -= 0.003f;		//backward	
	if (key.keyState(' ') == 2)  myStapler.speed *= 0.5f;						//handbrake

	//moving the fork
	if (key.keyState('8') == 2)  myGabel.liftspeed += 0.5f;						// fork lift up
	if (key.keyState('2') == 2)  myGabel.liftspeed -= 0.5f;						// fork lift up
	if (key.keyState('2') == 0 && key.keyState('8') == 0)  myGabel.liftspeed = 0.0f;
	
	if (key.keyState('4') == 2)  myGabel.forkspeed += 0.001f;						// fork move together
	if (key.keyState('6') == 2)  myGabel.forkspeed -= 0.001f;						// fork move apart
	if (key.keyState('4') == 0 && key.keyState('6') == 0) myGabel.forkspeed = 0.0f;

	//Luftwiederstand oder so
	if (key.specialKeyState(GLUT_KEY_UP) == 0 && key.specialKeyState(GLUT_KEY_DOWN) == 0) {
		myStapler.speed *= 0.995f;
	}

	//limit - To be tested yet
	myStapler.speed = MIN(myStapler.speed, myStapler.max_speed);
	//if (myStapler.speed > myStapler.max_speed)    myStapler.speed = myStapler.max_speed; 
	myStapler.speed = MAX(myStapler.speed, myStapler.min_speed);
	//if (myStapler.speed < myStapler.min_speed)    myStapler.speed = myStapler.min_speed;  

	if (myStapler.steer > 30.0f)    myStapler.steer = 30.0f;   // Max 30° 
	if (myStapler.steer < -30.0f)   myStapler.steer = -30.0f;   // Max -30°

	//TODO limit the forkspeed
	if (myGabel.liftspeed > 1.0f)    myGabel.liftspeed = 1.0f;  
	if (myGabel.liftspeed < -1.0f)   myGabel.liftspeed = -1.0f;  
	if (myGabel.forkspeed > 0.01f)    myGabel.forkspeed = 0.01f;    
	if (myGabel.forkspeed < -0.01f)   myGabel.forkspeed = -0.01f;  

	//processing FORK
	float speed_perframe = myGabel.liftspeed / 60.0f;

	if (speed_perframe > 0) {
		//////////// Holder //////////
		//limit holderhigh
		myGabel.holderhigh += speed_perframe;
		if (myGabel.holderhigh > myGabel.max_holderheight) {
			myGabel.holderhigh = myGabel.max_holderheight;
			myGabel.lifthigh += speed_perframe;



		}
		////////// LIFT ///////////////
		//limit lifthigh
		if (myGabel.lifthigh > myGabel.max_liftheight) {
			myGabel.lifthigh = myGabel.max_liftheight;
			myGabel.liftspeed = 0;
		}
	}
	else {
		////////// LIFT ///////////////
				//limit lifthigh
		myGabel.lifthigh += speed_perframe;
		if (myGabel.lifthigh < 0.0f) {
			myGabel.lifthigh = 0.0f;
			myGabel.holderhigh += speed_perframe;
		}
		//////////// Holder //////////
				//limit holderhigh
		if (myGabel.holderhigh < 0.0f) {
			myGabel.liftspeed = 0; // anhalten
			myGabel.holderhigh = 0.0f;
		}
	}

	speed_perframe = myGabel.forkspeed / 60.0f;
	myGabel.stickoffset += myGabel.forkspeed;
	if (myGabel.stickoffset > myGabel.max_stickoffset) {
		myGabel.stickoffset = myGabel.max_stickoffset;
	}
	else if(myGabel.stickoffset < 0.0f ){
		myGabel.stickoffset = 0.0f;
		myGabel.forkspeed = 0.0f;
	}



	//processing stapler speed

	// Geschwindigkeit in m/frame, berechnet aus speed in m/s
	speed_perframe = myStapler.speed / 60.0f;

	float circ = 2.0 * M_PI * myStapler.wheel_radius_front;			// Radumfang berechnen
	myStapler.wheelrot_front += 360.0f / circ * speed_perframe;	// neuer Drehwinkel der Räder

	circ = 2.0 * M_PI * myStapler.wheel_radius_back;			// Radumfang berechnen
	myStapler.wheelrot_back += 360.0f / circ * speed_perframe;	// neuer Drehwinkel der Räder

	// Position und Rotation neu berechnen:
	// Rotation ist nur um die Y-Achse interessant
	float alpha = (myStapler.rot[1] + myStapler.steer) * M_PI / 180.0f;
	float alpha_old = myStapler.rot[1] * M_PI / 180.0f;
	float vec[3] = { sin(alpha),    0,cos(alpha) };     // neuer Bewegungsvektor der Hinterachse
	float vec_old[3] = { sin(alpha_old),0,cos(alpha_old) }; // alter Richtungsvektor
	float back_point_old[3] = { vec_old[0] * myStapler.back_axis,    // Mittelpunkt der Hinterachse
								vec_old[1] * myStapler.back_axis,
								vec_old[2] * myStapler.back_axis };
	float back_point_new[3] = { back_point_old[0] - speed_perframe * vec[0], // neuer Mittelpunkt der Hinterachse
								back_point_old[1] - speed_perframe * vec[1],
								back_point_old[2] - speed_perframe * vec[2] };
	// Nun Mittelpunkt der Vorderachse (hier (0,0,0)!) neu berechnen.
	// Dieser entspricht dann der gesuchten Fahrzeugbewegung.
	// Er liegt auf dem Vektor V, der vom alten Mittelpunkt(0,0,0) zum neuen Hinterachsenpunkt zeigt
	float V[3] = { back_point_new[0],
				  back_point_new[1],
				  back_point_new[2] };
	normieren(V);
	float pos[3] = { back_point_new[0] - V[0] * myStapler.back_axis,
					back_point_new[1] - V[1] * myStapler.back_axis,
					back_point_new[2] - V[2] * myStapler.back_axis };

	float alpha_new = asin(V[0]) * 180.0f / M_PI; if (V[2] < 0) alpha_new = 180.0f - alpha_new;

	while (alpha_new > 360.0f) alpha_new -= 360.0f;
	while (alpha_new < 0.0f)   alpha_new += 360.0f;




		float rotz_old = myStapler.rot[1];
		myStapler.rot[1] = alpha_new;
		myStapler.pos[0] += pos[0];
		myStapler.pos[1] += pos[1];
		myStapler.pos[2] += pos[2];

		//area check with Objects - funktioniert einigermaßen
		if (cg_globState::collision) {


		if (myStapler.rot[1] != alpha_new || pos[0] != 0 || pos[2] != 0) {
			position test = myStapler.getCollider(myStapler.collisionPoint_FrontLeft);
			position test1 = myStapler.getCollider(myStapler.collisionPoint_FrontRight);
			position test2 = myStapler.getCollider(myStapler.collisionPoint_BackLeft);
			position test3 = myStapler.getCollider(myStapler.collisionPoint_BackRight);

			position test4 = myStapler.getCollider(myStapler.collisionPoint_FrontLeft_Karosse);
			position test5 = myStapler.getCollider(myStapler.collisionPoint_FrontRight_Karosse);


			for (auto obj : boundingareas) {
				if (obj.second.PointInArea(test) || obj.second.PointInArea(test1) || obj.second.PointInArea(test2) || obj.second.PointInArea(test3)) {
					//collision -> Stoße Stapler zurück und bremse ab
					//std::cout << "Collision!" << std::endl;
					myStapler.rot[1] = rotz_old;
					myStapler.pos[0] -= 3 * (pos[0]);
					myStapler.pos[1] -= 3 * (pos[1]);
					myStapler.pos[2] -= 3 * (pos[2]);
					myStapler.speed = 0;
					return;
				}
				else {
					//Keine Kollision mit wänden
				}
			}
			for (auto regal : regalareas) {
				if (regal.second.PointInArea(test4) || regal.second.PointInArea(test5) || regal.second.PointInArea(test2) || regal.second.PointInArea(test3)) {
					myStapler.rot[1] = rotz_old;
					myStapler.pos[0] -= 3 * (pos[0]);
					myStapler.pos[1] -= 3 * (pos[1]);
					myStapler.pos[2] -= 3 * (pos[2]);
					myStapler.speed = 0;
					return;
				}
				else {
					//Keine Kollision mit regalen
				}
			}
		}
	}
}

void ProcessliftableObjects(float* oldGabelPos , float* newGabelPos)
{
	//loop über alle objektposition die anhebbar sind bisher sind das:  eurofour_positions,	euro_positions
	//wenn gabel 'unterhalb' der objectposition + innerhalb der grenzen des objects -> anheben
	//äußere punkte der BB innerhal der fläche des objects sind und obere fläche der boundingbox auf einer ebene mit der unteren ebene des objects ?
	return;
}

void drawScene ()
{

	static bool start = false;

	if (start == false) {
		Load_Objects();
		start = true;
	}
	//blue backgroundcolor aka sky
	glClearColor(lightblue.fRed,lightblue.fGreen,lightblue.fBlue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

#pragma region testtexture
	//test textures -funktioniert nicht wirklich
	/*
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0f, 10.0f, 0.0f);
	glScalef(5, 5, 5);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glNormal3f(-1, -1, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -0.1f);

		glNormal3f(1, -1, 1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(1.0f, -1.0f, -0.1f);

		glNormal3f(1, 1, 1.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, 1.0f, -0.1f);

		glNormal3f(-1, 1, 1.0f);
		glTexCoord2f(0.0, 1);
		glVertex3f(-1.0f, 1.0f, -0.1f);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	*/
#pragma endregion

	// Zeichnet die Szene 1x im Weltkoordinatensystem
	//draw Stapler
	Draw_Stapler();
	//Draw Indoor
	Draw_Indoor();
	//draw Hall
	Draw_Hall();

}

/*
Draw all Hall objects
- Offsets are included in obj files - no translation/rotation needed
*/
void Draw_Hall() {

	for (int i = 0; i < HALL_OBJECTS_COUNT; i++) {
	glPushMatrix();
	if (cg_camera.CameraMode == CAMERAMODI::TOPDOWN && i == HALL_ROOF) { 
		//Dach nicht zeichnen in topwdown view
	}
	else if (cg_camera.CameraMode == CAMERAMODI::ORBIT && i == HALL_ROOF && cg_camera.pos.y > 55) { 
		//Dach nicht zeichnen in Normalview mit camerahigh > 55
	}
	else if (i == HALL_FENSTER) {
		glEnable(GL_BLEND);
		drawobject(objects_hall[i]);
		glDisable(GL_BLEND);
	}
	else if (i == CUBE_MAP_TEST) {
		//broken
		//glTranslatef(0.0f, 50.0f, 0.0f);
		//glScalef(2.0f, 2.0f, 2.0f);
		//drawobject(objects_hall[i]);
	}
	else 
		drawobject(objects_hall[i]);
	glPopMatrix();
	}
	/*for (auto obj : objects_hall) {
		drawobject(obj);
	}*/
}

void Draw_Indoor() {

#pragma region Paletten und Boxen
	glPushMatrix();
	glTranslatef(0.0f, myEuropalette.half_high, 0.0f);
	//4er stapel euro paletten zeichnen

	for (auto i : eurofour_positions) {
		glPushMatrix();
		glTranslatef(i.second.x, i.second.y, i.second.z);
		drawobject(objects_indoor[EUROPALETTE_FOUR]);
		glPopMatrix();
	}

	//einzelne Europaletten zeichnen
	for (auto i : euro_positions) {
		glPushMatrix();
		glTranslatef(i.second.x, i.second.y, i.second.z);
		drawobject(objects_indoor[EUROPALETTE]);
		glPopMatrix();
	}

	//Single Boxes
	for (auto i : box_positions) {
		glPushMatrix();
		glTranslatef(i.second.x, i.second.y, i.second.z);
		drawobject(objects_indoor[BOX]);
		glPopMatrix();
	}

	//Quad Boxes
	for (auto i : boxes_positions) {
		glPushMatrix();
		glTranslatef(i.second.x, i.second.y, i.second.z);
		drawobject(objects_indoor[BOXES]);
		glPopMatrix();
	}

	glPopMatrix();

#pragma endregion


#pragma region Regale

	for (auto i : regal_positions) {
			glPushMatrix();
			glTranslatef(i.second.x, i.second.y, i.second.z);
			drawobject(objects_indoor[REGAL]);
			for (auto e : regal_platte_offsets)
			{
				glTranslatef(0.0f, e.second, 0.0f);
				drawobject(objects_indoor[REGAL_PLATTE]);
			}
			glPopMatrix();
	}

#pragma endregion

#pragma region Security Cams

	for (auto i : securitycam_positions) {
		//Aktive Cam im SECURITYCAM modus nicht zeichnen!
		if (cg_camera.CameraMode != CAMERAMODI::SECURITYCAM || ( i.first != ACTIVE_SECCAM && cg_camera.CameraMode == CAMERAMODI::SECURITYCAM)) {
			glPushMatrix();
			glTranslatef(i.second.x, i.second.y, i.second.z);
			glRotatef(i.second.rot, 0, 1, 0);
			drawobject(objects_indoor[SECURITY_CAM]);
			glPopMatrix();
		}
	}

#pragma endregion

#pragma region Lamps
	for (auto l : lamp_ceiling_positions) {
		glPushMatrix();
		glTranslatef(l.second.x, l.second.y, l.second.z);
		drawobject(objects_indoor[LAMP_CEILING]);
		glPopMatrix();
	}
	static bool initlamp = true;
	if (initlamp) {
		for (int i = 0; i < 9; ++i)  // 9 deckenleuchten //todo noch etwas herumspielen
		{
			auto l = lamp_ceiling_positions[i];
			lamp_ceiling[i].setPosition(l.x, l.y - 10.0f, l.z, 1.0f);
			lamp_ceiling[i].setSpotlight(0.0, -1.0, 0.0, 90.0, 1.0);
			lamp_ceiling[i].setAmbient(1, 1, 1, 0);
			lamp_ceiling[i].setDiffuse(1.0, 1.0, 0.3, 1.0);
			lamp_ceiling[i].setSpecular(1.0, 1.0, 0.3, 1.0);
			lamp_ceiling[i].setAttentuation(1.0f, 0.05f, 0.0f);
			//std::cout << "init lamp " << i << std::endl;
		}
		initlamp = false;
	}

	if (ceilingLight) {
		for (int i = 0; i < 9; ++i)  // 9 lichter an
		{
			lamp_ceiling[i].draw();
		}
	}
	else {
		for (int i = 0; i < 9; ++i) // 9 lichter aus
		{
			lamp_ceiling[i].disable();
		}
	}


			//randomflackern von lampen - sieht nicht wirklich nach flackern aus^^
			/*srand(time(NULL));
			int lamp = rand() % 10 ; //random lampe nummer zwischen 0 und 9
			int flackern = rand() % 101; // 0 -100
			if (flackern > 50) lamp_ceiling[lamp].disable();
			else lamp_ceiling[lamp].draw();
			*/		
#pragma endregion
}



/*
Draw the front axis
2 front Wheels
rot: Rotation der Räder entlang der Fahrtrichtung
*/
void DrawFronAxis(float rot) {
	glPushMatrix();
		glRotatef(rot, 1.0, 0.0, 0.0);    // rot° Drehung um Querachse (X)
		drawobject(objects_stapler[REELS_FRONT]);
		drawobject(objects_stapler[REELS_FRONT_IN]);
	glPopMatrix();
}

/*
Draw the Single wheel Back axis
steer: Lenkeinschlag des Rades
rot:   Rotation der Räder entlang der Fahrtrichtung
*/
void DrawBackAxis(float steer, float rot)
{
	glPushMatrix();
		glRotatef(steer, 0.0, 1.0, 0.0);    // steer° Drehung um Hochachse (Y)
		glRotatef(rot, 1.0, 0.0, 0.0);    // rot° Drehung um Querachse (X)
		drawobject(objects_stapler[REEL_BACK]);
		drawobject(objects_stapler[REEL_BACK_IN]);
	glPopMatrix();
}


/*
Draw the lift
*/
void DrawLift() {
	drawobject(objects_stapler[GABEL_LIFT]);
}

/*
Draw the Spines
*/
void DrawSpines() {

	//left spine
	glPushMatrix();
		glTranslatef(myGabel.stickoffset, 0.0, 0.0);
		drawobject(objects_stapler[GABEL_STIFT_LEFT]);
	glPopMatrix();
	//right spine
	glPushMatrix();
		glTranslatef(- myGabel.stickoffset, 0.0, 0.0);
		drawobject(objects_stapler[GABEL_STIFT_RIGHT]);
	glPopMatrix();

}

/*
Draw the ForkHolder
*/
void DrawHolder() {
	drawobject(objects_stapler[GABEL_HALTER]);
	DrawSpines();
}

/*
Draw the Fork
*/
void DrawFork()
{
	glPushMatrix();
		glTranslatef(0.0, myGabel.lifthigh, 0.0);
		DrawLift();
		glPushMatrix();
			glTranslatef(0.0, myGabel.holderhigh, 0.0);
			DrawHolder();
		glPopMatrix();
	glPopMatrix();
}

/*
Set up the Front Lights
*/
void setUpFrontLights() {

	static bool init = true;
	if (init) {
		for (int i = 0; i < 2; ++i)  // 2 Frontlichter definieren
		{
			front_lights[i].setPosition(-myStapler.lights_offset, myStapler.lights_high,myStapler.lights_dist, 1.0f);
			front_lights[i].setSpotlight(0.0, 0.0, -1.0, 20.0, 1.0);
			front_lights[i].setAmbient(1, 1, 1, 1.0);
			front_lights[i].setDiffuse(1.0, 1.0, 0.3, 1.0);
			front_lights[i].setSpecular(1.0, 1.0, 0.3, 1.0);
			front_lights[i].setAttentuation(1.0, 0.05, 0.0);
		}
		front_lights[1].setPosition(myStapler.lights_offset, myStapler.lights_high, myStapler.lights_dist, 1.0f);
		init = false;
	}
	if (myStapler.lights_on) {
		for (int i = 0; i < 2; ++i)  // 2 Frontlichter an
		{
			glColor3f(colors_stapler[LIGHT_FRONT_LEFT].fRed, colors_stapler[LIGHT_FRONT_LEFT].fGreen, colors_stapler[LIGHT_FRONT_LEFT].fBlue);
			front_lights[i].draw();
		}
	}
	else {
		for (int i = 0; i < 2; ++i) // 2 Frontlichter aus
		{
			front_lights[i].disable();
		}
	}
	//objekte
	glPushMatrix();
		glTranslatef(front_lights[0].getPosX(), front_lights[0].getPosY(), front_lights[0].getPosZ());
		drawobject(objects_stapler[LIGHT_FRONT_LEFT]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(front_lights[1].getPosX(), front_lights[1].getPosY(), front_lights[1].getPosZ());
		drawobject(objects_stapler[LIGHT_FRONT_RIGHT]);
	glPopMatrix();
}

/*
Draw the Stapler
*/
void Draw_Stapler() {

	glPushMatrix(); // Anheben
		glTranslatef(0.0, myStapler.karosse_floordist, 0.0);
		glTranslatef(myStapler.pos[0], myStapler.pos[1], myStapler.pos[2]);
		//glRotatef(myStapler.rot[2], 0, 0, 1);  // Rotation um Z-Achse
		glRotatef(myStapler.rot[1], 0, 1, 0);  // Rotation um Y-Achse
		//glRotatef(myStapler.rot[0], 1, 0, 0);  // Rotation um X-Achse

		//karosse 
		drawobject(objects_stapler[KAROSSE]);
		//karosse front
		drawobject(objects_stapler[KAROSSE_FRONT]);
		//ABC Säule
		drawobject(objects_stapler[STAPLER_ABCSAEULEN]);
		//roof
		drawobject(objects_stapler[STAPLER_ROOF]);
		//amatur
		drawobject(objects_stapler[STAPLER_AMATUR]);
		//sitz
		drawobject(objects_stapler[STAPLER_SITZ]);
		//sitz polster
		drawobject(objects_stapler[STAPLER_SITZ_IN]);
		//lampenhalterung
		drawobject(objects_stapler[LAMPENHALTER]);

		//front axis
		glPushMatrix();
			glTranslatef(0.0, myStapler.wheel_radius_front, 0.0);
			glTranslatef(0.0, 0.0, myStapler.front_axis);
			DrawFronAxis(myStapler.wheelrot_front);
		glPopMatrix();

		//back axis
		glPushMatrix();
			glTranslatef(0.0, myStapler.wheel_radius_back, 0.0);
			glTranslatef(0.0, 0.0, myStapler.back_axis);
			DrawBackAxis(myStapler.steer, myStapler.wheelrot_back);
		glPopMatrix();

		//Lenkrad
		glPushMatrix();
			glTranslatef(0.0f, myStapler.lenkrad_high, myStapler.lenkrad_offset );
			//Winkel anpassen und lenkeinschlag rotieren
			glRotatef(myStapler.lenkrad_rot, 1, 0, 0);
			glRotatef(-myStapler.steer* 3, 0, 1, 0);
			drawobject(objects_stapler[LENKRAD]);
		glPopMatrix();

		//Frontlights
		glPushMatrix();
			setUpFrontLights();	
		glPopMatrix();

		//Fork
		DrawFork();

	glPopMatrix();
}


void keyHandler(cg_help help,cg_globState globState,cg_key key) {

	// Tastatur abfragen
	// Achtung: einmaliges Betätigen funktioniert so nur mit glutIgnoreKeyRepeat(true) (siehe main())
	if (key.keyState(27))
	{
		exit(0); // Escape -> Programm beenden
	}
	else if (1 == key.keyState('f') || 1 == key.keyState('F'))
	{
		help.toggleFps();	// Framecounter on/off
	}
	else if (1 == key.keyState('h') || 1 == key.keyState('H') || 1 == key.specialKeyState(GLUT_KEY_F1))
	{
		help.toggle();	// Hilfetext on/off
	}
	else if (1 == key.keyState('k') || 1 == key.keyState('K'))
	{
		help.toggleKoordsystem();	// Koordinatensystem on/off
	}
	else if (1 == key.keyState('w') || 1 == key.keyState('W'))
	{
		globState.drawMode = (globState.drawMode == GL_FILL) ? GL_LINE : GL_FILL; // Wireframe on/off
	}
	else if (1 == key.keyState('l') || 1 == key.keyState('L'))
	{
		globState.lightMode = !globState.lightMode;	// Beleuchtung on/off
	}
	else if (1 == key.keyState('c') || 1 == key.keyState('C'))
	{
		globState.cullMode = !globState.cullMode; // Backfaceculling on/off
	}
	else if (1 == key.keyState('i') || 1 == key.keyState('I'))
	{
		globState.cameraHelper[0] = 0;	// Initialisierung der Kamera
		globState.cameraHelper[1] = 0;
	}
	else if (1 == key.keyState('s') || 1 == key.keyState('S')) {
		if (globState.shadeMode == GL_FLAT) {
			globState.shadeMode = GL_SMOOTH;
		}
		else globState.shadeMode = GL_FLAT;
	}
	else if (1 == key.specialKeyState(GLUT_KEY_F2))
	{
		if (cg_camera.CameraMode < CAMERAMODI::MODICOUNT - 1) {
			cg_camera.setCameraMode(cg_camera.CameraMode + 1);
		}
		else cg_camera.setCameraMode(0);
		cg_camera.dx = 0;
		cg_camera.dy = 0;
		cg_help::setCameraModeString(cg_camera.stringFromCameraMode());
		cg_help::setCameraModeControls(cg_camera.getCameraModeControls());
	}
	else if (1 == key.specialKeyState(GLUT_KEY_F3))
	{
		if (cg_globState::collision) cg_globState::collision = false;
		else cg_globState::collision = true;
		cg_help::setCollisionMode(cg_globState::collision);
	}
	else if (1 == key.specialKeyState(GLUT_KEY_F9)) {
		ceilingLight = !ceilingLight;
	}
	else if (1 == key.specialKeyState(GLUT_KEY_F10)) {
		globalLight = !globalLight;
	}

}


void processCameraMovement(cg_key key) {


	if (cg_mouse::buttonState(GLUT_LEFT_BUTTON))
	{
		if (cg_camera.CameraMode == CAMERAMODI::FAHRER)
		{
			cg_camera.dx += 0.001f * cg_mouse::moveX();
			cg_camera.dy += 0.001f * cg_mouse::moveY();
		}
		if (cg_camera.CameraMode == CAMERAMODI::WALK) {
			float alpha = cg_camera.walkpos.rot - 0.05f * cg_mouse::moveX();
			while (alpha > 360.0f) alpha -= 360.0f;
			while (alpha < 0.0f)   alpha += 360.0f;
			cg_camera.walkpos.rot = alpha;
			cg_camera.dy += 0.001f * cg_mouse::moveY();
			//glutWarpPointer(cg_globState::screenSize[0]/2 , cg_globState::screenSize[1] / 2); das is doof -> warppointer zählt auch als mausbewegung
		}
	}
	

	if (cg_mouse::buttonState(GLUT_MIDDLE_BUTTON))
	{
		if (cg_camera.CameraMode == CAMERAMODI::FOLLOW)
		{
			cg_camera.followerdist = Clamp(cg_camera.followerdist + (0.002 * cg_mouse::moveY()), 1.0f, 2.0f);
		}
		if (cg_camera.CameraMode == CAMERAMODI::TOPDOWN) {
			cg_camera.topdowndist = Clamp(cg_camera.topdowndist + (0.2 * cg_mouse::moveY()), 50.0f, 250.0f);
		}
	}

	if (cg_camera.CameraMode == CAMERAMODI::WALK) {
		float vec[3] = { sin(cg_camera.walkpos.rot * M_PI / 180.0f),    0,cos(cg_camera.walkpos.rot * M_PI / 180.0f) }; //richtungsvektor
		float dx = 0, dz = 0;
		//move forward
		if (key.specialKeyState(GLUT_KEY_UP)) {
			dx += vec[0] * cg_camera.speed;
			dz += vec[2] * cg_camera.speed;
			//cg_camera.walkpos.x += vec[0] * cg_camera.speed;
			//cg_camera.walkpos.z += vec[2] * cg_camera.speed;
		}
		//move backward
		if (key.specialKeyState(GLUT_KEY_DOWN)) {
			dx -= vec[0] * cg_camera.speed;
			dz -= vec[2] * cg_camera.speed;
			//cg_camera.walkpos.x -= vec[0] * cg_camera.speed;
			//cg_camera.walkpos.z -= vec[2] * cg_camera.speed;
		}
		//move left
		if (key.specialKeyState(GLUT_KEY_LEFT)) {
			dx += vec[2] * cg_camera.speed;
			dz -= vec[0] * cg_camera.speed;
			//cg_camera.walkpos.x += vec[2] * cg_camera.speed; 
			//cg_camera.walkpos.z -= vec[0] * cg_camera.speed;
		}
		//move right
		if (key.specialKeyState(GLUT_KEY_RIGHT)) {
			dx -= vec[2] * cg_camera.speed;
			dz += vec[0] * cg_camera.speed;
			//cg_camera.walkpos.x -= vec[2] * cg_camera.speed;
			//cg_camera.walkpos.z += vec[0] * cg_camera.speed;
		}

		bool collision = false;
		if (cg_globState::collision) {
			//collsion test
			for (auto obj : boundingareas) {
				if (obj.second.PointInArea(position::newPosition(cg_camera.walkpos.x + dx, 0, cg_camera.walkpos.z + dz))) collision = true;
			}
			for (auto regal : regalareas) {
				if (regal.second.PointInArea(position::newPosition(cg_camera.walkpos.x + dx, 0, cg_camera.walkpos.z + dz))) collision = true;
			}
			if (!collision) {
				cg_camera.walkpos.x += dx;
				cg_camera.walkpos.z += dz;
			}
		}
	}


	if (key.specialKeyState(GLUT_KEY_PAGE_UP) == 1) {
		if(ACTIVE_SECCAM < securitycam_positions.size()-1)
			ACTIVE_SECCAM++;
		else 
			ACTIVE_SECCAM = 0;
	}

}

/////////////////////////////////////////////////////////////////////////////////
//	Kamerafunktion
/////////////////////////////////////////////////////////////////////////////////
void setCamera()
{
	cg_mouse mouse;
	// Ansichtstransformationen setzen,
	// SetCamera() zum Beginn der Zeichenfunktion aufrufen
	double The, Phi, x, y, z;
	float alpha = myStapler.rot[1] * M_PI / 180.0f;
	float c = cos(alpha), s = sin(alpha);
	static double radius = 100.0f;
	// Maus abfragen
	if (cg_mouse::buttonState(GLUT_LEFT_BUTTON))
	{
		cg_globState::cameraHelper[0] += mouse.moveX();
		cg_globState::cameraHelper[1] += mouse.moveY();
	}
	if (cg_mouse::buttonState(GLUT_MIDDLE_BUTTON))
	{
		radius += 0.1 * mouse.moveY();
		radius = Clamp(radius, 50.0f, 350.0f);
	}
	Phi = 0.2 * cg_globState::cameraHelper[0] / cg_globState::screenSize[0] * M_PI + M_PI * 0.5;
	The = 0.2 * cg_globState::cameraHelper[1] / cg_globState::screenSize[1] * M_PI;
	x = radius * cos(Phi) * cos(The);
	y = radius * sin(The);
	z = radius * sin(Phi) * cos(The);
	int Oben = (The <= 0.5 * M_PI || The > 1.5 * M_PI) * 2 - 1;
	float vec2[3] = { x * c + s * z, y, -s * x + c * z };
	switch (cg_camera.CameraMode) {

	case TOPDOWN:
		cg_camera.pos.x = myStapler.pos[0];
		cg_camera.pos.y = myStapler.pos[1] + cg_camera.topdowndist;
		cg_camera.pos.z = myStapler.pos[2];

		cg_camera.lookat.x = myStapler.pos[0];
		cg_camera.lookat.y = myStapler.pos[1];
		cg_camera.lookat.z = myStapler.pos[2];
		gluLookAt(cg_camera.pos.x, cg_camera.pos.y, cg_camera.pos.z, cg_camera.lookat.x, cg_camera.lookat.y, cg_camera.lookat.z, 0, 0, 1);
		break;

	//spinnt noch etwas
	case ORBIT:
		cg_camera.pos.x = x;
		cg_camera.pos.y = Clamp(y,20.0f,500.0f);
		cg_camera.pos.z = z;

		cg_camera.lookat.x = myStapler.pos[0];
		cg_camera.lookat.y = myStapler.pos[1];
		cg_camera.lookat.z = myStapler.pos[2];
		gluLookAt(cg_camera.pos.x, cg_camera.pos.y, cg_camera.pos.z, cg_camera.lookat.x, cg_camera.lookat.y, cg_camera.lookat.z, 0, Oben, 0);

		break;

	case SECURITYCAM:
		cg_camera.pos.x = securitycam_positions[ACTIVE_SECCAM].x;
		cg_camera.pos.y = securitycam_positions[ACTIVE_SECCAM].y;
		cg_camera.pos.z = securitycam_positions[ACTIVE_SECCAM].z;

		if (AUTO_SECCAM) {
			cg_camera.lookat.x = myStapler.pos[0];
			cg_camera.lookat.y = myStapler.pos[1];
			cg_camera.lookat.z = myStapler.pos[2];
		}

		gluLookAt(cg_camera.pos.x, cg_camera.pos.y, cg_camera.pos.z, cg_camera.lookat.x, cg_camera.lookat.y, cg_camera.lookat.z, 0, Oben, 0);
		break;

	case FAHRER:
		cg_camera.pos.x = myStapler.cockpit[0] * c + myStapler.cockpit[2] * s + myStapler.pos[0];
		cg_camera.pos.y = myStapler.cockpit[1] + myStapler.pos[1];
		cg_camera.pos.z = -myStapler.cockpit[0] * s + myStapler.cockpit[2] * c + myStapler.pos[2];

		cg_camera.lookat.x = Clamp (cg_camera.dx*c , -1.0f,1.0f) + myStapler.pos[0];
		cg_camera.lookat.y = Clamp(myStapler.cockpit[1] - (cg_camera.dy) ,myStapler.cockpit[1]-2.0f,myStapler.cockpit[1]+ 2.5);
		cg_camera.lookat.z = Clamp(-cg_camera.dx * s, -1.0f,1.0f)  + myStapler.pos[2];
		gluLookAt(cg_camera.pos.x, cg_camera.pos.y, cg_camera.pos.z, cg_camera.lookat.x, cg_camera.lookat.y, cg_camera.lookat.z, 0, Oben, 0);

		break;

	case FOLLOW:
		cg_camera.pos.x = (myStapler.follower[0] * c + myStapler.follower[2]* s )*cg_camera.followerdist + myStapler.pos[0];
		cg_camera.pos.y = myStapler.follower[1]*cg_camera.followerdist + myStapler.pos[1];
		cg_camera.pos.z = (-myStapler.follower[0] * s + myStapler.follower[2] * c)* cg_camera.followerdist + myStapler.pos[2];

		cg_camera.lookat.x = myStapler.pos[0];
		cg_camera.lookat.y = myStapler.follower[1];
		cg_camera.lookat.z = myStapler.pos[2];
		gluLookAt(cg_camera.pos.x, cg_camera.pos.y, cg_camera.pos.z, cg_camera.lookat.x, cg_camera.lookat.y, cg_camera.lookat.z, 0, Oben, 0);

		break;

	case WALK: 
		
		float vec[3] = { sin(cg_camera.walkpos.rot * M_PI / 180.0f),    0,cos(cg_camera.walkpos.rot * M_PI / 180.0f) }; //richtungsvektor
		cg_camera.lookat.x = cg_camera.walkpos.x + vec[0];
		cg_camera.lookat.y = Clamp(cg_camera.walkpos.y - (cg_camera.dy), cg_camera.walkpos.y - 2.0f, cg_camera.walkpos.y + 2.5);
		cg_camera.lookat.z = cg_camera.walkpos.z + vec[2];
		gluLookAt(cg_camera.walkpos.x, cg_camera.walkpos.y, cg_camera.walkpos.z, cg_camera.lookat.x, cg_camera.lookat.y, cg_camera.lookat.z, 0, Oben, 0);
		break;
	}
}
	

