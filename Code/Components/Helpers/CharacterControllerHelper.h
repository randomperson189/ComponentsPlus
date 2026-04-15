#pragma once

#include <CryCore/StaticInstanceList.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/SharedString.h>

////////////////////////////////////////////////////////
// Physicalized bullet shot from weaponry, expires on collision with another object
////////////////////////////////////////////////////////
class CCharacterControllerHelperComponent final : public IEntityComponent
{
public:
	CCharacterControllerHelperComponent();
	virtual ~CCharacterControllerHelperComponent();

	// IEntityComponent

	static void ReflectType(Schematyc::CTypeDesc<CCharacterControllerHelperComponent>& desc);
	// ~IEntityComponent

	float GetDimensions(/*float& radius, */float& height, bool& bCapsule, float& groundContactEps);
	void SetDimensions(/*float mass, */float radius, float height, bool bCapsule, float groundContactEps);
};