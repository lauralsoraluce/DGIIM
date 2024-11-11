#encoding:utf-8
require_relative 'WeaponType.rb'
require_relative 'WeaponToUI.rb'
require_relative 'copiaDice.rb'

module Deepspace
	class Weapon
		def initialize (n, t, u) #"constructor"
				@name=n
				@type=t
				@uses=u
		end
		
=begin
		
=end
		def self.copy2 (n,u)
			dice = Dice.new
			type = dice.whichType
			new(n, type, u)
		end
		
		def self.newCopy (copy)
			new(copy.name, copy.type, copy.uses)
		end

		def getUIversion
			WeaponToUI.new(self)
		end
		
		public
		def name
			@name
		end
		def type
			@type
		end
		def uses
			@uses
		end
		
		def power
			@type.power
		end
		
		def useIt
			if @uses > 0
				@uses = @uses - 1
				power
			else
				1.0
			end
		end

		def to_s
			"Name: " + @name.to_s + "\nType: " + @type.to_s + "\nUses: " + @uses.to_s
		end
	end
	
	#objeto = Weapon.new("Pepe", WeaponType::LASER, 20)
	#puts objeto.to_s
	
end

