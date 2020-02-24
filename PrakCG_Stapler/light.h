#ifndef LIGHT_H
#define LIGHT_H



#include "Include/freeglut.h"



/////////////////////////////////////////////////////////////////////////////////
//	Modellierungsfunktionen
/////////////////////////////////////////////////////////////////////////////////
// Material setzen (nur fuer Beleuchtungsmodus)
void SetMaterial ( GLenum face, GLfloat amb[4], GLfloat diff[4], GLfloat spec[4], GLfloat shine, GLfloat emis[4] );

// Parameter einer Lichtquelle setzen (nur fuer Beleuchtungsmodus)
void SetLightColors ( GLenum lightid, GLfloat amb[4], GLfloat diff[4], GLfloat spec[4] );

// Lichtquellen setzen
void SetLights (bool enableGlobalLight);



class cg_light
{
public:
	// Konstructior, id zwischen 0-7 muss uebergeben werden
	cg_light ( int num );


	// wenn w=0 -> direktionales Licht, Richtung wird eingespeichert
	// wenn w=1 -> Punktlichtquelle, Positon wird eingespeichert
	void setPosition ( float x, float y, float z, float w );

	// ambienten Anteil der Lichtfarbe einspeichern
	void setAmbient ( float r, float g, float b, float a );
	// diffusen Anteil der Lichtfarbe einspeichern
	void setDiffuse ( float r, float g, float b, float a );
	// specularen Anteil der Lichtfarbe einspeichern
	void setSpecular ( float r, float g, float b, float a );

	// Richtung, Oeffnungswinkel und exponent einspeichern (nur bei Punktlichtquelle sinnvoll)
	void setSpotlight ( float directionX, float directionY, float directionZ, float cutoff, float exponent );

	// Abschwächungsfaktoren der Lichtintensität einspeichern
	void setAttentuation ( float constant, float linear, float quadric );

	// Licht einschalten und mit den bisher eingespeicherten Parametern rendern
	void draw ();

	// Lichtquelle ausschalten
	void disable ();

	auto getPosX() { return pos[0]; }
	auto getPosY() { return pos[1]; }
	auto getPosZ() { return pos[2]; }

private:
	int id;
	float pos[4];
	float amb[4];
	float diff[4];
	float spec[4];
	float spot[5];
	float att[3];
};

#endif // LIGHT_H
