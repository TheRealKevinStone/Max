// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "AI/Navigation/NavAreas/NavArea.h"
//#include "NavArea_Jump.generated.h"
/*
This script will implement a special "jump" navigation area

One of the ways of annotating navmesh in UE4 is by applying navigation area types to it.
Navigation areas can apply a specific set of flags and costs to the navigation mesh.

*/

//UENUM()
//namespace ENavAreaFlag
//{
//	enum Type
//	{
//		Default,
//		Jump,
//		Crouch,
//	};
//}
//
///*
//Note that we're not using the first bit, since it has a special meaning in our navmesh internals. 
//If first bit in a area is set it means it's walkable, and it's treated as not walkable otherwise. 
//
//Let's also implement some helper functions for operating on area flags:
//*/
//namespace FNavAreaHelper
//{
//	FORCEINLINE bool IsSet(uint16 Flags, ENavAreaFlag::Type Bit) { return (Flags & (1 << Bit)) != 0; }
//	FORCEINLINE void Set(uint16& Flags, ENavAreaFlag::Type Bit) { Flags |= (1 << Bit); }
//
//	FORCEINLINE bool IsNavLink(const FNavPathPoint& PathVert) { return (FNavMeshNodeFlags(PathVert.Flags).PathFlags & RECAST_STRAIGHTPATH_OFFMESH_CONNECTION) != 0; }
//	FORCEINLINE bool HasJumpFlag(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::Jump); }
//	FORCEINLINE bool HasCrouchFlag(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::Crouch); }
//}
//
//
//UCLASS()
//class UNavArea_Jump : public UNavArea
//{
//	GENERATED_UCLASS_BODY()
//	
//};
//
//

/**
Dear Future Franco
Enjoy making AI jump
remember
i love you.


A proper C++ solution would involve following steps:

* Implement a new Navigation Area class - you do that by deriving from UNavArea. Let's call it UNavArea_Jump
* Define a "jump flag" - the implementation details don't really matter, but a enum would work best here.
- Set the "jump flag" in UNavArea_Jump::AreaFlags
* Now you'll be able to assign UNavArea_Jump as a navigation area of navigation links.
* Next step is to implement your own path following component. Derive from UPathFollowingComponent. Let's call it UMyPathFollowingComponent.
* Have UMyPathFollowingComponent override UPathFollowingComponent::SetMoveSegment(uint32 SegmentStartIndex) function. This function gets called whenever AI is starting to follow new path segment
- if FNavMeshNodeFlags(Path->PathPoints[SegmentStartIndex].Flags).AreaFlags has your defined "jump flag" set it means it's "jumpable"
- the simplest solution would be to enable flying in such a case. You do that by calling SetMovementMode(MOVE_Flying) on your movement component. From within path following component you can get this by casting UPathFollowingComponent::MovementComp to UCharacterMovementComponent.
- don't forget to set movement mode back to MOVE_Flying once AI finished following "jump segment"

That should pretty much do it  Sorry for any potential misspelling of class or function names
*/
