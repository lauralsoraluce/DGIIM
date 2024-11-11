#encoding:utf-8
require_relative 'WeaponType.rb'

module Deepspace
	class Weapon
		def initialize (n, t, u) #"constructor"
				@name=n
				@type=t
				@uses=u
		end
		
		def self.newCopy (copy)
			new(copy.name, copy.type, copy.uses)
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
	end
	
	# objeto = Weapon.new("Pepe", WeaponType::LASER, 20)
end
