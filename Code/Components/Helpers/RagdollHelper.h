#pragma once

#include <CryCore/StaticInstanceList.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/SharedString.h>

////////////////////////////////////////////////////////
// Physicalized bullet shot from weaponry, expires on collision with another object
////////////////////////////////////////////////////////
class CRagdollHelperComponent final : public IEntityComponent
{
public:
	CRagdollHelperComponent();
	virtual ~CRagdollHelperComponent();

	// IEntityComponent
	virtual void Initialize() override;

	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;

	static void ReflectType(Schematyc::CTypeDesc<CRagdollHelperComponent>& desc);
	// ~IEntityComponent

	void Ragdollize();
	void UnRagdollize();

	bool IsRagdoll();
};