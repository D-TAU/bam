#ifndef GENLISTITEMCLASS_H_
#define GENLISTITEMCLASS_H_

#include <Elementary.h>
#include <memory>

class GenlistItemClass
{

public:
	GenlistItemClass(const char *itemStyle, const char *decorateItemStyle = nullptr, const char *decorateAllItemStyle = nullptr);
	~GenlistItemClass();

	inline operator const Elm_Genlist_Item_Class*() const;
	inline Elm_Genlist_Item_Class *getGenlistItemClass() const;

private:
	void registerCb();

private:
	Elm_Genlist_Item_Class *m_pClass;
};

typedef std::shared_ptr<GenlistItemClass> GenlistItemClassRef;

inline GenlistItemClass::operator const Elm_Genlist_Item_Class*() const
{
	return m_pClass;
}

inline Elm_Genlist_Item_Class *GenlistItemClass::getGenlistItemClass() const
{
	return m_pClass;
}

#endif /* GENLISTITEMCLASS_H_ */
