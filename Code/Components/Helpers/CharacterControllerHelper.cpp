#include "StdAfx.h"
#include "CharacterControllerHelper.h"

#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CrySchematyc/Env/Elements/EnvFunction.h>
#include <CrySchematyc/Env/Elements/EnvSignal.h>

#include <DefaultComponents/Physics/CharacterControllerComponent.h>

namespace
{
	static void RegisterCharacterControllerHelperComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CCharacterControllerHelperComponent));

			{
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::GetDimensions, "{7A4F08BD-466A-438A-987B-FAF2E1347ACC}"_cry_guid, "Get Dimensions");
					pFunction->BindOutput(0, 'radi', "Collider Radius", "Radius of the capsule or cylinder");
					pFunction->BindOutput(1, 'heig', "Collider Height", "Height of the capsule or cylinder");
					pFunction->BindOutput(2, 'caps', "Use Capsule", "Whether or not to use a capsule as the main collider, otherwise cylinder");
					pFunction->BindOutput(3, 'gce', "Ground Contact Epsilon", "The amount that the player needs to move upwards before ground contact is lost");
					componentScope.Register(pFunction);
				}
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::SetDimensions, "{5E934515-4256-4431-9853-39E9001CA398}"_cry_guid, "Set Dimensions");
					pFunction->BindInput(1, 'radi', "Collider Radius", "Radius of the capsule or cylinder", 0.45f);
					pFunction->BindInput(2, 'heig', "Collider Height", "Height of the capsule or cylinder", 0.935f);
					pFunction->BindInput(3, 'caps', "Use Capsule", "Whether or not to use a capsule as the main collider, otherwise cylinder", true);
					pFunction->BindInput(4, 'gce', "Ground Contact Epsilon", "The amount that the player needs to move upwards before ground contact is lost", 0.004f);
					componentScope.Register(pFunction);
				}
			}
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterCharacterControllerHelperComponent);
}

// Reflect type to set a unique identifier for this component
void CCharacterControllerHelperComponent::ReflectType(Schematyc::CTypeDesc<CCharacterControllerHelperComponent>& desc)
{
	desc.SetGUID("{6C1F2B4A-FBF7-46A5-A976-AA81871103F1}"_cry_guid);

	desc.SetEditorCategory("Utilities");
	desc.SetLabel("Character Controller Helper");
	desc.SetDescription("Component to help with character controllers");
}

CCharacterControllerHelperComponent::CCharacterControllerHelperComponent()
{
}

CCharacterControllerHelperComponent::~CCharacterControllerHelperComponent()
{
}

float CCharacterControllerHelperComponent::GetDimensions(/*float& radius, */float& height, bool& bCapsule, float& groundContactEps)
{
	if (Cry::DefaultComponents::CCharacterControllerComponent* pCharacterController = m_pEntity->GetComponent<Cry::DefaultComponents::CCharacterControllerComponent>())
	{
		// Get the physical entity
		IPhysicalEntity* pPhysEnt = pCharacterController->GetEntity()->GetPhysicalEntity();

		pe_player_dimensions playerDimensions;

		pPhysEnt->GetParams(&playerDimensions);

		bCapsule = playerDimensions.bUseCapsule;
		//radius = playerDimensions.sizeCollider.x;
		height = playerDimensions.sizeCollider.z / 0.5f;
		groundContactEps = playerDimensions.groundContactEps;

		if (playerDimensions.bUseCapsule)
		{
			height /= 0.5f;
		}

		// Radius is the return value here
		return playerDimensions.sizeCollider.x / 0.5f;
	}

	return 0;
}

void CCharacterControllerHelperComponent::SetDimensions(/*float mass, */float radius, float height, bool bCapsule, float groundContactEps)
{
	if (Cry::DefaultComponents::CCharacterControllerComponent* pCharacterController = m_pEntity->GetComponent<Cry::DefaultComponents::CCharacterControllerComponent>())
	{
		// Create a new SPhysics struct and get it's values from the Character Controller
		Cry::DefaultComponents::CCharacterControllerComponent::SPhysics pPhysics = pCharacterController->GetPhysicsParameters();

		// Set the values to our new ones
		//pPhysics.m_mass = mass;
		pPhysics.m_radius = radius;
		pPhysics.m_height = height;
		pPhysics.m_bCapsule = bCapsule;
		pPhysics.m_groundContactEps = groundContactEps;

		// Get the physical entity
		IPhysicalEntity* pPhysEnt = pCharacterController->GetEntity()->GetPhysicalEntity();

		pe_player_dimensions playerDimensions;

		pPhysEnt->GetParams(&playerDimensions);

		// Prefer usage of a cylinder
		playerDimensions.bUseCapsule = pPhysics.m_bCapsule ? 1 : 0;

		// Specify the size of our capsule, physics treats the input as the half-size, so we multiply our value by 0.5.
		// This ensures that 1 unit = 1m for designers.
		playerDimensions.sizeCollider = Vec3(pPhysics.m_radius * 0.5f, 1.f, pPhysics.m_height * 0.5f);
		// Capsule height needs to be adjusted to match 1 unit ~= 1m.
		if (playerDimensions.bUseCapsule)
		{
			playerDimensions.sizeCollider.z *= 0.5f;
		}
		playerDimensions.groundContactEps = pPhysics.m_groundContactEps;

		// Update the physical entity params to use our new dimensions
		pPhysEnt->SetParams(&playerDimensions);
	}
}
