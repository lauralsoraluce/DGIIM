#encoding:utf-8
require_relative 'WeaponType.rb'
require_relative 'WeaponToUI.rb'
#require_relative 'Dice.rb'

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

=begin
		def self.newConstructor (name, uses)
			#laserprob = 0.5
			#plasmaprob = 0.3
			generator = Random.new
			prob = generator.rand
			dice = Dice.new
			
			if prob < dice.FIRSTSHOTPROB
				new(name,WeaponType::LASER,uses)
			else 
				if prob < (dice.FIRSTSHOTPROB + dice.NWEAPONSPROB)
					new(name,WeaponType::PLASMA,uses)
				else
					new(name,WeaponType::MISSILE,uses)
				end
			end 
		end
=end
		def getUIversion
			WeaponToUI.new(self)
		end
		
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
			#"Name: " + @name.to_s + "\nType: " + @type.to_s + "\nUses: " + @uses.to_s
			getUIversion.to_s
		end
	end
	
	#objeto = Weapon.new("Pepe", WeaponType::LASER, 20)
	#puts objeto.to_s
	
end
