#include "UnitRowHandleCustomization.h"
#include "UnitRowHandle.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "Widgets/Input/SComboBox.h"

TSharedRef<IPropertyTypeCustomization> FUnitRowHandleCustomization::MakeInstance()
{
    return MakeShareable(new FUnitRowHandleCustomization);
}

void FUnitRowHandleCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    RowNameHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDataTableRowHandle, RowName));

    RefreshRowNames();

    HeaderRow.NameContent()
        [
            PropertyHandle->CreatePropertyNameWidget()
        ]
        .ValueContent()
        [
            MakeRowNameWidget()
        ];
}

void FUnitRowHandleCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FUnitRowHandleCustomization::RefreshRowNames()
{
    RowNames.Empty();

    UDataTable* DataTable = LoadObject<UDataTable>(nullptr,
        TEXT("/Game/Framework/DataTable/DT_UnitSpawnData.DT_UnitSpawnData"));

    if (!DataTable) return;

    for (const FName& Name : DataTable->GetRowNames())
    {
        RowNames.Add(MakeShareable(new FName(Name)));
    }
}

TSharedRef<SWidget> FUnitRowHandleCustomization::MakeRowNameWidget()
{
    return SNew(SComboBox<TSharedPtr<FName>>)
        .OptionsSource(&RowNames)
        .OnGenerateWidget_Lambda([](TSharedPtr<FName> Item)
            {
                return SNew(STextBlock).Text(FText::FromName(*Item));
            })
        .OnSelectionChanged_Lambda([this](TSharedPtr<FName> Item, ESelectInfo::Type)
            {
                if (Item.IsValid() && RowNameHandle.IsValid())
                    RowNameHandle->SetValue(*Item);
            })
        .Content()
        [
            SNew(STextBlock)
                .Text_Lambda([this]() -> FText
                    {
                        FName CurrentName;
                        if (RowNameHandle.IsValid())
                            RowNameHandle->GetValue(CurrentName);
                        return FText::FromName(CurrentName);
                    })
        ];
}