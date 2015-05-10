#ifndef CALLBACKASSIST_H_
#define CALLBACKASSIST_H_

#define EVAS_OBJECT_EVET_CB(ClassName, method) [](void *data, Evas *e, Evas_Object *obj, void *event_info) \
{																										   \
	static_cast<ClassName*>(data)->method(obj, event_info);											       \
}

#define EVAS_SMART_EVET_CB(ClassName, method) [](void *data, Evas_Object *obj, void *event_info) \
{																								 \
	static_cast<ClassName*>(data)->method(obj, event_info);										 \
}

#define EEXT_EVET_CB(ClassName, method) [](void *data, Evas_Object *obj, void *event_info) \
{																						   \
	static_cast<ClassName*>(data)->method(obj, event_info);								   \
}

#endif /* CALLBACKASSIST_H_ */
