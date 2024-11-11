require_relative 'copiaSpaceStation.rb'
require_relative 'copiaSuppliesPackage.rb'
require_relative 'copiaLoot.rb'
require_relative 'copiaGameUniverse.rb'
require_relative 'copiaCardDealer.rb'

class Examen
	def self.run
		supplies = Deepspace::SuppliesPackage.new(0,0,0)
		estacion = Deepspace::SpaceStation.new("Estacion", supplies)
		loot = Deepspace::Loot.new(10, 3, 2, 1, 0, false, false)
		estacion.setLoot(loot)
		
		game = Deepspace::GameUniverse.new()
		names = ['Laura', 'Alba']
		game.init(names)
		
		test = Deepspace::CardDealer.instance
		enemy = test.nextEnemy()
		puts enemy.to_s
		
		game.combatGo(estacion, enemy)
		
		puts estacion.to_s
	end
end
Examen.run
