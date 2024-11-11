#encoding:utf-8

require 'singleton'

require_relative 'PowerEfficientSpaceStation.rb'
require_relative 'Dice.rb'

module Deepspace
    class BetaPowerEfficientSpaceStation < PowerEfficientSpaceStation
        @@EXTRAEFFICIENCY = 1.20

        def initialize (station)
            super
            @dice = Dice.new
        end

        def fire
            if (dice.extraEfficiency)
                return (super * @@EXTRAEFFICIENCY)
            else
                return super
            end
        end
    end
end