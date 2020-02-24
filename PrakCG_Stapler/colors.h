#pragma once

struct color {

	float fRed;
	float fGreen;
	float fBlue;

	color() {
		fRed = 0;
		fGreen = 0;
		fBlue = 0;
	}

	color(int fr, int fg, int fb) {
		fRed = fr / 255.0f;
		fGreen = fg / 255.0f;
		fBlue = fb / 255.0f;
	}
};




//Definition der Farben


color lightpink(255, 182, 193);
color pink(255, 192, 203);
color crimson(220, 20, 60);
color lavenderblush(255, 240, 245);
color hotpink(255, 105, 180);
color palevioletred(219, 112, 147);
color deeppink(255, 20, 147);
color mediumvioletred(199, 21, 133);
color orchid(218, 112, 214);
color thistle(216, 191, 216);
color plum(221, 160, 221);
color violet(238, 130, 238);
color magenta(255, 0, 255);
color fuchsia(255, 0, 255);
color darkmagenta(139, 0, 139);
color purple(128, 0, 128);
color mediumorchid(186, 85, 211);
color darkviolet(148, 0, 211);
color darkorchid(153, 50, 204);
color indigo(75, 0, 130);
color blueviolet(138, 43, 226);
color mediumpurple(147, 112, 219);
color mediumslateblue(123, 104, 238);
color slateblue(106, 90, 205);
color darkslateblue(72, 61, 139);
color navy(0, 0, 128);
color midnightblue(25, 25, 112);
color mediumblue(0, 0, 205);
color blue(0, 0, 255);
color lavender(230, 230, 250);
color ghostwhite(248, 248, 255);
color darkblue(0, 0, 139);
color royalblue(65, 105, 225);
color cornflowerblue(100, 149, 237);
color lightsteelblue(176, 196, 222);
color slategray(112, 128, 144);
color lightslategray(119, 136, 153);
color dodgerblue(30, 144, 255);
color aliceblue(240, 248, 255);
color steelblue(70, 130, 180);
color lightskyblue(135, 206, 250);
color skyblue(135, 206, 235);
color deepskyblue(0, 191, 255);
color lightblue(173, 216, 230);
color powderblue(176, 224, 230);
color cadetblue(95, 158, 160);
color darkturquoise(0, 206, 209);
color azure(240, 255, 255);
color lightcyan(224, 255, 255);
color paleturquoise(175, 238, 238);
color cyan(0, 255, 255);
color aqua(0, 255, 255);
color darkslategray(47, 79, 79);
color darkcyan(0, 139, 139);
color teal(0, 128, 128);
color mediumturquoise(72, 209, 204);
color lightseagreen(32, 178, 170);
color turquoise(64, 224, 208);
color aquamarine(127, 255, 212);
color mediumaquamarine(102, 205, 170);
color mediumspringgreen(0, 250, 154);
color mintcream(245, 255, 250);
color springgreen(0, 255, 127);
color mediumseagreen(60, 179, 113);
color seagreen(46, 139, 87);
color honeydew(240, 255, 240);
color lightgreen(144, 238, 144);
color palegreen(152, 251, 152);
color darkseagreen(143, 188, 143);
color limegreen(50, 205, 50);
color lime(0, 255, 0);
color forestgreen(34, 139, 34);
color green(0, 128, 0);
color darkgreen(0, 100, 0);
color chartreuse(127, 255, 0);
color lawngreen(124, 252, 0);
color greenyellow(173, 255, 47);
color darkOlivegreen(85, 107, 47);
color yellowgreen(154, 205, 50);
color olivedrab(107, 142, 35);
color beige(245, 245, 220);
color lightgoldenrodyellow(250, 250, 210);
color ivory(255, 255, 240);
color lightyellow(255, 255, 224);
color yellow(255, 255, 0);
color olive(128, 128, 0);
color darkkhaki(189, 183, 107);
color palegoldenrod(238, 232, 170);
color lemonchiffon(255, 250, 205);
color khaki(240, 230, 140);
color gold(255, 215, 0);
color cornsilk(255, 248, 220);
color goldenrod(218, 165, 32);
color darkgoldenrod(184, 134, 11);
color floralwhite(255, 250, 240);
color oldlace(253, 245, 230);
color wheat(245, 222, 179);
color orange(255, 165, 0);
color moccasin(255, 228, 181);
color papayawhip(255, 239, 213);
color blanchedalmond(255, 235, 205);
color navajowhite(255, 222, 173);
color antiquewhite(250, 235, 215);
color tann(210, 180, 140);
color burlywood(222, 184, 135);
color bisque(255, 228, 196);
color darkorange(255, 140, 0);
color linen(250, 240, 230);
color peru(205, 133, 63);
color peachpuff(255, 218, 185);
color sandybrown(244, 164, 96);
color chocolate(210, 105, 30);
color saddlebrown(139, 69, 19);
color seashell(255, 245, 238);
color sienna(160, 82, 45);
color lightsalmon(255, 160, 122);
color coral(255, 127, 80);
color orangered(255, 69, 0);
color darksalmon(233, 150, 122);
color tomato(255, 99, 71);
color mistyrose(255, 228, 225);
color salmon(250, 128, 114);
color snow(255, 250, 250);
color lightcoral(240, 128, 128);
color rosybrown(188, 143, 143);
color indianred(205, 92, 92);
color red(255, 0, 0);
color brown(165, 42, 42);
color firebrick(178, 34, 34);
color darkred(139, 0, 0);
color maroon(128, 0, 0);
color white(255, 255, 255);
color whitesmoke(245, 245, 245);
color gainsboro(220, 220, 220);
color lightgrey(211, 211, 211);
color silver(192, 192, 192);
color darkgray(169, 169, 169);
color gray(128, 128, 128);
color dimgray(105, 105, 105);
color black(0, 0, 0);
