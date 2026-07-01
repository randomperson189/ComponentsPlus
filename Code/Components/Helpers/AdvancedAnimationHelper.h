#pragma once

#include <CryCore/StaticInstanceList.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/SharedString.h>

////////////////////////////////////////////////////////
// Physicalized bullet shot from weaponry, expires on collision with another object
////////////////////////////////////////////////////////
class CAdvancedAnimationHelperComponent final : public IEntityComponent
{
public:
	CAdvancedAnimationHelperComponent();
	virtual ~CAdvancedAnimationHelperComponent();

	// IEntityComponent
	virtual void Initialize() override;

	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CAdvancedAnimationHelperComponent>& desc)
	{
		desc.SetGUID("{1DF944B1-3802-41D6-B56E-D90AB368511E}"_cry_guid);

		desc.SetEditorCategory("Utilities");
		desc.SetLabel("Advanced Animation Helper");
		desc.SetDescription("Component to help with advanced animation");
	}
	// ~IEntityComponent
};