#include "StdAfx.h"
#include "CharacterControllerHelper.h"

#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CrySchematyc/Env/Elements/EnvFunction.h>
#include <CrySchematyc/Env/Elements/EnvSignal.h>
#include <CrySchematyc/Env/IEnvRegistrar.h>

namespace
{
	static void RegisterCharacterControllerHelperComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CCharacterControllerHelperComponent));

			{
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::SetMovementParams, "{FA0EEE4D-074B-43F3-B264-D41BC3DC6A6A}"_cry_guid, "SetMovementParams");
					pFunction->BindInput(1, 'move', "Movement", "Movement");
					componentScope.Register(pFunction);
				}
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::ExpandMovementParams, "{15F17102-5722-4F34-96A2-CC71F7C1A6D7}"_cry_guid, "ExpandMovementParams");
					pFunction->BindInput(1, 'move', "Movement", "Movement");
					pFunction->BindOutput(2, 'airc', "Air Control Ratio", "Indicates how much the character can move in the air, 0 means no movement while 1 means full control.");
					pFunction->BindOutput(3, 'airr', "Air Resistance", nullptr);
					pFunction->BindOutput(4, 'iner', "Inertia Coefficient", "More amount gives less inertia, 0 being none");
					pFunction->BindOutput(5, 'inea', "Inertia Acceleration Coefficient", "More amount gives less inertia on acceleration, 0 being none");
					pFunction->BindOutput(6, 'maxc', "Maximum Climb Angle", "Maximum angle the character can climb");
					pFunction->BindOutput(7, 'maxj', "Maximum Jump Angle", "Maximum angle the character can jump at");
					pFunction->BindOutput(8, 'mins', "Minimum Angle For Slide", "Minimum angle before the player starts sliding");
					pFunction->BindOutput(9, 'minf', "Minimum Angle For Fall", "Minimum angle before the character starts falling");
					pFunction->BindOutput(10, 'maxg', "Maximum Surface Velocity", "Maximum velocity of the surface the character is on before they are considered airborne and slide off");
					componentScope.Register(pFunction);
				}
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::CreateMovementParams, "{3362B789-7745-4D6C-8C4E-6104F90855FF}"_cry_guid, "CreateMovementParams");
					pFunction->BindOutput(0, 'move', "Movement", "Movement");

					pFunction->BindInput(1, 'airc', "Air Control Ratio", "Indicates how much the character can move in the air, 0 means no movement while 1 means full control.", 1.f);
					pFunction->BindInput(2, 'airr', "Air Resistance", nullptr, 0.2f);
					pFunction->BindInput(3, 'iner', "Inertia Coefficient", "More amount gives less inertia, 0 being none", 8.f);
					pFunction->BindInput(4, 'inea', "Inertia Acceleration Coefficient", "More amount gives less inertia on acceleration, 0 being none", 8.f);
					pFunction->BindInput(5, 'maxc', "Maximum Climb Angle", "Maximum angle the character can climb", 50.0f);
					pFunction->BindInput(6, 'maxj', "Maximum Jump Angle", "Maximum angle the character can jump at", 50.0f);
					pFunction->BindInput(7, 'mins', "Minimum Angle For Slide", "Minimum angle before the player starts sliding", 70.0f);
					pFunction->BindInput(8, 'minf', "Minimum Angle For Fall", "Minimum angle before the character starts falling", 80.0f);
					pFunction->BindInput(9, 'maxg', "Maximum Surface Velocity", "Maximum velocity of the surface the character is on before they are considered airborne and slide off", DEG2RAD(50.f));
					componentScope.Register(pFunction);
				}

				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::SetPhysicsParams, "{CABCDB93-79AB-4064-BF89-67980A2E653A}"_cry_guid, "SetPhysicsParams");
					pFunction->BindInput(1, 'phys', "Physics", "Physics");
					pFunction->BindInput(2, 'zoff', "Z Offset", "Offset of the capsule or cylinder on the Z axis");
					componentScope.Register(pFunction);
				}
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::ExpandPhysicsParams, "{F095BC6E-AA53-47C1-9BED-F9E850B66879}"_cry_guid, "ExpandPhysicsParams");
					pFunction->BindInput(1, 'phys', "Physics", "Physics");
					pFunction->BindOutput(2, 'radi', "Collider Radius", "Radius of the capsule or cylinder");
					pFunction->BindOutput(3, 'heig', "Collider Height", "Height of the capsule or cylinder");
					pFunction->BindOutput(4, 'caps', "Use Capsule", "Whether or not to use a capsule as the main collider, otherwise cylinder");
					pFunction->BindOutput(5, 'gce', "Ground Contact Epsilon", "The amount that the player needs to move upwards before ground contact is lost");
					pFunction->BindOutput(6, 'send', "Send Collision Signal", "Whether or not this component should listen for collisions and report them");
					componentScope.Register(pFunction);
				}
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::CreatePhysicsParams, "{52CE8F28-7D0D-4821-ACB8-6D586201F844}"_cry_guid, "CreatePhysicsParams");
					pFunction->BindOutput(0, 'phys', "Physics", "Physics");
					pFunction->BindInput(1, 'radi', "Collider Radius", "Radius of the capsule or cylinder", 0.45f);
					pFunction->BindInput(2, 'heig', "Collider Height", "Height of the capsule or cylinder", 0.935f);
					pFunction->BindInput(3, 'caps', "Use Capsule", "Whether or not to use a capsule as the main collider, otherwise cylinder", true);
					pFunction->BindInput(4, 'gce', "Ground Contact Epsilon", "The amount that the player needs to move upwards before ground contact is lost", 0.004f);
					pFunction->BindInput(5, 'send', "Send Collision Signal", "Whether or not this component should listen for collisions and report them", false);
					componentScope.Register(pFunction);
				}

				/*{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::GetTransform, "{7F1171B3-5ABB-46E3-91D0-01F033A85977}"_cry_guid, "GetControllerTransform");
					pFunction->BindOutput(0, 'tsfm', "Transform", "Transform");
					componentScope.Register(pFunction);
				}
				{
					auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCharacterControllerHelperComponent::SetTransform, "{1A406F28-447B-436D-8688-A9D2B17581FC}"_cry_guid, "SetControllerTransform");
					pFunction->BindInput(1, 'tsfm', "Transform", "Transform");
					componentScope.Register(pFunction);
				}*/
			}
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterCharacterControllerHelperComponent);
}

