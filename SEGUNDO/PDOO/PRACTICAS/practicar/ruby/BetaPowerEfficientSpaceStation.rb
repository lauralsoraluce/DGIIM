#encoding:utf-8

require 'singleton'

require_relative 'PowerEfficientSpaceStation.rb'
require_relative 'Transformation.rb'
require_relative 'Dice.rb'

module Deepspace
    class BetaPowerEfficientSpaceStation < PowerEfficientSpaceStation
        @@EXTRAEFFICIENCY=1.2

        def initialize (station)
            super(station)
            @dice=Dice.new
        end

        def fire
            if (dice.extraEfficiency)
                return (super*EXTRAEFFICIENCY)
            else
                return super
            end
        end

        def setLoot(loot)
            check = super(loot)

            if (check==Transformation::SPACECITY)
                return Transformation::NOTRANSFORM
            else
                return check
            end
        end
    end
end