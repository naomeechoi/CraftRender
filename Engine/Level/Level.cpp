#include "Level.h"
#include "Actor/Actor.h"

namespace Craft
{
	Level::Level()
	{
	}

	Level::~Level()
	{
	}

	void Level::OnInitialized()
	{
		hasInitialized = true;
	}

	void Level::BeginPlay()
	{
		for (const std::shared_ptr<Actor>& actor : actorList)
		{
			if (actor->HasBeganPlay() || !actor->IsActive())
				continue;
			
			actor->BeginPlay();
		}
	}

	void Level::Tick(float deltaTime)
	{
		for (const std::shared_ptr<Actor>& actor : actorList)
		{
			if (!actor->IsActive())
				continue;
			actor->Tick(deltaTime);
		}
	}

	void Level::Draw()
	{
		for (const std::shared_ptr<Actor>& actor : actorList)
		{
			if (!actor->IsActive())
				continue;
			actor->Draw();
		}
	}

	void Level::ProcessAddAndDestroyActors()
	{
		for (auto iter = actorList.begin(); iter != actorList.end();)
		{
			if ((*iter)->HasExpired())
			{
				iter = actorList.erase(iter);
				continue;
			}
			iter++;
		}

		if (addRequestedActorList.empty())
			return;

		for (const std::shared_ptr<Actor>& actor : addRequestedActorList)
		{
			actorList.emplace_back(actor);
		}

		addRequestedActorList.clear();
	}
}