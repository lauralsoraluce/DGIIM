#encoding:utf-8

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
	end
end
