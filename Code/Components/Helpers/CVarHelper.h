#pragma once

#include <CryCore/StaticInstanceList.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/SharedString.h>

////////////////////////////////////////////////////////
// Physicalized bullet shot from weaponry, expires on collision with another object
////////////////////////////////////////////////////////
class CCVarHelperComponent final : public IEntityComponent
{
public:
	CCVarHelperComponent();
	virtual ~CCVarHelperComponent();

	// IEntityComponent
	virtual void Initialize() override;

	static void ReflectType(Schematyc::CTypeDesc<CCVarHelperComponent>& desc);
	// ~IEntityComponent

	void ExecuteConsoleCommand(Schematyc::CSharedString command, bool bSilentMode = false, bool bDeferExecution = false);
};