require_relative 'copiaSpaceStation.rb'
require_relative 'copiaSuppliesPackage.rb'
require_relative 'copiaSpaceCity.rb'

class Examen 
	def self.run
		array = Array.new
		i=0
		while i<3
			supplies = Deepspace::SuppliesPackage.new(i+1,i+2,i+3)
			array.push(Deepspace::SpaceStation.new('arma', supplies))
			#puts array.at(i).to_s
			i=i+1
		end
		
		collaborators = [array.at(1), array.at(2)]
		array[0] = Deepspace::SpaceCity.new(array.at(0), collaborators)
 
 		i=0
 		while i<3
 			array[i].fire
 			i=i+1
 		end
	end
end
Examen.run

