#include "Project_EEditor.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "UnitRowHandleCustomization.h"
#include "UnitRowHandle.h"

IMPLEMENT_MODULE(FProject_EEditorModule, Project_EEditor)

void FProject_EEditorModule::StartupModule()
{
    
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomPropertyTypeLayout(
        FUnitRowHandle::StaticStruct()->GetFName(),
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FUnitRowHandleCustomization::MakeInstance)
    );
}

void FProject_EEditorModule::ShutdownModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.UnregisterCustomPropertyTypeLayout(FUnitRowHandle::StaticStruct()->GetFName());
}