
#ifndef BamApplicatin_h
#define BamApplicatin_h

#include "Window.h"
#include "NaviFrame.h"
#include <app.h>

// TODO:
class AccountManager;
namespace sqlite
{
    class database;
};

class Application
{
public:
	Application();
	~Application();

	AccountManager &getEngine();
	const AccountManager &getEngine() const;

	Window &getWindow();

	int run(int argc, char *argv[]);
	void exit();

private:
	// Application:
	bool onAppCreate();
	void onAppTerminate();
	void onAppPause();
	void onAppResume();
	void onAppControl(app_control_h app_control);

	// HW buttons:
	void onHwBackButtonPressed(Evas_Object *obj, void *event_info);
	void onHwMoreButtonPressed(Evas_Object *obj, void *event_info);

private:
	Window *m_pWindow;
	NaviFrame *m_pNaviFrame;
	/*accounts manager*/
	AccountManager * m_pAccountManager;
};

#endif // BamApplicatin_h
