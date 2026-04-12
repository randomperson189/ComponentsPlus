// Copyright 2019-2022 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "CollisionMask.h"

#include <CryCore/StaticInstanceList.h>
#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CrySchematyc/Env/Elements/EnvFunction.h>

#define STATIC_CAST_UNDERLYING(V) static_cast<std::underlying_type<std::remove_reference<decltype(V)>::type>::type>(V)

static void RegisterCollisionMaskComponent(Schematyc::IEnvRegistrar& registrar)
{
	Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
	{
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CCollisionMaskComponent));
		// Functions
		{
			auto const pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCollisionMaskComponent::AddIgnoredTypeId, "{8535A523-1812-4F63-B48C-EF2B3AAB9A6D}"_cry_guid, "AddIgnoredType");
			pFunction->SetDescription("Adds a collision type id to the ignored collision types for this entity.");
			pFunction->BindInput(1, 'type', "Type", "Type Id");
			componentScope.Register(pFunction);
		}
		{
			auto const pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCollisionMaskComponent::RemoveIgnoredTypeId, "{759B2CC3-2B08-4F04-AD74-00C663FA628B}"_cry_guid, "RemoveIgnoredType");
			pFunction->SetDescription("Removes a collision type id from the ignored collision types for this entity.");
			pFunction->BindInput(1, 'type', "Type", "Type Id");
			componentScope.Register(pFunction);
		}
		{
			auto const pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCollisionMaskComponent::ClearIgnoredTypeIds, "{B92BE20F-C493-48A0-B6E1-2793C6FCE838}"_cry_guid, "ClearIgnoredTypes");
			pFunction->SetDescription("Clear collision type ids from the ignored collision types for this entity.");
			componentScope.Register(pFunction);
		}
		{
			auto const pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCollisionMaskComponent::AddEntityTypeId, "{AC6939C0-AF64-4C19-9A91-DDF8E80B3843}"_cry_guid, "AddEntityType");
			pFunction->SetDescription("Adds a collision type id to the entity types this entity is a part of.");
			pFunction->BindInput(1, 'type', "Type", "Type Id");
			componentScope.Register(pFunction);
		}
		{
			auto const pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCollisionMaskComponent::RemoveEntityTypeId, "{3F09ADD6-7447-4AD1-8C28-639722C8E5DF}"_cry_guid, "RemoveEntityType");
			pFunction->SetDescription("Removes a collision type id from the entity types this entity is a part of.");
			pFunction->BindInput(1, 'type', "Type", "Type Id");
			componentScope.Register(pFunction);
		}
		{
			auto const pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CCollisionMaskComponent::ClearEntityTypeIds, "{64C45DA3-47DC-42B6-9BA8-16ADF8E8F3D1}"_cry_guid, "ClearEntityTypes");
			pFunction->SetDescription("Clear collision type ids from the entity types this entity is a part of.");
			componentScope.Register(pFunction);
		}
	}
}
CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterCollisionMaskComponent)

EntityEventMask CCollisionMaskComponent::GetEventMask() const
{
	return EEntityEvent::Reset | EEntityEvent::EditorPropertyChanged | EEntityEvent::LevelStarted;
}

// Control update order (Lower = Sooner, Default is 14).
IEntityComponent::ComponentEventPriority CCollisionMaskComponent::GetEventPriority() const
{
	// This way we make sure all the default components has been updated already.
	// This is especially important for making sure any RigidBody component has already
	// been initialized so we can apply parameters to the physical entity.
	return 15;
}

