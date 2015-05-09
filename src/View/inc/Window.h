#ifndef WINDOW_H_
#define WINDOW_H_

#include "View.h"

class Window
	: public View
{
public:
	Window();

	Evas_Object *getWindowEo() const;
	Evas_Object *getConformEo() const;
	Evas_Object *getBgEo() const;
	void setContent(Evas_Object *content);
	Evas_Object *getContent() const;

private:
	virtual ~Window();
	void create();

private:
	Evas_Object *m_pWin;
	Evas_Object *m_pConform;
	Evas_Object *m_pBg;
};

#endif /* WINDOW_H_ */
