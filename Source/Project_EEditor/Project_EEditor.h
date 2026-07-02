#pragma once

#include "Modules/ModuleManager.h"

class FProject_EEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};