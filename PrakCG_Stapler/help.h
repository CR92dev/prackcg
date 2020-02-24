#pragma once
#include <list>
#include <string>

#ifndef HELP_H
#define HELP_H


// *** Help-Module, PrakCG Template

#ifdef __EXPORT_HELP

std::list<std::string> Settings{
	"Settings",
	"",
	"f,F    - Framerate (An/Aus)",
	"c,C    - Backfaceculling(An/Aus)",
	"s,S    - Zwischnen Smooth und Flat-Shading wechseln",
	"F2     - Cameramodus wechseln",
	"l,L    - Zwischen Light und Shadingmodus wechseln",
	"F10    - Globales Licht (An/Aus)",
	"F3     - Kolissionserkennung (An/Aus)",
	"h,H,F1 - Hilfe (An/Aus)",
	"w,W    - WireFrame (An/Aus)",
	"k,K    - Koordinatensystem (An/Aus)",
	"", "", "", "",
	"ESC    - Beenden",
};

const char *spalte2[] =
{
	"Settings:",
	"",
	"f,F    - Framerate (An/Aus)",
	"c,C    - Backfaceculling(An/Aus)",
	"s,S    - Zwiscnen Smooth und Flat-Shading wechseln",
	"F2     - Cameramodus wechseln",
	"l,L    - Licht global (An/Aus)",
	"h,H,F1 - Hilfe (An/Aus)",
	"w,W    - WireFrame (An/Aus)",
	"k,K    - Koordinatensystem (An/Aus)",
	"", "", "", "",
	"ESC    - Beenden",

	NULL
};
#endif


#ifndef	M_PI				// Pi
#define M_PI 3.14159265358979323846
#endif
#ifndef SGN					// Vorzeichen bestimmen
#define SGN(y) (((y) < 0) ? -1 : ((y) > 0))
#endif
#ifndef MIN					// Minimum bestimmen
#define MIN(a,b) ((a) > (b))? (b) : (a)
#endif
#ifndef MAX					// Maximum bestimmen
#define MAX(a,b) ((a) > (b))? (a) : (b)
#endif


class cg_help
{
public:
	void  toggle ();
	void  toggleFps ();
	void  setTitle ( char *t );
	void  setWireframe ( bool wf );
	bool  isWireframe ();
	void  toggleKoordsystem ();
	bool  isKoordsystem ();
	float getFps ();
	void  draw ();
	void  drawKoordsystem ( GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax, GLfloat zmin, GLfloat zmax );
	void  static setCameraModeString(char* c);
	void  static setCameraModeControls(std::list<std::string> description);
	void static setCollisionMode(bool enabled);

private:
	static bool  showhelp, showfps, wireframe, koordsystem;
	static int   frames;
	static float fps, bg_size, shadow;
	static const char  *title;
	void drawBackground();
	void printText ( float x, float y, const char *text, void *font = GLUT_BITMAP_HELVETICA_18 );
	void printText ( float x, float y, const char *text, float r, float g, float b, void *font = GLUT_BITMAP_HELVETICA_18 );
	void printTextShadow ( float x, float y, const char *text, float r, float g, float b, void *font = GLUT_BITMAP_HELVETICA_18 );
	void printFps ( float x, float y, void *font = GLUT_BITMAP_HELVETICA_18 );
	void printCameraMode(float x, float y, void* font = GLUT_BITMAP_HELVETICA_18);
	void printCollisionMode(float x, float y,void* font = GLUT_BITMAP_HELVETICA_18);
};


#endif	// HELP_H
