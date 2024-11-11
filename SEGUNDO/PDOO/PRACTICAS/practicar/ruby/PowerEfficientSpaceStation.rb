#encoding:utf-8

require 'singleton'

require_relative 'SpaceStation.rb'
require_relative 'Transformation.rb'

module Deepspace
    class PowerEfficientSpaceStation < SpaceStation
        @@EFFICIENCYFACTOR=1.1
        def initialize (station)
            newCopy(station)
        end

        def fire
            fire=super
            return (fire*EFFICIENCYFACTOR)
        end

        def protection
            shield = super
            return (shield*EFFICIENCYFACTOR)
        end

        def setLoot(loot)
            check = super

            if (check==Transformation::SPACECITY)
                return Transformation::NOTRANSFORM
            else
                return check
            end
        end
    end
end