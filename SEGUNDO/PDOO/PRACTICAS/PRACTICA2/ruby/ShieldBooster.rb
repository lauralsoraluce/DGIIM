#encoding:utf-8

require_relative 'ShieldToUI.rb'

module Deepspace
	class ShieldBooster
		def initialize (n, b, u) #"constructor"
				@name=n
				@boost=b
				@uses=u
		end
		
		def self.newCopy (copy)
			new(copy.name, copy.boost, copy.uses)
		end

		def getUIversion
			ShieldToUI.new(self)
		end

		public
		def name
			@name
		end
		def boost
			@boost
		end
		def uses
			@uses
		end
		
		def useIt
			if @uses > 0
				@uses = @uses - 1
				@boost
			else
				1.0
			end
		end

		def to_s
			"Name: " + @name.to_s + "\nBoost: " + @boost.to_s + "\nUses: " + @uses.to_s
		end

	end

	#objeto = ShieldBooster.new("Laura", 4.5, 2)
	#objeto2 = objeto.getUIversion() 		#Para comprobar la dependencia 
	#puts objeto2.to_s
end
