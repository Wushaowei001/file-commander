#ifndef CFILECOMMANDERPLUGIN_H
#define CFILECOMMANDERPLUGIN_H

#include "cpluginproxy.h"
#include "plugin_export.h"

class CFileCommanderPlugin;

typedef CFileCommanderPlugin* (*CreatePluginFunc)();

class PLUGIN_EXPORT CFileCommanderPlugin
{
public:
	enum PluginType {Viewer, Archive, Tool};

	CFileCommanderPlugin();
	virtual ~CFileCommanderPlugin() = 0;

	virtual PluginType type() = 0;
	virtual QString name() const = 0;

	void setProxy(CPluginProxy * proxy);

protected:
	// Is called after proxy has been set so that the plugin may init itself or the UI
	virtual void proxySet();

protected:
	CPluginProxy * _proxy;
};

#endif // CFILECOMMANDERPLUGIN_H
