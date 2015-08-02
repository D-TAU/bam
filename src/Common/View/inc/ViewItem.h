#ifndef VIEWITEM_H_
#define VIEWITEM_H_

#include <Elementary.h>

class ViewItem
{
public:
	inline Elm_Object_Item *getElmItem() const;
	inline operator Elm_Object_Item*() const;

	inline void setContent(Evas_Object *content, const char *part = nullptr);
	inline Evas_Object *getContent(const char *part = nullptr) const;
	inline void setData(void *data);
	inline void *getData() const;

protected:
	ViewItem();
	virtual ~ViewItem();
	virtual void onDestroy(ViewItem &item);
	void setElmItem(Elm_Object_Item *item);

private:
	void onDel(Evas_Object *obj, void *event_info);


private:
	Elm_Object_Item *m_pItem;
};

inline Elm_Object_Item *ViewItem::getElmItem() const
{
	return m_pItem;
}

inline ViewItem::operator Elm_Object_Item*() const
{
	return m_pItem;
}

inline void ViewItem::setContent(Evas_Object *content, const char *part)
{
	elm_object_item_part_content_set(m_pItem, part, content);
}

inline Evas_Object *ViewItem::getContent(const char *part) const
{
	return elm_object_item_part_content_get(m_pItem, part);
}

inline void ViewItem::setData(void *data)
{
	elm_object_item_data_set(m_pItem, data);
}

inline void *ViewItem::getData() const
{
	return elm_object_item_data_get(m_pItem);
}

#endif /* VIEWITEM_H_ */
