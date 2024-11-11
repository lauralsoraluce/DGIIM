#encoding:utf-8

require_relative 'SpaceStation.rb'
require_relative 'Transformation.rb'

module Deepspace
    class SpaceCity < SpaceStation
        attr_reader :collaborators

        def initialize (base, rest)
            super(base)
            @base = base
            @collaborators = rest
        end

        def fire
            fire = @base.fire

            for station in @collaborators do
                fire += station.fire
            end
        end

        def protection
            shield = @base.protection

            for station in @collaborators do
                shield += station.protection
            end
        end

        def setLoot (loot)
            super

            return Transformation::NOTRANSFORM
        end
    end
end