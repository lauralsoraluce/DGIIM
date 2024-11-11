#encoding utf-8

require_relative 'SuppliesPackage.rb'
require_relative 'SpaceStation.rb'
require_relative 'SpaceCity.rb'

class Examen
    def self.run 

        aux = Array.new
        aux2= Array.new

        i=0
        while i<3
            supplies = Deepspace::SuppliesPackage.new(i+1, i+1, i+1)
            aux.push(Deepspace::SpaceStation.new("a", supplies))
        end

        rest=Array.new
        rest.push(aux.at(0))
        rest.push(aux.at(2))
        city = Deepspace::SpaceCity.new(aux.at(1), rest)
        #aux.at(1) = city
        
        aux2.push(aux.at(0))
        aux2.push(city)
        aux2.push(aux.at(2))

        i=0
        while i<3
            aux.at(i).fire
        end

    end
end

Examen.run
