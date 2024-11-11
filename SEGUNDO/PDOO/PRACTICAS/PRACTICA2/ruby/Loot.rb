#encoding:utf-8

require_relative 'LootToUI.rb'

module Deepspace
	class Loot
		attr_reader :efficient, :spaceCity
		def initialize (supp, weap, shield, hang, med, ef=false, city=false) #"constructor"
			@nSupplies=supp
			@nWeapons=weap
			@nShields=shield
			@nHangars=hang
			@nMedals=med
			@efficient=ef
			@spaceCity=city
		end

		def getUIversion
			LootToUI.new(self)
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

		def to_s ()
			#"Number of supplies: " + @nSupplies.to_s + "\nNumber of weapons: " + @nWeapons.to_s + "\nNumber of shields: " + @nShields.to_s + "\nNumber of hangars: " + @nHangars.to_s + "\nNumber of medals: " + @nMedals.to_s
			getUIversion.to_s
		end
	end

	#objeto = Loot.new(1,2,3,4,5)
	#objeto2 = objeto.getUIversion
	#puts objeto2.to_s
end
