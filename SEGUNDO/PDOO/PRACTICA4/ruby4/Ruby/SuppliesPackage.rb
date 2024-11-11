#encoding:utf-8

module Deepspace
	class SuppliesPackage
		def initialize (ammo, fuel, shield) #"constructor"
				@ammoPower=ammo
				@fuelUnits=fuel
				@shieldPower=shield
		end
		
		def self.newCopy (copy)
			new(copy.ammoPower, copy.fuelUnits, copy.shieldPower)
		end
		
		def ammoPower
			@ammoPower
		end
		def fuelUnits
			@fuelUnits
		end
		def shieldPower
			@shieldPower
		end

		def to_s ()
			"Ammo Power: " + @ammoPower.to_s + "\nFuel Units: " + @fuelUnits.to_s + "\nShield Power: " + @shieldPower.to_s
		end
	end

	# objeto = SuppliesPackage.new(2.0, 4.0, 2.5)
	# puts objeto.to_s

end
