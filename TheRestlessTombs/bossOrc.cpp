#include "bossOrc.h"

BossOrc::BossOrc(std::string nameBoss, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Boss::Boss(nameBoss, player, lineOfSight, rm, camera, shader, world) {
	// stats of the BossOrc
	damage = 1;
	speed = 4.0f;
	originalSpeed = speed;
	attackSpeed = 1.40f;
	health = 10;
	currentHealth = health;
	specialAbilityCooldown = 4.0f;
	specialAbilityTimer = 0.0f;
	specialAbility = false;

	// Create the Hammer
	hammer = new Weapon(damage, 135.0f, attackSpeed, false, camera, shader, this->world);
	hammer->GiveTexture(rm->GetTexture("bossOrcWeapon"));
	hammer->CreateBody(0, 0, 30, 120);
	hammer->SetAngle(glm::vec2(0.0f, 0.0f));
	hammer->localPosition.x = 40.0f;
	this->AddChild(hammer);
	timer = 0.0f;
}

BossOrc::~BossOrc() {
	delete hammer;
}

void BossOrc::Update(double deltaTime) {
	if (LookForPlayer(deltaTime)) {
		// Calculate the angle between the player and piviot of the enemy
		glm::vec2 angle;
		if (!specialAbility) {
			angle = glm::vec2(player->localPosition.x, player->localPosition.y) - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
		}
		else {
			angle = glm::vec2(specialAttackDirection.x, specialAttackDirection.y);
		}
		// Normalize the angle
		angle = glm::normalize(angle);
		// Set the length of the angle to 40 pixels away from the player's piviot
		angle *= 40.0f;
		hammer->SetAngle(angle);
		hammer->localPosition.x = angle.x;
		hammer->localPosition.y = angle.y;
		// Flip the texture hammer
		if (IsTextureFlipped() && hammer->IsFlipped()) {
			hammer->FlipBody();
		}
		else if (!IsTextureFlipped() && !hammer->IsFlipped()) {
			hammer->FlipBody();
		}
		if (distancePlayer < minimalRange || specialAbility) {
			hammer->Attack();
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

bool BossOrc::LookForPlayer(double deltaTime) {
	this->localPosition = glm::vec3(this->GetPositionInPixels().x, this->GetPositionInPixels().y, 1.0f);
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (this->ShootRaycast()) {
		timer += deltaTime;
		// If the special ability is ready change the speed and charge to the player's location
		if (timer >= specialAbilityCooldown && !specialAbility) {
			specialAbility = true;
			specialAttackDirection = b2Vec2(player->localPosition.x - this->localPosition.x, player->localPosition.y - this->localPosition.y);
			vel = specialAttackDirection;
			speed = 6.0f;
		}
		else if (specialAbility) {
			specialAbilityTimer += deltaTime;
			vel = specialAttackDirection;
			if (specialAbilityTimer >= specialAbilityCooldown) {
				specialAbilityTimer = 0.0f;
				specialAbility = false;
				timer = 0.0f;
				speed = originalSpeed;
			}
		}
		else {
			vel = b2Vec2(player->localPosition.x - this->localPosition.x, player->localPosition.y - this->localPosition.y);
			specialAbility = false;
			specialAbilityTimer = 0.0f;
			speed = originalSpeed;
		}
		vel.Normalize();
		vel *= speed;
		body->SetLinearVelocity(vel);
		// Flip texture BossOrc
		if (IsTextureFlipped() && vel.x < 0.0f) {
			FlipTexture();
		}
		else if (!IsTextureFlipped() && vel.x > 0.0f) {
			FlipTexture();
		}
		return true;
	}
	else if (glm::distance(this->localPosition, playerLastLocation) > minimalRange) {
		specialAbilityTimer = 0.0f;
		specialAbility = false;
		speed = originalSpeed;
		timer = 0.0f;
		vel = b2Vec2(playerLastLocation.x - this->localPosition.x, playerLastLocation.y - this->localPosition.y);
		vel.Normalize();
		vel *= speed;
		body->SetLinearVelocity(vel);
		return false;
	}
	timer = 0.0f;
	specialAbilityTimer = 0.0f;
	specialAbility = false;
	speed = originalSpeed;
	body->SetLinearVelocity(vel);
	return false;
}

void BossOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
		damaged = true;
	}
	else {
		currentHealth = 0;
		this->Destroy();
		hammer->SetActive(false);
		this->RemoveChild(hammer);
		if (item != nullptr) {
			item->Reset();
		}
	}
}

void BossOrc::Reset() {
	// Reset all of the variables to their start value
	body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
	playerLastLocation = spawnPosition;
	if (!IsAlive()) {
		alive = true;
		hammer->SetActive(true);
		this->AddChild(hammer);
		currentHealth = health;
		SetActive(true);
		if (item != nullptr) {
			item->Destroy();
		}
	}
	specialAbilityTimer = 0.0f;
	specialAbility = false;
	timer = 0.0f;
	speed = originalSpeed;
	currentHealth = health;
}
