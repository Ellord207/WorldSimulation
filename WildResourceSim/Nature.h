#pragma once


namespace Nature
{

	enum BiomeType
	{
		Wasteland,
		Forest,
		Quarry,
		Plains,
		Mountains,
		Desert,
		Volcanic,
		Water,
	};

	struct Resources
	{

		/* Some refences I found for techincics for member varibles
		https://stackoverflow.com/questions/11031062/c-preprocessor-avoid-code-repetition-of-member-variable-list/11744832#11744832
		https://stackoverflow.com/questions/19059157/iterate-through-struct-and-class-members
		*/
		// food -> dependant for population
		int crops = 0;
		int wildlife = 0;
		int cattle = 0;

		// construction -> dependant for expantion
		int wood = 0;
		int stone = 0;

		// other -> movement and such
		int water = 0;
		int terrain = 0;

		enum ResourceTypes : int
		{
			Crops,
			Wildlife,
			Cattle,
			Wood,
			Stone,
			Water,
			Terrain,
			NUMBER_OF_TYPES
		};

	};

	struct Biome
	{
		Biome() : type(Nature::Wasteland), magnitude(0)
		{}
		Biome(BiomeType t, int mag) : type(t), magnitude(mag) 
		{}

		BiomeType type;
		float  magnitude;
	};

}
