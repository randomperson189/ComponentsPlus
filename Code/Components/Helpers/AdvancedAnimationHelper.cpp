#include "StdAfx.h"
#include "AdvancedAnimationHelper.h"

#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CrySchematyc/Env/Elements/EnvFunction.h>
#include <CrySchematyc/Env/Elements/EnvSignal.h>
#include <DefaultComponents/Input/InputComponent.h>

namespace
{
	static void RegisterAdvancedAnimationHelperComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CAdvancedAnimationHelperComponent));
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterAdvancedAnimationHelperComponent);
}

CAdvancedAnimationHelperComponent::CAdvancedAnimationHelperComponent() 
{
}

CAdvancedAnimationHelperComponent::~CAdvancedAnimationHelperComponent()
{
}

void CAdvancedAnimationHelperComponent::Initialize()
{
}