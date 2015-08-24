
#include "Bam.h"
#include "Application.h"
#include "AccountController.h"
#include "CallbackAssist.h"

Application::Application()
	: m_pWindow(nullptr)
	, m_pNaviFrame(nullptr)
	, m_db(nullptr)
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

	//FIXME in-memory database should be replaced by database file
	m_db = new sqlite::database(":memory:");

	// Create window:
	m_pWindow = new Window;
	m_pWindow->show();
	eext_object_event_callback_add(*m_pWindow, EEXT_CALLBACK_BACK, EEXT_EVET_CB(Application, onHwBackButtonPressed), this);
	eext_object_event_callback_add(*m_pWindow, EEXT_CALLBACK_MORE, EEXT_EVET_CB(Application, onHwMoreButtonPressed), this);

	// Create Naviframe:
	m_pNaviFrame = new NaviFrame(*m_pWindow);
	m_pNaviFrame->show();


	// Create AccountController
	AccountController *account = new AccountController(*this, m_db, *m_pNaviFrame);

	m_pNaviFrame->push(account);
	m_pWindow->setContent(*m_pNaviFrame);

	return true;
}

void Application::onHwBackButtonPressed(Evas_Object *obj, void *event_info)
{
	NaviFrameItem *topItem = m_pNaviFrame->getTopItem();
	NaviFrameItem *bottomItem = m_pNaviFrame->getBottomItem();

	if(topItem == bottomItem) // Last frame
		Application::exit();
	else
		m_pNaviFrame->pop();
}

void Application::onHwMoreButtonPressed(Evas_Object *obj, void *event_info)
{

}

void Application::onAppTerminate()
{
	BAM_LOG("App terminate");

	m_pWindow->destroy();

	delete m_db;
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
