GetComponent<CollisionsAggregator>()
		->GetSignal(TerrainCollider::GetTypeInfoStatic())
		->Connect(this, &AircraftController::OnTerrainCollision);