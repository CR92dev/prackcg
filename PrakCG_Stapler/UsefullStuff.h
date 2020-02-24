#ifndef USEFULLSTUFF_H
#define USEFULLSTUFF_H

struct position {
	float x;
	float y;
	float z;

	float rot; // initial rot around the y axis

	static position newPosition(float x_, float y_, float z_)
	{
		position p = { x_, y_, z_ };
		return p;
	}

	static position newPosition(float x_, float y_, float z_, float rot_) {
		position p = { x_, y_, z_ , rot_ };
		return p;
	}

	bool equals(position p) {
		return x == p.x && y == p.y && z == p.z;
	}
};

struct area {

	position A;
	position B;

	static area newArea(position A_, position B_) {
		area a = { A_,B_ };
		return a;
	}

	bool PointInArea(position p) {

		//da wir uns nicht in Y richtung bewegen reicht ein check der x,z fläche

		if ((p.x <= A.x && p.x >= B.x) || p.x <= B.x && p.x >= A.x) {   //punkt liegt innerhalb der x Werte der Area
			if ((p.z <= A.z && p.z >= B.z) || p.z <= B.z && p.z >= A.z) // punkt liegt innerhalb der z Were der Area
				return true;
			else return false;
		}
		else return false;
	}
};



#endif // USEFULLSTUFF_H
