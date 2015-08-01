
#ifndef BamApplicatin_h
#define BamApplicatin_h

#include "Window.h"
#include <app.h>

// TODO:
class AccountManager;

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
	bool onAppCreate();
	void onAppTerminate();
	void onAppPause();
	void onAppResume();
	void onAppControl(app_control_h app_control);

private:
	Window *m_pWindow;
};

#endif // BamApplicatin_h
