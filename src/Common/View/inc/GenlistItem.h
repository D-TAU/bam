
#ifndef GENLISTITEM_H_
#define GENLISTITEM_H_

#include "ViewItem.h"
#include "GenlistItemClass.h"

#include <string>

class Genlist;

class GenlistItem
	: public ViewItem
{
	friend class Genlist;
	friend class GenlistItemClass;

public:
	GenlistItem(Genlist &parent, GenlistItemClassRef &itemClass);
	Genlist *getParent() const;
	GenlistItemClassRef getItemClass() const;

private:
	// C++ callback:
	virtual std::string getText(const char *part);
	virtual Evas_Object *getContent(const char *part);
	virtual bool getState(const char *part);
	virtual void onDel();

	// C callback:
	static char *get_text_cb(void *data, Evas_Object *obj, const char *part);
	static Evas_Object *get_content_cb(void *data, Evas_Object *obj, const char *part);
	static Eina_Bool get_state_cb(void *data, Evas_Object *obj, const char *part);
	static void del_cb(void *data, Evas_Object *obj);

protected:
	virtual ~GenlistItem();

	// ViewItem:
	virtual void onDestroy(ViewItem &item);

private:
	Genlist *m_pGenlist;
	GenlistItemClassRef m_ItemClass;
};

#endif /* GENLISTITEM_H_ */
