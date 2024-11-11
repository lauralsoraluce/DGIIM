#encoding:utf-8
require_relative 'CombatResult.rb'
require_relative 'GameCharacter.rb'
require_relative 'ShotResult.rb'
require_relative 'Loot.rb'
require_relative 'SuppliesPackage.rb'
require_relative 'ShieldBooster.rb'
require_relative 'Weapon.rb'
require_relative 'Dice.rb'

module Deepspace
	class TestP1
		def self.main
			puts "\n---------------------------------------------------------------------------------------------------------\n"
			
			loot = Loot.new(1, 2, 3, 4 ,5)
			puts "Test Clase Loot \nSupplies: " + loot.nSupplies.to_s + "\nWeapons: " + loot.nWeapons.to_s + "\nShields: " + loot.nShields.to_s + "\nHangars: " + loot.nHangars.to_s + "\nMedals: " + loot.nMedals.to_s
			
			puts "\n---------------------------------------------------------------------------------------------------------\n"
			
			supplies1 = SuppliesPackage.new(100, 200, 300)
			supplies2 = SuppliesPackage.newCopy(supplies1)
			puts "Test Clase SuppliesPackage \nAmmo power: " + supplies2.ammoPower.to_s + "\nFuel units: " + supplies2.fuelUnits.to_s + "\nShield power: " + supplies2.shieldPower.to_s
			
			puts "\n---------------------------------------------------------------------------------------------------------\n"
			
			shield1 = ShieldBooster.new("Pepe", 2.5, 1)
			shield2 = ShieldBooster.newCopy(shield1)
			puts "\Test Clase ShieldBooster \nName: " + shield2.name + "\nBoost: " + shield2.boost.to_s + "\nUses: " + shield2.uses.to_s
			puts "\nProbamos el método useIt \nResultado tras llamarlo una vez: " + shield2.useIt.to_s + "(= @boost) \nVolvemos a llamarlo: " + shield2.useIt.to_s
			puts "\nValor del atributo uses tras llamar al método useIt dos veces: " + shield2.uses.to_s
			
			puts "\n---------------------------------------------------------------------------------------------------------\n"
			
			weapon1 = Weapon.new("Pepe", WeaponType::LASER, 1)
			weapon2 = Weapon.newCopy(weapon1)
			puts "Test Clase Weapon \nName: " + weapon2.name + "\nType: " + weapon2.type.to_s + "\nUses: " + weapon2.uses.to_s + "\nPower: " + weapon2.power.to_s
			puts "\nProbamos el método useIt \nResultado tras llamarlo una vez: " + weapon2.useIt.to_s + "(= power) \nVolvemos a llamarlo: " + weapon2.useIt.to_s
			puts "\nValor del atributo uses tras llamar al método useIt dos veces: " + weapon2.uses.to_s
			
			puts "\n---------------------------------------------------------------------------------------------------------\n"
			
			dice = Dice.new
			puts "Test Clase Dice"

			hangarsprob = 0
			weaponsprob = 0
			shieldsprob = 0
			players = 0
			firstshot = 0
			speed = 0

			for i in (0..99)
				salida = dice.initWithNHangars
			
				if salida == 0
					hangarsprob = hangarsprob + 1
				end
			end
			
			puts "\nProbabilidad de hangar sobre 100: " + hangarsprob.to_s
			
			for i in (0..99)
				salida = dice.initWithNWeapons
				
				if salida == 1
					weaponsprob = weaponsprob + 1
				end
			end
			
			puts "\nProbabilidad de weapons sobre 100: " + weaponsprob.to_s
			
			for i in (0..99)
				salida = dice.initWithNShields
			
				if salida == 0
					shieldsprob = shieldsprob + 1
				end
			end
			
			puts "\nProbabilidad de shields sobre 100: " + shieldsprob.to_s
			
			for i in (0..99)
				salida = dice.whoStarts(2)
			
				if salida == 1
					players = players + 1
				end
			end
			
			puts "\nProbabilidad de players sobre 100 (entre 2 jugadores): " + players.to_s
			
			for i in (0..99)
				salida = dice.firstShot
				
				if salida == GameCharacter::SPACESTATION
					firstshot = firstshot + 1
				end
			end
			
			puts "\nProbabilidad de que empiece la estación espacial disparando sobre 100: " + firstshot.to_s
			
			for i in (0..99)
				salida = dice.spaceStationMoves(0.7)
			
				if salida
					speed = speed + 1
				end
			end
			
			puts "\nProbabilidad de que la estación se mueva sobre 100 (speed = 0.7): " + speed.to_s
		end
	end
	
	TestP1.main
end
