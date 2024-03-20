#pragma once

#include "CoreMinimal.h"

class AActor;
class UWorld;

template <class Object=AActor>
class TActorObjectPool
{
private:
	UWorld* CurrentWorld=nullptr;

	UClass* ReturnType=nullptr;

	//初始化对象池个数（每次增加的值）
	int32 InitCount=0;

	//每次扩充对象池增加的值
	int32 GrowCount=0;
	//对象池缓冲区
	TArray<Object*> GameObjectPoolBuff;

	int32 PoolBuffNum=0;

	FVector DefaultLocation=FVector(0,0,-100.f);
public:
	TActorObjectPool<Object>(){};

	TActorObjectPool<Object>(UWorld* _World,int32 _InitCount,int32 _GrowCount=0)
	:CurrentWorld(_World),InitCount(_InitCount)
	{
		ReturnType=Object::StaticClass();
		if(_GrowCount<=0)
		{
			GrowCount=InitCount;
		}
		else
		{
			GrowCount=_GrowCount;
		}
	}

	void Initial(UWorld* _World,int32 _InitCount,int32 _GrowCount=0)
	{
		CurrentWorld=_World;
		InitCount=_InitCount;
		ReturnType=Object::StaticClass();
		if(_GrowCount<=0)
		{
			GrowCount=InitCount;
		}
		else
		{
			GrowCount=_GrowCount;
		}
	}
	void CreateNewObjectToPool()
	{
		for(int Index=0;Index<GrowCount;++Index)
		{
			Object* T=CurrentWorld->SpawnActor<Object>(ReturnType);
			T->SetHidden(true);
			GameObjectPoolBuff.Emplace(T);
		}
		PoolBuffNum+=GrowCount;
	}

	UObject* CreateActor()
	{
		if(PoolBuffNum==0)
		{
			CreateNewObjectToPool();
		}
		for(int Index=0;Index<GameObjectPoolBuff.Num();++Index)
		{
			if(GameObjectPoolBuff[Index]->IsHidden())
			{
				GameObjectPoolBuff[Index]->SetHidden(false);
				--PoolBuffNum;
				return GameObjectPoolBuff[Index];
			}
		}
		return nullptr;
	}

	void DestoryActor(Object* Actor)
	{
		Actor->SetActorLocation(DefaultLocation);
		int32 Index=GameObjectPoolBuff.Find(Actor);
		if(Index!=INDEX_NONE)
		{
			GameObjectPoolBuff[Index]->SetHidden(true);
			++PoolBuffNum;
		}
	}
};
