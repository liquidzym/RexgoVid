package rexgo.net.liquid;

import processing.core.PApplet;
import processing.core.PConstants;
import processing.core.PImage;

public class RexgoVid implements PConstants {

	private int w;

	private int h;

	private PImage img;

	private PApplet parent;

	private int rate;

	public RexgoVid(PApplet _p) {
		parent = _p;
	}

	static {
		System.loadLibrary("RexgoVid");
	}

	// DLL native calls
	native void native_start(int w, int h, int rate);

	native void native_stop();

	native void native_update();

	native void native_imageCopy(int[] dst);

	// Library stuff
	public void start(int _w, int _h, int _rate) {
		w = _w;
		h = _h;
		rate = _rate;
		img = parent.createImage(w, h, RGB);

		native_start(w, h, rate);
	}

	public void stop() {
		native_stop();
	}

	public void imageCopy(int[] dst) {
		native_imageCopy(dst);
	}

	public void update() {
		native_update();
	}

}
