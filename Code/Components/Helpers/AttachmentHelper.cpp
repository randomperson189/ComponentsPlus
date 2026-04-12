#include "StdAfx.h"
#include "AttachmentHelper.h"

#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CrySchematyc/Env/Elements/EnvFunction.h>
#include <CrySchematyc/Env/Elements/EnvSignal.h>

#include <DefaultComponents/Geometry/AdvancedAnimationComponent.h>

namespace
{
	static void RegisterAttachmentHelperComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CAttachmentHelperComponent));

			{
				auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CAttachmentHelperComponent::CreateAttachment, "{A6A098D7-151B-46C9-A83D-D5D20580FA6A}"_cry_guid, "Attach Entity");
				pFunction->BindInput(1, 'tgte', "Target", "Target Entity to find");
				pFunction->BindInput(2, 'aci', "Anim Component Index", "Index of the Animation Component to use", 0);
				pFunction->BindInput(3, 'atcn', "Attachment Name", "Name of the attachment to find in the Animation Component");
				pFunction->BindInput(4, 'scl', "Scale", "Scale of the attached entity", Vec3(1.f, 1.f, 1.f));
				componentScope.Register(pFunction);
			}
			{
				auto pFunction = SCHEMATYC_MAKE_ENV_FUNCTION(&CAttachmentHelperComponent::RemoveAttachment, "{90B7B539-FA9C-4824-8361-2DF9EA299BA6}"_cry_guid, "Detach Entity");
				pFunction->BindInput(1, 'aci', "Anim Component Index", "Index of the Animation Component to use", 0);
				pFunction->BindInput(2, 'atcn', "Attachment Name", "Name of the attachment to find in the Animation Component");
				componentScope.Register(pFunction);
			}
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterAttachmentHelperComponent);
}

// Reflect type to set a unique identifier for this component
void CAttachmentHelperComponent::ReflectType(Schematyc::CTypeDesc<CAttachmentHelperComponent>& desc)
{
	desc.SetGUID("{5F753867-3CC6-47C2-80E6-769EE6ECA27E}"_cry_guid);

	desc.SetEditorCategory("Utilities");
	desc.SetLabel("Attachment Helper");
	desc.SetDescription("Component to manage attachments");
}

CAttachmentHelperComponent::CAttachmentHelperComponent()
{
}

CAttachmentHelperComponent::~CAttachmentHelperComponent()
{
}

void CAttachmentHelperComponent::Initialize()
{
}

void CAttachmentHelperComponent::CreateAttachment(Schematyc::ExplicitEntityId id, int animComponentIndex, Schematyc::CSharedString attachmentName, Vec3 scale)
{
	if (gEnv->pEntitySystem->GetEntity(static_cast<EntityId>(id)) == nullptr)
		return;

	// Define the animation component's interface ID (from ReflectType)
	// TODO: Find a better way to get the GUID directly, just in case it changes
	const CryInterfaceID animComponentID = "{3CD5DDC5-EE15-437F-A997-79C2391537FE}"_cry_guid;

	// Array to store all components of this type
	DynArray<IEntityComponent*> components;
	m_pEntity->GetComponentsByTypeId(animComponentID, components);

	if (Cry::DefaultComponents::CAdvancedAnimationComponent* animationComponent = static_cast<Cry::DefaultComponents::CAdvancedAnimationComponent*>(components[animComponentIndex]))
	{
		if (ICharacterInstance* pCharInstance = animationComponent->GetCharacter())
		{
			if (IAttachmentManager* pAttachmentMgr = pCharInstance->GetIAttachmentManager())
			{
				CEntityAttachment* pEntityAttachment = new CEntityAttachment();
				pEntityAttachment->SetEntityId(static_cast<EntityId>(id));
				pEntityAttachment->SetScale(scale);

				pAttachmentMgr->GetInterfaceByName(attachmentName.c_str())->AddBinding(pEntityAttachment);
			}
		}
	}
}

void CAttachmentHelperComponent::RemoveAttachment(int animComponentIndex, Schematyc::CSharedString attachmentName)
{
	// Define the animation component's interface ID (from ReflectType)
	// TODO: Find a better way to get the GUID directly, just in case it changes
	const CryInterfaceID animComponentID = "{3CD5DDC5-EE15-437F-A997-79C2391537FE}"_cry_guid;

	// Array to store all components of this type
	DynArray<IEntityComponent*> components;
	m_pEntity->GetComponentsByTypeId(animComponentID, components);

	if (Cry::DefaultComponents::CAdvancedAnimationComponent* animationComponent = static_cast<Cry::DefaultComponents::CAdvancedAnimationComponent*>(components[animComponentIndex]))
	{
		if (ICharacterInstance* pCharInstance = animationComponent->GetCharacter())
		{
			if (IAttachmentManager* pAttachmentMgr = pCharInstance->GetIAttachmentManager())
			{
				pAttachmentMgr->GetInterfaceByName(attachmentName.c_str())->ClearBinding();
			}
		}
	}
}