CCharacterControllerHelperComponent::CCharacterControllerHelperComponent()
{
}

CCharacterControllerHelperComponent::~CCharacterControllerHelperComponent()
{
}

void CCharacterControllerHelperComponent::SetMovementParams(const Cry::DefaultComponents::CCharacterControllerComponent::SMovement movement)
{
	// Get the physical entity
	if (IPhysicalEntity* pPhysEnt = m_pEntity->GetPhysicalEntity())
	{
		pe_player_dynamics playerDynamics;

		pPhysEnt->GetParams(&playerDynamics);

		//playerDynamics.mass = movement.mass;

		playerDynamics.kAirControl = movement.m_airControlRatio;
		playerDynamics.kAirResistance = movement.m_airResistance;
		playerDynamics.kInertia = movement.m_inertia;
		playerDynamics.kInertiaAccel = movement.m_inertiaAcceleration;

		playerDynamics.maxClimbAngle = movement.m_maxClimbAngle.ToDegrees();
		playerDynamics.maxJumpAngle = movement.m_maxJumpAngle.ToDegrees();
		playerDynamics.minFallAngle = movement.m_minFallAngle.ToDegrees();
		playerDynamics.minSlideAngle = movement.m_minSlideAngle.ToDegrees();

		playerDynamics.maxVelGround = movement.m_maxGroundVelocity;

		pPhysEnt->SetParams(&playerDynamics);
	}
}

void CCharacterControllerHelperComponent::ExpandMovementParams(const Cry::DefaultComponents::CCharacterControllerComponent::SMovement& movement, float& airControl, float& airResistance, float& inertia, float& inertiaAcceleration, float& maxClimbAngle, float& maxJumpAngle, float& minSlideAngle, float& minFallAngle, float& maxGroundVelocity)
{
	airControl = movement.m_airControlRatio;
	airResistance = movement.m_airResistance;
	inertia = movement.m_inertia;
	inertiaAcceleration = movement.m_inertiaAcceleration;

	maxClimbAngle = movement.m_maxClimbAngle.ToDegrees();
	maxJumpAngle = movement.m_maxJumpAngle.ToDegrees();
	minSlideAngle = movement.m_minSlideAngle.ToDegrees();
	minFallAngle = movement.m_minFallAngle.ToDegrees();

	maxGroundVelocity = movement.m_maxGroundVelocity;
}

