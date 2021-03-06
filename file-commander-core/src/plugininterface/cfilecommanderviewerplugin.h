#ifndef CFILECOMMANDERVIEWERPLUGIN_H
#define CFILECOMMANDERVIEWERPLUGIN_H

#include "cfilecommanderplugin.h"
#include "cpluginwindow.h"

class PLUGIN_EXPORT CFileCommanderViewerPlugin : public CFileCommanderPlugin
{
public:
	CFileCommanderViewerPlugin();
	virtual ~CFileCommanderViewerPlugin() = 0;

	virtual bool canViewCurrentFile() const = 0;
	virtual CPluginWindow* viewCurrentFile() = 0;

	virtual PluginType type();
};

#endif // CFILECOMMANDERVIEWERPLUGIN_H
