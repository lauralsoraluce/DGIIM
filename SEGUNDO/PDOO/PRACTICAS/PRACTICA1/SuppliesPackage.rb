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
		
		public
		def ammoPower
			@ammoPower
		end
		def fuelUnits
			@fuelUnits
		end
		def shieldPower
			@shieldPower
		end
	end
end