Cry::DefaultComponents::CCharacterControllerComponent::SMovement CCharacterControllerHelperComponent::CreateMovementParams(float airControl, float airResistance, float inertia, float inertiaAcceleration, float maxClimbAngle, float maxJumpAngle, float minSlideAngle, float minFallAngle, float maxGroundVelocity)
{
	Cry::DefaultComponents::CCharacterControllerComponent::SMovement movement;

	movement.m_airControlRatio = airControl;
	movement.m_airResistance = airResistance;
	movement.m_inertia = inertia;
	movement.m_inertiaAcceleration = inertiaAcceleration;

	movement.m_maxClimbAngle = CryTransform::CAngle::FromDegrees(maxClimbAngle);
	movement.m_maxJumpAngle = CryTransform::CAngle::FromDegrees(maxJumpAngle);
	movement.m_minSlideAngle = CryTransform::CAngle::FromDegrees(minSlideAngle);
	movement.m_minFallAngle = CryTransform::CAngle::FromDegrees(minFallAngle);

	movement.m_maxGroundVelocity = maxGroundVelocity;

	return movement;
}

void CCharacterControllerHelperComponent::SetPhysicsParams(const Cry::DefaultComponents::CCharacterControllerComponent::SPhysics physics, float zOffset)
{
	if (auto* pCharacterController = m_pEntity->GetComponent<Cry::DefaultComponents::CCharacterControllerComponent>())
	{
		// Get the physical entity
		if (IPhysicalEntity* pPhysEnt = m_pEntity->GetPhysicalEntity())
		{
			// Set controller component z position to offset
			Matrix34 tm = pCharacterController->GetTransformMatrix();
			Vec3 pos = tm.GetTranslation();
			pos.z = zOffset;
			tm.SetTranslation(pos);
			pCharacterController->SetTransformMatrix(tm);

			pe_player_dimensions playerDimensions;

			pPhysEnt->GetParams(&playerDimensions);

			// Prefer usage of a cylinder
			playerDimensions.bUseCapsule = physics.m_bCapsule ? 1 : 0;

			// Specify the size of our capsule, physics treats the input as the half-size, so we multiply our value by 0.5.
			// This ensures that 1 unit = 1m for designers.
			playerDimensions.sizeCollider = Vec3(physics.m_radius * 0.5f, 1.f, physics.m_height * 0.5f);
			// Capsule height needs to be adjusted to match 1 unit ~= 1m.
			if (playerDimensions.bUseCapsule)
			{
				playerDimensions.sizeCollider.z *= 0.5f;
			}
			playerDimensions.groundContactEps = physics.m_groundContactEps;
			// Keep pivot at the player's feet (defined in player geometry) 
			playerDimensions.heightPivot = 0.f;
			// Offset collider upwards
			playerDimensions.heightCollider = pCharacterController->GetTransform() != nullptr ? pCharacterController->GetTransformMatrix().GetTranslation().z : 0.f;

			pPhysEnt->SetParams(&playerDimensions);
		}
	}
}

void CCharacterControllerHelperComponent::ExpandPhysicsParams(const Cry::DefaultComponents::CCharacterControllerComponent::SPhysics& physics, float& radius, float& height, bool& capsule, float& groundContactEps, bool& sendCollisionSignal)
{
	//mass = physics.m_mass;
	radius = physics.m_radius;
	height = physics.m_height;
	capsule = physics.m_bCapsule;
	groundContactEps = physics.m_groundContactEps;
	sendCollisionSignal = physics.m_bSendCollisionSignal;
}

Cry::DefaultComponents::CCharacterControllerComponent::SPhysics CCharacterControllerHelperComponent::CreatePhysicsParams(float radius, float height, bool capsule, float groundContactEps, bool sendCollisionSignal)
{
	Cry::DefaultComponents::CCharacterControllerComponent::SPhysics physics;

	//physics.m_mass = mass;
	physics.m_radius = radius;
	physics.m_height = height;
	physics.m_bCapsule = capsule;
	physics.m_groundContactEps = groundContactEps;
	physics.m_bSendCollisionSignal = sendCollisionSignal;

	return physics;
}

float CCharacterControllerHelperComponent::GetZOffset()
{
	if (auto* pCharacterController = m_pEntity->GetComponent<Cry::DefaultComponents::CCharacterControllerComponent>())
	{
		return pCharacterController->GetTransformMatrix().GetTranslation().z;
	}

	return 0;
}