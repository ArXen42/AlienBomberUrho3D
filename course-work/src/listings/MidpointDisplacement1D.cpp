void TerrainController::MidpointDisplacement1D(unsigned int l, unsigned int r, float roughness)
{
	const unsigned int delta = r - l;
	if (delta > 1)
	{
		heightmap_[(l + r)/2] = (heightmap_[l] + heightmap_[r]) / 2
		                        + (Random() - 0.5f)
		                          * delta * roughness;

		MidpointDisplacement1D(l, (l + r) / 2, roughness);
		MidpointDisplacement1D((l + r) / 2, r, roughness);
	}
}