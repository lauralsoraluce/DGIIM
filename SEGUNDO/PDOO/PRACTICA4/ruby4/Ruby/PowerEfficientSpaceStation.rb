#encoding:utf-8

require 'singleton'

require_relative 'SpaceStation.rb'
require_relative 'Transformation.rb'

module Deepspace
    class PowerEfficientSpaceStation < SpaceStation
        @@EFFICIENCYFACTOR = 1.10

        def initialize (station)
            super
        end

        def fire
            fire = super

            return (fire*@@EFFICIENCYFACTOR)
        end

        def protection
            shield = super

            return (shield*@@EFFICIENCYFACTOR)
        end

        def setLoot (loot)
            trans = super

            if (trans == Transformation::SPACECITY)
                return Transformation::NOTRANSFORM
            else
                return trans
            end
        end
    end
end