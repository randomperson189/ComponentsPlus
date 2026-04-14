// Copyright 2019-2022 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CrySchematyc/MathTypes.h>
#include <CryEntitySystem/IEntityComponent.h>
#include <CryPhysics/physinterface.h>

enum class ECollisionType : uint32
{
	Bit_1  = BIT(0),
	Bit_2  = BIT(1),
	Bit_3  = BIT(2),
	Bit_4  = BIT(3),
	Bit_5  = BIT(4),
	Bit_6  = BIT(5),
	Bit_7  = BIT(6),
	Bit_8  = BIT(7),
	Bit_9  = BIT(8),
	Bit_10 = BIT(9),
	Bit_11 = BIT(10),
	Bit_12 = BIT(11),
	Bit_13 = BIT(12),
	Bit_14 = BIT(13),
	Bit_15 = BIT(14),
	Bit_16 = BIT(15),
	Bit_17 = BIT(16),
	Bit_18 = BIT(17),
	Bit_19 = BIT(18),
	Bit_20 = BIT(19),
	Bit_21 = BIT(20),
	Bit_22 = BIT(21),
	Bit_23 = BIT(22),
	Bit_24 = BIT(23),
	Bit_25 = BIT(24),
	Bit_26 = BIT(25),
	Bit_27 = BIT(26),
	Bit_28 = BIT(27),
	Bit_29 = BIT(28),
	Bit_30 = BIT(29),
	Bit_31 = BIT(30),
	Bit_32 = BIT(31)
};

typedef CEnumFlags<ECollisionType> ECollisionTypeMask;

static void ReflectType(Schematyc::CTypeDesc<ECollisionType>& desc)
{
	desc.SetGUID("{D04D3FA5-C29B-48FC-A481-1161DF1F54CF}"_cry_guid);
	desc.SetLabel("Collision Type Bit");
	desc.SetDescription("A collision type bit that can be used to filter collisions between entities.");
	desc.AddConstant(ECollisionType::Bit_1,  "Bit1", "Bit 1");
	desc.AddConstant(ECollisionType::Bit_2,  "Bit2", "Bit 2");
	desc.AddConstant(ECollisionType::Bit_3,  "Bit3", "Bit 3");
	desc.AddConstant(ECollisionType::Bit_4,  "Bit4", "Bit 4");
	desc.AddConstant(ECollisionType::Bit_5,  "Bit5", "Bit 5");
	desc.AddConstant(ECollisionType::Bit_6,  "Bit6", "Bit 6");
	desc.AddConstant(ECollisionType::Bit_7,  "Bit7", "Bit 7");
	desc.AddConstant(ECollisionType::Bit_8,  "Bit8", "Bit 8");
	desc.AddConstant(ECollisionType::Bit_9,  "Bit9", "Bit 9");
	desc.AddConstant(ECollisionType::Bit_10, "Bit10", "Bit 10");
	desc.AddConstant(ECollisionType::Bit_11, "Bit11", "Bit 11");
	desc.AddConstant(ECollisionType::Bit_12, "Bit12", "Bit 12");
	desc.AddConstant(ECollisionType::Bit_13, "Bit13", "Bit 13");
	desc.AddConstant(ECollisionType::Bit_14, "Bit14", "Bit 14");
	desc.AddConstant(ECollisionType::Bit_15, "Bit15", "Bit 15");
	desc.AddConstant(ECollisionType::Bit_16, "Bit16", "Bit 16");
	desc.AddConstant(ECollisionType::Bit_17, "Bit17", "Bit 17");
	desc.AddConstant(ECollisionType::Bit_18, "Bit18", "Bit 18");
	desc.AddConstant(ECollisionType::Bit_19, "Bit19", "Bit 19");
	desc.AddConstant(ECollisionType::Bit_20, "Bit20", "Bit 20");
	desc.AddConstant(ECollisionType::Bit_21, "Bit21", "Bit 21");
	desc.AddConstant(ECollisionType::Bit_22, "Bit22", "Bit 22");
	desc.AddConstant(ECollisionType::Bit_23, "Bit23", "Bit 23");
	desc.AddConstant(ECollisionType::Bit_24, "Bit24", "Bit 24");
	desc.AddConstant(ECollisionType::Bit_25, "Bit25", "Bit 25");
	desc.AddConstant(ECollisionType::Bit_26, "Bit26", "Bit 26");
	desc.AddConstant(ECollisionType::Bit_27, "Bit27", "Bit 27");
	desc.AddConstant(ECollisionType::Bit_28, "Bit28", "Bit 28");
	desc.AddConstant(ECollisionType::Bit_29, "Bit29", "Bit 29");
	desc.AddConstant(ECollisionType::Bit_30, "Bit30", "Bit 30");
	desc.AddConstant(ECollisionType::Bit_31, "Bit31", "Bit 31");
	desc.AddConstant(ECollisionType::Bit_32, "Bit32", "Bit 32");
}

class CCollisionMaskComponent final : public IEntityComponent
{
	struct SDefault
	{
		static constexpr uint32 collisionMask = 0;
	};

public:
	static void ReflectType(Schematyc::CTypeDesc<CCollisionMaskComponent>& desc)
	{
		desc.SetLabel("CollisionMask");
		desc.SetEditorCategory("Physics");
		desc.SetDescription("Provides the ability to control collision masks for this objects physical entity.");
		desc.SetGUID("{92765DC2-3A84-4558-A82E-B25F55768AFA}"_cry_guid);
		desc.SetComponentFlags({ IEntityComponent::EFlags::Singleton });

		desc.AddMember(&CCollisionMaskComponent::m_types, 'mskt', "Types", "Entity Types", "The bitmask of collision type Ids this object represents.", Schematyc::CArray<ECollisionType>());
		desc.AddMember(&CCollisionMaskComponent::m_ignores, 'mski', "Ignores", "Ignored Types", "The bitmask of collision type Ids this object will ignore.", Schematyc::CArray<ECollisionType>());
	}

	CCollisionMaskComponent() = default;
	virtual ~CCollisionMaskComponent() override final {};
	
	void AddIgnoredTypeId(const ECollisionType& typeId) const;
	void RemoveIgnoredTypeId(const ECollisionType& typeId) const;
	void ClearIgnoredTypeIds() const;

	void AddEntityTypeId(const ECollisionType& typeId) const;
	void RemoveEntityTypeId(const ECollisionType& typeId) const;
	void ClearEntityTypeIds() const;

protected:
	// IEntityComponent
	virtual EntityEventMask GetEventMask() const override final;
	virtual ComponentEventPriority GetEventPriority() const override final;
public:
	virtual void Initialize() override final;
protected:
	virtual void ProcessEvent(const SEntityEvent& event) override final;
	// ~IEntityComponent

private:
	bool IgnoreExists(ECollisionType typeId) const;
	bool TypeExists(ECollisionType typeId) const;
	void UpdatePhysicalEntity(pe_params_collision_class& params) const;

private:
	Schematyc::CArray<ECollisionType> m_types;
	Schematyc::CArray<ECollisionType> m_ignores;
};