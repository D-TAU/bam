#ifndef GENLIST_H_
#define GENLIST_H_

#include "View.h"
#include "GenlistItem.h"

class IGenlistListener;

class Genlist
	: public View
{
public:
	Genlist(Evas_Object *parent);
	virtual ~Genlist();

	void setListener(IGenlistListener *listener);
	void appendItem(GenlistItem &item, GenlistItem *parentItem = nullptr, Elm_Genlist_Item_Type type = ELM_GENLIST_ITEM_NONE);

private:
	void onSelected(Evas_Object *obj, void *eventInfo);

private:
	IGenlistListener *m_pListener;
};

class IGenlistListener
{
public:
	virtual ~IGenlistListener() {}

	virtual void onSelected(Genlist &genlist, GenlistItem &item) {};
};

#endif /* GENLIST_H_ */