void CCollisionMaskComponent::Initialize()
{
	// Arrays to bitmasks
	uint32 ignored = 0;
	uint32 types = 0;
	
	for (int i=0; i<m_ignores.Size(); i++)
	{
		ignored |= static_cast<uint32>(m_ignores.At(i));
	}
	
	for (int i=0; i<m_types.Size(); i++)
	{
		types |= static_cast<uint32>(m_types.At(i));
	}
	
	pe_params_collision_class params;
	params.collisionClassOR.ignore = ignored;
	params.collisionClassOR.type = types;

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::ProcessEvent(const SEntityEvent & event)
{
	switch (event.event)
	{
		
	case EEntityEvent::Reset:
	case EEntityEvent::EditorPropertyChanged:
	case EEntityEvent::LevelStarted:
	{
		Initialize();
	} break;

	}
}

bool CCollisionMaskComponent::IgnoreExists(ECollisionType typeId) const
{
	if (IPhysicalEntity* pPhysicalEntity = m_pEntity->GetPhysicalEntity())
	{
		pe_params_collision_class params;
		pPhysicalEntity->GetParams(&params);

		if ((params.collisionClassOR.ignore & static_cast<uint32>(typeId)) != 0)
		{
			return true;
		}
	}

	return false;
}

bool CCollisionMaskComponent::TypeExists(ECollisionType typeId) const
{
	if (IPhysicalEntity* pPhysicalEntity = m_pEntity->GetPhysicalEntity())
	{
		pe_params_collision_class params;
		pPhysicalEntity->GetParams(&params);

		if ((params.collisionClassOR.type & static_cast<uint32>(typeId)) != 0)
		{
			return true;
		}
	}

	return false;
}

void CCollisionMaskComponent::AddIgnoredTypeId(const ECollisionType& typeId) const
{
	CRY_ASSERT(STATIC_CAST_UNDERLYING(typeId) > 0 && STATIC_CAST_UNDERLYING(typeId) <= 32, "Collision bitmask id out of range 1-32.");
	
	pe_params_collision_class params;
	params.collisionClassAND.type = ~0ul; // Keep all active bits
	params.collisionClassAND.ignore = ~0ul; // Keep all active bits

	params.collisionClassOR.ignore = static_cast<uint32>(typeId); // Add typeId bit

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::RemoveIgnoredTypeId(const ECollisionType& typeId) const
{
	CRY_ASSERT(STATIC_CAST_UNDERLYING(typeId) > 0 && STATIC_CAST_UNDERLYING(typeId) <= 32, "Collision bitmask id out of range 1-32.");

	pe_params_collision_class params;
	params.collisionClassAND.type = ~0ul; // Keep all active bits
	params.collisionClassAND.ignore = ~static_cast<uint32>(typeId); // Keep all active bits except typeId

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::ClearIgnoredTypeIds() const
{
	pe_params_collision_class params;
	params.collisionClassAND.type = ~0ul; // Keep all active bits
	params.collisionClassAND.ignore = 0;

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::AddEntityTypeId(const ECollisionType& typeId) const
{
	CRY_ASSERT(STATIC_CAST_UNDERLYING(typeId) > 0 && STATIC_CAST_UNDERLYING(typeId) <= 32, "Collision bitmask id out of range 1-32.");
	
	pe_params_collision_class params;
	params.collisionClassAND.type = ~0ul; // Keep all active bits
	params.collisionClassAND.ignore = ~0ul; // Keep all active bits

	params.collisionClassOR.type = static_cast<uint32>(typeId); // Add typeId bit

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::RemoveEntityTypeId(const ECollisionType& typeId) const
{
	CRY_ASSERT(STATIC_CAST_UNDERLYING(typeId) > 0 && STATIC_CAST_UNDERLYING(typeId) <= 32, "Collision bitmask id out of range 1-32.");

	pe_params_collision_class params;
	params.collisionClassAND.type = ~static_cast<uint32>(typeId); // Keep all active bits except typeId
	params.collisionClassAND.ignore = ~0ul; // Keep all active bits

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::ClearEntityTypeIds() const
{
	pe_params_collision_class params;
	params.collisionClassAND.type = 0;
	params.collisionClassAND.ignore = ~0ul; // Keep all active bits

	UpdatePhysicalEntity(params);
}

void CCollisionMaskComponent::UpdatePhysicalEntity(pe_params_collision_class& params) const
{
	if (IPhysicalEntity* pPhysicalEntity = m_pEntity->GetPhysicalEntity())
	{
		pPhysicalEntity->SetParams(&params);
	}
}