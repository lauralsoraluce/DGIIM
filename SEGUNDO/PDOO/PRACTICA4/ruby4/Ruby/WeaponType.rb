#encoding:utf-8

module Deepspace
	module WeaponType
		class Type
			def initialize (p) #"constructor"
				@power=p
			end
			
			public
			def power
				@power
			end

			def to_s
				if @power == 2.0
					"LASER. Power: " + @power.to_s
				elsif @power == 3.0
					"MISSILE. Power: " + @power.to_s
				elsif @power == 4.0
					"PLASMA. Power: " + @power.to_s
				end
			end
		end
		
		LASER = Type.new(2.0)
		MISSILE = Type.new(3.0)
		PLASMA = Type.new(4.0)

	end
end
