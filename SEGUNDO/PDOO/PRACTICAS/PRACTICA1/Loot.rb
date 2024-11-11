#encoding:utf-8

module Deepspace
	class Loot
		def initialize (supp, weap, shield, hang, med) #"constructor"
				@nSupplies=supp
				@nWeapons=weap
				@nShields=shield
				@nHangars=hang
				@nMedals=med
		end
		
		public
		def nSupplies
			@nSupplies
		end
		def nWeapons
			@nWeapons
		end
		def nShields
			@nShields
		end
		def nHangars
			@nHangars
		end
		def nMedals
			@nMedals
		end
	end
end
