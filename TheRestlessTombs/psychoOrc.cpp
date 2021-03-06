#include "psychoOrc.h"

PsychoOrc::PsychoOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Enemy::Enemy(player, lineOfSight, rm, camera, shader, world) {
	// stats of the psychoorc
	damage = 1;
	speed = 9.0f;
	attackSpeed = 0.75f;
	health = 1;
	currentHealth = health;
	// create the weapon
	sword = new Weapon(damage, 135.0f, attackSpeed, false, camera, shader, this->world);
	sword->GiveTexture(this->rm->GetTexture("psychoOrcWeapon"));
	sword->CreateBody(0, 0, 18, 36);
	sword->SetAngle(glm::vec2(0.0f, 0.0f));
	sword->localPosition.x = 40.0f;
	this->AddChild(sword);
}

PsychoOrc::~PsychoOrc() {
	delete sword;
}

void PsychoOrc::Update(double deltaTime) {
	if (LookForPlayer()) {
		// Calculate the angle between the player and piviot of the enemy
		glm::vec2 angle = glm::vec2(player->localPosition.x, player->localPosition.y) - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
		// Normalize the angle
		angle = glm::normalize(angle);
		// Set the length of the angle to 40 pixels away from the psychoorc's piviot
		angle *= 40.0f;
		sword->SetAngle(angle);
		sword->localPosition.x = angle.x;
		sword->localPosition.y = angle.y;
		// flip the texture of the sword
		if (IsTextureFlipped() && sword->IsFlipped()) {
			sword->FlipBody();
		}
		else if (!IsTextureFlipped() && !sword->IsFlipped()) {
			sword->FlipBody();
		}
		// if the player is in range attack him
		if (distancePlayer < minimalRange) {
			sword->Attack();
		}
	}
	// Check if the person got damaged
	if (damaged && timerDamaged < cooldownDamaged) {
		timerDamaged += deltaTime;
	}
	else {
		timerDamaged = 0.0f;
		damaged = false;
	}
}

void PsychoOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
		damaged = true;
	}
	else {
		currentHealth = 0;
		this->Destroy();
		sword->SetActive(false);
		this->RemoveChild(sword);
		if (item != nullptr) {
			item->Reset();
		}
	}
}

void PsychoOrc::Reset() {
	// Set all of the variables back to their base values
	body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
	playerLastLocation = spawnPosition;
	if (!IsAlive()) {
		alive = true;
		sword->SetActive(true);
		this->AddChild(sword);
		currentHealth = health;
		SetActive(true);
		if (item != nullptr) {
			item->Destroy();
		}
	}
	currentHealth = health;
}
