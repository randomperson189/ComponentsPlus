#pragma once

#include <CryCore/StaticInstanceList.h>
#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/SharedString.h>

////////////////////////////////////////////////////////
// Physicalized bullet shot from weaponry, expires on collision with another object
////////////////////////////////////////////////////////
class CAttachmentHelperComponent final : public IEntityComponent
{
public:
	CAttachmentHelperComponent();
	virtual ~CAttachmentHelperComponent();

	// IEntityComponent
	virtual void Initialize() override;

	static void ReflectType(Schematyc::CTypeDesc<CAttachmentHelperComponent>& desc);
	// ~IEntityComponent

	void CreateAttachment(Schematyc::ExplicitEntityId id, int animComponentIndex, Schematyc::CSharedString attachmentName, Vec3 scale = Vec3(1.f, 1.f, 1.f));
	void RemoveAttachment(int animComponentIndex, Schematyc::CSharedString attachmentName);
};