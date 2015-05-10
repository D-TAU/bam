
#include "Bam.h"
#include "Application.h"
#include "AccountView.h"

Application::Application()
	: m_Account()
	, m_pWindow(nullptr)
{
	BAM_LOG("App create");
}

Application::~Application()
{
	BAM_LOG("App destroy");
}

int Application::run(int argc, char *argv[])
{
	BAM_LOG("App run");

	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};

	event_callback.create = [](void *data)->bool
	{
		return static_cast<Application*>(data)->onAppCreate();
	};

	event_callback.terminate = [](void *data)
	{
		static_cast<Application*>(data)->onAppTerminate();
	};

	event_callback.pause = [](void *data)
	{
		static_cast<Application*>(data)->onAppPause();
	};

	event_callback.resume = [](void *data)
	{
		static_cast<Application*>(data)->onAppResume();
	};

	event_callback.app_control = [](app_control_h app_control, void *data)
	{
		static_cast<Application*>(data)->onAppControl(app_control);
	};

	ret = ui_app_main(argc, argv, &event_callback, this);

	if (ret != APP_ERROR_NONE)
		BAM_LOG_ERROR("ui_app_main() is failed. err = %d", ret);

	return ret;
}

Account &Application::getEngine()
{
	return m_Account;
}

const Account &Application::getEngine() const
{
	return m_Account;
}

void Application::exit()
{
	BAM_LOG("App request exit");
	ui_app_exit();
}

Window &Application::getWindow()
{
	return *m_pWindow;
}

bool Application::onAppCreate()
{
	BAM_LOG("App create");

	m_pWindow = new Window;
	m_pWindow->show();

	AccountView *accountView = new AccountView(*m_pWindow);
	accountView->show();
	accountView->expand();

	m_pWindow->setContent(*accountView);

	return true;
}

void Application::onAppTerminate()
{
	BAM_LOG("App terminate");

	m_pWindow->destroy();
}

void Application::onAppPause()
{
	BAM_LOG("App pause");
}

void Application::onAppResume()
{
	BAM_LOG("App resume");
}

void Application::onAppControl(app_control_h app_control)
{
	BAM_LOG("App control");
}
