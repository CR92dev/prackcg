#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <map>
#include "colors.h"
#include "light.h"
#include "wavefront.h"
#include "UsefullStuff.h"

#pragma region Region Define Objects

constexpr auto RESPATH = ".\\resources";
constexpr auto RES_HALL = "\\hall\\";
constexpr auto RES_STAPLER = "\\stapler\\";
constexpr auto RES_INDOOR = "\\indoor\\";
constexpr auto HALL_OBJECTS_COUNT = 9;
constexpr auto STAPLER_OBJECTS_COUNT = 12;
constexpr auto INDOOR_OBJECTS_COUNT = 2;


enum INDOORSTUFF {
	EUROPALETTE = 0,
	EUROPALETTE_FOUR
};

map<int, string> objectfiles_indoor = {
	{EUROPALETTE, "europalette.obj"},
	{EUROPALETTE_FOUR, "eurofour.obj"}
};

map<int, color> colors_indoor = {
	{EUROPALETTE, brown},
	{EUROPALETTE_FOUR, brown}
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
	{0, position::newPosition(0.0f,0.0f,0.0f)},
	{1, position::newPosition(0.0f,0.0f,5.0f)},
	{2, position::newPosition(0.0f,0.0f,10.0f)},
	{3, position::newPosition(0.0f,0.0f,15.0f)},
};

map<int, position> eurofour_positions = {
	{0, position::newPosition(-42.0f,0.0f,42.0f)},
	{1, position::newPosition(-42.0f,0.0f,50.0f)},
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
	HALL_ROOF
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
	{HALL_ROOF,"hall_roof.obj"}
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
	{HALL_ROOF, darkorange}

};

enum STAPLEROBJ {
	KAROSSE = 0,
	REELS_FRONT,
	REEL_BACK,
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

	float cockpit[3] = { 0 ,7.8f,3 };
	float follower[3] = { 0,15, 16 };


	Stapler()
	{
		wheelrot_front = wheelrot_back = 0;
		speed = 0; steer = 0;
		pos[0] = pos[1] = pos[2] = 0;
		rot[0] = rot[1] = rot[2] = 0;
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

	float bb_pos[3] = { 0.0f, myStapler.karosse_floordist + 0.5f ,-7.6f };
	float bb_width = 1.8f;

	Gabel() {
		liftspeed = forkspeed = 0;
		lifthigh = 0;
		holderhigh = 0;
		stickoffset = 0;
	}
} myGabel;

map<int, string> objectfiles_stapler = {
	{KAROSSE, "stapler_karosse.obj"},
	{REELS_FRONT,"stapler_reels_front.obj"},
	{REEL_BACK,"stapler_reel_back.obj"},
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
	{KAROSSE, yellow}
};

static cg_light front_lights[2] = { 1, 2 };
object3D* objects_hall[HALL_OBJECTS_COUNT];
object3D* objects_stapler[STAPLER_OBJECTS_COUNT];
object3D* objects_indoor[INDOOR_OBJECTS_COUNT];



#pragma endregion 

void Load_Objects(void) {

	//load hall objects and init colors
	for (auto obj : objectfiles_hall) {
		char file[255] = "";
		strcat(file, RESPATH);
		strcat(file, RES_HALL);
		strcat(file, obj.second.c_str());

		objects_hall[obj.first] = loadobject(file, false);
		if (colors_hall.count(obj.first) > 0) {
			set_obj_material(objects_hall[obj.first], colors_hall[obj.first].fRed, colors_hall[obj.first].fGreen, colors_hall[obj.first].fBlue, 1.0f, 0.0f, 128.0f, 0.0f);
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


#endif //OBJECTS
