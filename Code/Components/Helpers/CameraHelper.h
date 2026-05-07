#pragma once

#include <CryCore/StaticInstanceList.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/SharedString.h>

////////////////////////////////////////////////////////
// Physicalized bullet shot from weaponry, expires on collision with another object
////////////////////////////////////////////////////////
class CCameraHelperComponent final : public IEntityComponent
{
public:
	CCameraHelperComponent();
	virtual ~CCameraHelperComponent();

	// IEntityComponent
	virtual void Initialize() override;

	static void ReflectType(Schematyc::CTypeDesc<CCameraHelperComponent>& desc);
	// ~IEntityComponent

	void SetFOV(CryTransform::CAngle fov);
};