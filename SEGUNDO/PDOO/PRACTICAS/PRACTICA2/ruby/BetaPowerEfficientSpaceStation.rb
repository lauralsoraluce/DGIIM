#encoding:utf-8

require 'singleton'

require_relative 'PowerEfficientSpaceStation.rb'
require_relative 'Transformation.rb'
require_relative 'Dice.rb'
require_relative 'BetaPowerEfficientSpaceStationToUI.rb'

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

        def to_s
            message = "(Beta) " + super
            return message
        end
      
        # To UI
        def getUIversion
            return BetaPowerEfficientSpaceStationToUI.new(self)
        end
    end
end