#pragma once

#include <DefaultComponents/Physics/CharacterControllerComponent.h>

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

	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CCharacterControllerHelperComponent>& desc)
	{
		desc.SetGUID("{6C1F2B4A-FBF7-46A5-A976-AA81871103F1}"_cry_guid);

		desc.SetEditorCategory("Helpers");
		desc.SetLabel("Character Controller Helper");
		desc.SetDescription("Component to help with character controllers");
		desc.SetComponentFlags({ IEntityComponent::EFlags::Singleton });
	}
	// ~IEntityComponent

	void SetMovementParams(const Cry::DefaultComponents::CCharacterControllerComponent::SMovement movement);
	void ExpandMovementParams(const Cry::DefaultComponents::CCharacterControllerComponent::SMovement& movement, float& airControl, float& airResistance, float& inertia, float& inertiaAcceleration, float& maxClimbAngle, float& maxJumpAngle, float& minSlideAngle, float& minFallAngle, float& maxGroundVelocity);
	Cry::DefaultComponents::CCharacterControllerComponent::SMovement CreateMovementParams(float airControl, float airResistance, float inertia, float inertiaAcceleration, float maxClimbAngle, float maxJumpAngle, float minSlideAngle, float minFallAngle, float maxGroundVelocity);

	void SetPhysicsParams(const Cry::DefaultComponents::CCharacterControllerComponent::SPhysics physics, float zOffset);
	void ExpandPhysicsParams(const Cry::DefaultComponents::CCharacterControllerComponent::SPhysics& physics, float& radius, float& height, bool& capsule, float& groundContactEps, bool& sendCollisionSignal);
	Cry::DefaultComponents::CCharacterControllerComponent::SPhysics CreatePhysicsParams(float radius, float height, bool capsule, float groundContactEps, bool sendCollisionSignal);

	float GetZOffset();
};