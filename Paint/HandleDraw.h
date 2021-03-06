#pragma once
#ifndef _HANDLE_DRAW_H_
#define _HANDLE_DRAW_H_

#include <commdlg.h>
#include <vector>
#include <memory>

#include "HandleEdit.h"
#include "HandleEvent.h"
#include "Shape.h"

class HandleDraw {

private:	//private attribute
	//Color while drawing
	static CHOOSECOLOR  _cc;
	static COLORREF  _acrCustClr[16];
	static DWORD  _color;
	static HBRUSH  _hbrush;

	//shapes which are being dragged
	static std::vector<std::shared_ptr<Shape>> _draggedShapes;

private:	//friend class (to access _draggedShapes);
	friend HandleEdit;

private:	//private utilities

	//Helper for drawIntoMemDC
	// Get a ptr to a figure which was generated by fromX, fromY, toX, toY
	static std::shared_ptr<figure::Figure> getFigureToDraw(int, int, int, int, int);

	//Get figure from getFigureToDraw() and draw in to memoryDc
	static void drawIntoMemDC(HDC&, Pen&, int = HandleEvent::typeFigure,
		int = HandleEvent::fromX, int = HandleEvent::fromY, 
		int = HandleEvent::toX, int = HandleEvent::toY);

	//Initialize for void draw(HWND&)
	//static void initToDraw(HDC&, HDC&, HBITMAP&);

	//Help Delete/Cut/Copy/Paste travel in states
	static void traversalStates(void(*)(int, int, std::vector<std::shared_ptr<Shape>>&), std::vector<std::shared_ptr<Shape>>& );

	//Choose color from menu
	static void chooseColor(HWND&);

private:	//private mode process

	/*
	static void modePreview(HDC&, HDC&, int);	//Preview mode process
	static void modeDraw(HDC&, HDC&, int);		//Draw mode process
	static void modeSelect(HDC&, HDC&, int);		//Select mode process
	static void modeDrag(HDC&, HDC&, bool, int);	//Drag mode process
	static void modeChangeColor(HDC&, HDC&, int);	//Change color mode process
	static void modeDelete(HDC&, HDC&, int);
	*/

public:	//getter and setter
	//Return the current color
	static DWORD color();

public: //Helper
	//After dragging, if there are some selected shape
	//	=> push back into states and clear all current selected shapes
	static void finishToDrag(std::vector<std::vector<std::shared_ptr<Shape>>>&);

	//Initialize for onPaint
	static void initToDraw(HDC&, HDC&, HBITMAP&);


public:		//Public onPaint method

	static void modePreview(HDC&, HDC&, int);		//Preview mode process
	static void modeDraw(HDC&, HDC&, int);			//Draw mode process
	static void modeDrawPause(HDC&, HDC&, int);		//Pause after dragging while in draw mode process
	static void modeSelect(HDC&, HDC&, int);		//Select mode process
	static void modeDrag(HDC&, HDC&, bool, int);	//Drag mode process
	static void modeChangeColor(HDC&, HDC&, int);	//Change color mode process
	
public:		//Activate
	static void activateSelect(int&);
	static void activateDrawShape(int&, int);
	static void activateChooseColor(HWND&, int&);
};



#endif // !_HANDLE_DRAW_H_




