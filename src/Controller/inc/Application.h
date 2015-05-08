
#ifndef BamApplicatin_h
#define BamApplicatin_h

#include "Account.h"
#include <app.h>

class Application
{
public:
	Application();
	~Application();

	Account &getEngine();
	const Account &getEngine() const;

	int run(int argc, char *argv[]);
	void exit();

private:
	bool onAppCreate();
	void onAppTerminate();
	void onAppPause();
	void onAppResume();
	void onAppControl(app_control_h app_control);

private:
	Account m_Account;
};

#endif // BamApplicatin_h
