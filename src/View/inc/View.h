#ifndef VIEW_H_
#define VIEW_H_

#include <Elementary.h>

class View
{
public:
	inline Evas_Object *getEo();
	inline operator Evas_Object*() const;

	void expand();
	inline void show();
	inline void hide();
	inline void destroy();
	inline void setContent(Evas_Object *obj, const char *part = nullptr);
	inline Evas_Object *getContent(const char *part = nullptr) const;

protected:
	View();
	virtual ~View();

	void setEo(Evas_Object *obj);
	virtual void onDestroy(View &view);

private:
	// Evas_Object callbacks:
	void onFree(Evas_Object *obj, void *eventInfo);

private:
	Evas_Object *m_pEo;
};

inline Evas_Object *View::getEo()
{
	return m_pEo;
}

inline View::operator Evas_Object*() const
{
	return m_pEo;
}

inline void View::show()
{
	evas_object_show(m_pEo);
}

inline void View::hide()
{
	evas_object_hide(m_pEo);
}

inline void View::destroy()
{
	evas_object_del(m_pEo);
}

inline void View::setContent(Evas_Object *obj, const char *part)
{
	elm_object_part_content_set(m_pEo, part, obj);
}

inline Evas_Object *View::getContent(const char *part) const
{
	return elm_object_part_content_get(m_pEo, part);
}

#endif /* VIEW_H_ */
